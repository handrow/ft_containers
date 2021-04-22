/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:11:30 by handrow           #+#    #+#             */
/*   Updated: 2021/04/22 04:45:07 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../allocator.hpp"
#include "../algorithm.hpp"

namespace ft
{

    template<typename T>
    struct AVLnode
    {
        AVLnode*     left;
        AVLnode*     right;
        AVLnode*     parent;
        T            data;
        int          h;

        static int get_height(const AVLnode* other)
        {
            return other != NULL ? other->h : 0;
        }

        int bfactor() const
        {
            return get_height(left) - get_height(right);
        }

        void fix_height()
        {
            h = max(get_height(left), get_height(right)) + 1;
        }
    };

    template <typename T, typename Comp=less<T> , typename Allocator=ft::allocator<T> >
    class AVLtree
    {
    public:
        struct iterator
        {
            typedef T           ValueType;
            typedef AVLnode<T>  NodeType;

            NodeType*           _curnode;
            NodeType*           _end;

            iterator(NodeType* end = NULL, NodeType* cur = NULL)
            : _curnode(cur)
            , _end(end)
            {
            }

            iterator(const AVLtree& tree)
            : _curnode(tree._root)
            , _end(tree._end_node)
            {
            }

            bool    is_equal(const iterator& other) const
            {
                return _curnode == other._curnode;
            }

            static NodeType*    __min_elem(NodeType* node)
            {
                while (node->left)
                    node = node->left;
                return node;
            }

            static NodeType*    __max_elem(NodeType* node)
            {
                while (node->right)
                    node = node->right;
                return node;
            }

            iterator&    next()
            {
                if (_curnode->right)
                    _curnode = __min_elem(_curnode->right);
                else if (_curnode != _end)
                {
                    while (_curnode->parent && _curnode->parent->right == _curnode) // while we are right child go up
                        _curnode = _curnode->parent;
                    _curnode = _curnode->parent;
                    if (_curnode == NULL)
                        _curnode = _end;
                }
                else
                    _curnode->left->parent = NULL; // if next after end, then SEGFAULT
                return *this;
            }

            iterator&    prev()
            {
                if (_curnode->left)
                    _curnode = __max_elem(_curnode->left);
                else
                {
                    while (_curnode->parent && _curnode->parent->left == _curnode)
                        _curnode = _curnode->parent;
                    _curnode = _curnode->parent; // if no more nodes, then it will be NULL
                }
                return *this;
            }
        
            T&      get_data_ref() const
            {
                return _curnode->data;
            }

            const T& get_data_const_ref() const
            {
                return _curnode->data;
            }
        };

    public:
        typedef Comp                                                    Compare;
        typedef T                                                       DataType;
        typedef AVLnode<DataType>                                       NodeType;
        typedef Allocator                                               DataAllocator;
        typedef typename Allocator::template rebind<NodeType>::other    NodeAllocator;

    private:
        Compare             _compare;
        DataAllocator       _data_alloc;
        NodeAllocator       _node_alloc;
        NodeType*           _end_node; // fake node
        NodeType*           _root;

    private:
        NodeType*           _new_node()
        {
            NodeType* empty_node = _node_alloc.allocate(1);
            empty_node->left = NULL;
            empty_node->right = NULL;
            empty_node->parent = NULL;
            empty_node->h = 1;
            return empty_node;
        }

        void                _delete_node(NodeType* node)
        {
            _node_alloc.deallocate(node, 1);
        }

        static bool         _node_compare(const NodeType* n1, const NodeType* n2, const Compare& c)
        {
            return c(n1->data, n2->data);
        }

        static bool         _node_compare(const NodeType* n1, const DataType& d2, const Compare& c)
        {
            return c(n1->data, d2);
        }

        static bool         _node_compare(const DataType& d1, const NodeType* n2, const Compare& c)
        {
            return c(d1, n2->data);
        }

        static NodeType*    _rotate_l(NodeType* subroot)
        {
            NodeType*   new_subroot = subroot->right;

            subroot->right = new_subroot->left;
            if (subroot->right)
                subroot->right->parent = subroot;

            new_subroot->left = subroot;
            new_subroot->left->parent = new_subroot;

            subroot->fix_height();
            new_subroot->fix_height();
            return new_subroot;
        }

        static NodeType*    _rotate_r(NodeType* subroot)
        {
            NodeType*   new_subroot = subroot->left;

            subroot->left = new_subroot->right;
            if (subroot->left)
                subroot->left->parent = subroot;

            new_subroot->right = subroot;
            new_subroot->right->parent = new_subroot;

            subroot->fix_height();
            new_subroot->fix_height();
            return new_subroot;
        }

        static NodeType*    _balance(NodeType* subroot)
        {
            subroot->fix_height();
            const int sroot_bfactor = subroot->bfactor();
            if (sroot_bfactor >= 2)
            {
                if (subroot->left->bfactor() <= -1)
                {
                    subroot->left = _rotate_l(subroot->left);
                    subroot->left->parent = subroot;
                }
                return _rotate_r(subroot);
            }
            else if (sroot_bfactor <= -2)
            {
                if (subroot->right->bfactor() >= 1)
                {
                    subroot->right = _rotate_r(subroot->right);
                    subroot->right->parent = subroot;
                }
                return _rotate_l(subroot);
            }
            return subroot;
        }

        static NodeType*    _insert(NodeType* subroot, NodeType* inode, const Compare& c)
        {
            if (subroot == NULL)
                return inode;
            else if (_node_compare(subroot, inode, c))  // <
            {
                subroot->right = _insert(subroot->right, inode, c);
                subroot->right->parent = subroot;
            }
            else
            {
                subroot->left = _insert(subroot->left, inode, c);
                subroot->left->parent = subroot;
            }
            return _balance(subroot);
        }

        static NodeType*    _delete_max(NodeType* subroot, NodeType*& deleted)
        {
            if (subroot->right == NULL)
                return deleted = subroot, (NodeType*)NULL;
            
            subroot->right = _delete_max(subroot->right, deleted);
            if (subroot->right)
                subroot->right->parent = subroot;
            return _balance(subroot);
        }

        static NodeType*    _delete(NodeType* subroot, const T& data, NodeType*& deleted,
                                    NodeType*& after_del, const Compare& c)
        {
            if (subroot == NULL)
                return deleted = NULL, subroot;
            else if (_node_compare(subroot, data, c)) // <
            {
                subroot->right = _delete(subroot->right, data, deleted, after_del, c);
                if (subroot->right)
                    subroot->right->parent = subroot;
            }
            else if (_node_compare(data, subroot, c)) // >
            {
                subroot->left = _delete(subroot->left, data, deleted, after_del, c);
                if (subroot->left)
                    subroot->left->parent = subroot;
            }
            else // ==
            {
                deleted = subroot;

                {
                    iterator after(NULL, deleted);
                    after_del = after.next()._curnode;
                }

                if (subroot->left == NULL)
                    return subroot->right;

                deleted->left = _delete_max(subroot->left, subroot);
                after_del = subroot;

                subroot->right = deleted->right;
                subroot->left = deleted->left;
                if (subroot->right)
                    subroot->right->parent = subroot;
                if (subroot->left)
                    subroot->left->parent = subroot;
            }
            return _balance(subroot);
        }

        static NodeType*    _cleanup_tree(NodeType* subroot, DataAllocator& da, NodeAllocator& na)
        {
            if (subroot != NULL)
            {
                _cleanup_tree(subroot->right, da, na);
                _cleanup_tree(subroot->left, da, na);
                da.destroy(&subroot->data);
                na.deallocate(subroot, 1);
            }
            return NULL;
        }

        static NodeType*    _copy(NodeType* subroot, DataAllocator& da, NodeAllocator& na)
        {
            if (subroot != NULL)
            {
                NodeType* old_subroot = subroot;
                subroot = na.allocate(1);
                subroot->left = _copy(old_subroot->left, da, na);
                subroot->right = _copy(old_subroot->right, da, na);
                subroot->h = old_subroot->h;

                if (subroot->left)
                    subroot->left->parent = subroot;
                if (subroot->right)
                    subroot->right->parent = subroot;

                da.construct(&subroot->data, old_subroot->data);
            }
            return subroot;
        }

    public:

        ~AVLtree()
        {
            _root = _cleanup_tree(_root, _data_alloc, _node_alloc);
            _delete_node(_end_node);
        }

        AVLtree(const Compare& comp=Compare(), const DataAllocator& da=DataAllocator(),
                const NodeAllocator& na=NodeAllocator())
        : _compare(comp)
        , _data_alloc(da)
        , _node_alloc(na)
        , _end_node(_new_node())
        , _root(NULL)
        {
            _end_node->h = 0;
        }

        AVLtree(const AVLtree& other_tree)
        : _compare(other_tree._compare)
        , _data_alloc(other_tree._data_alloc)
        , _node_alloc(other_tree._node_alloc)
        , _end_node(_new_node())
        , _root(_copy(other_tree._root, _data_alloc, _node_alloc))
        {
            _end_node->h = 0;
        }

        AVLtree& operator=(const AVLtree& other_tree)
        {
            if (this != &other_tree)
            {
                _root = _cleanup_tree(_root, _data_alloc, _node_alloc);
                _compare = other_tree._compare;
                _data_alloc = other_tree._data_alloc;
                _node_alloc = other_tree._node_alloc;
                _root = _copy(other_tree._root, _data_alloc, _node_alloc);
            }
            return *this;
        }


        iterator begin() const
        { 
            return iterator(_end_node, (_root == NULL)
                                            ? _end_node
                                            : iterator::__min_elem(_root));
        }

        iterator end() const
        {
            return iterator(_end_node, _end_node);
        }

        iterator find_node(const T& data) const
        {
            iterator iter(_end_node, _root);

            while (true)
            {
                if (iter._curnode == NULL)
                    return iterator(_end_node, _end_node);
                else if (_node_compare(iter._curnode, data, _compare))
                    iter._curnode = iter._curnode->right;
                else if (_node_compare(data, iter._curnode, _compare))
                    iter._curnode = iter._curnode->left;
                else
                    return iter;
                
            }
        }

        iterator insert(const T& data)
        {
            NodeType* node = _new_node();

            _data_alloc.construct(&node->data, data);
            _root = _insert(_root, node, _compare);
            _root->parent = NULL;
            _end_node->parent = iterator::__max_elem(_root);

            return iterator(_end_node, node);
        }

        iterator remove(const T& data)
        {
            NodeType* deleted = NULL;
            NodeType* after_del = NULL;
            _root = _delete(_root, data, deleted, after_del, _compare);
            if (_root)
                _root->parent = NULL;

            if (deleted != NULL)
            {
                _node_alloc.destroy(deleted);
                _node_alloc.deallocate(deleted, 1);
            }
            return iterator(_end_node, (after_del == NULL) ? _end_node
                                                           : after_del);
        }

    };

} // namespace ft
