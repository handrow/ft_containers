/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USSRtree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:11:30 by handrow           #+#    #+#             */
/*   Updated: 2021/04/19 04:33:40 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "../stack/stack.hpp"
#include "../allocator.hpp"

namespace ft
{

    template<class T>
    struct less
    {
        bool operator()(const T& x, const T& y) const
        {
            return x < y;
        }
    };

    template<class T>
    const T& max(const T& a, const T& b)
    {
        return (a > b) ? a : b;
    }

    template<typename T, typename Comp=less<T> >
    class AVLnode
    {
    private:
        Comp         __cmp_func;

    public:
        AVLnode*     left;
        AVLnode*     right;
        T            data;
        int          h;

    public:
        // <
        bool compare(const AVLnode& other) const
        {
            return compare(other.data);
        }
        
        // <
        bool compare(const T& other_data) const
        {
            return __cmp_func(data, other_data);
        }

        // >
        bool compare_r(const AVLnode& other) const
        {
            return compare_r(other.data);
        }

        // >
        bool compare_r(const T& other_data) const
        {
            return __cmp_func(other_data, data);
        }


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
            typedef AVLnode<T, Comp>      NodeType;

            stack<NodeType*>    _fwd;
            stack<NodeType*>    _rev;
            NodeType*           _curnode;
            NodeType*           _end;
            NodeType*           _rend;

            iterator(const AVLtree& tree)
            : _fwd(), _rev()
            , _curnode(tree._root)
            , _end(tree._end_node)
            , _rend(tree._rend_node)
            {
            }

            bool    is_equal(const iterator& other) const
            {
                return _curnode == other._curnode;
            }

            iterator&    next()
            {
                if (_curnode->right)
                {
                    move_to_right();
                    move_to_min();
                }
                else if (!_fwd.empty())
                {
                    _curnode = _fwd.top();
                    _fwd.pop();
                    while (!_rev.empty() && _curnode->h > _rev.top()->h)
                        _rev.pop();
                }
                else if (_curnode != _end)
                {
                    _rev.push(_curnode);
                    _curnode = _end;
                }
                return *this;
            }

            iterator&    prev()
            {
                if (_curnode->left)
                {
                    move_to_left();
                    move_to_max();
                }
                else if (!_rev.empty())
                {
                    _curnode = _rev.top();
                    _rev.pop();
                    while (!_fwd.empty() && _curnode->h > _fwd.top()->h) // delete old parents in other stack
                        _fwd.pop();
                }
                else if (_curnode != _rend) // if we are already on the rend, then we can't go prev
                {
                    _fwd.push(_curnode);
                    _curnode = _rend;
                }
                return *this;
            }

            void    move_to_max()
            {
                while (_curnode->right != NULL)
                    move_to_right();
            }

            void    move_to_min()
            {
                while (_curnode->left != NULL)
                    move_to_left();
            }

            void    move_to_left()
            {
                _fwd.push(_curnode);
                _curnode = _curnode->left;
            }

            void    move_to_right()
            {
                _rev.push(_curnode);
                _curnode = _curnode->right;
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
        typedef AVLnode<T, Comp>                                        NodeType;
        typedef Allocator                                               DataAllocator;
        typedef typename Allocator::template rebind<NodeType>::other    NodeAllocator;

    private:
        DataAllocator       _data_alloc;
        NodeAllocator       _node_alloc;
        NodeType*           _end_node; // fake node
        NodeType*           _rend_node; // fake node
        NodeType*           _root;

    private:
        NodeType*           _new_node()
        {
            NodeType* empty_node = _node_alloc.allocate(1);
            empty_node->left = NULL;
            empty_node->right = NULL;
            empty_node->h = 1;
            return empty_node;
        }

        void                _delete_node(NodeType* node)
        {
            _node_alloc.deallocate(node, 1);
        }

        static NodeType*    _rotate_l(NodeType* subroot)
        {
            NodeType*   new_subroot = subroot->right;
            subroot->right = new_subroot->left;
            new_subroot->left = subroot;
            subroot->fix_height();
            new_subroot->fix_height();
            return new_subroot;
        }

        static NodeType*    _rotate_r(NodeType* subroot)
        {
            NodeType*   new_subroot = subroot->left;
            subroot->left = new_subroot->right;
            new_subroot->right = subroot;
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
                    subroot->left = _rotate_l(subroot->left);
                return _rotate_r(subroot);
            }
            else if (sroot_bfactor <= -2)
            {
                if (subroot->right->bfactor() >= 1)
                    subroot->right = _rotate_r(subroot->right);
                return _rotate_l(subroot);
            }
            return subroot;
        }

        static NodeType*    _insert(NodeType* subroot, NodeType* inode)
        {
            if (subroot == NULL)
                return inode;
            else if (subroot->compare(*inode)) // <
                subroot->right = _insert(subroot->right, inode);
            else
                subroot->left = _insert(subroot->left, inode);
            return _balance(subroot);
        }

        static NodeType*    _delete_max(NodeType* subroot, NodeType*& deleted)
        {
            if (subroot->right == NULL)
                return deleted = subroot, (NodeType*)NULL;
            
            subroot->right = _delete_max(subroot->right, deleted);
            return _balance(subroot);
        }

        static NodeType*    _delete(NodeType* subroot, const T& data, NodeType*& deleted)
        {
            if (subroot == NULL)
                return deleted = NULL, subroot;
            else if (subroot->compare(data)) // <
                subroot->right = _delete(subroot->right, data, deleted);
            else if (subroot->compare_r(data)) // >
                subroot->left = _delete(subroot->left, data, deleted);
            else // ==
            {
                deleted = subroot;
                if (subroot->left == NULL)
                    return subroot->right;
                deleted->left = _delete_max(subroot->left, subroot);
                subroot->right = deleted->right;
                subroot->left = deleted->left;
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
                da.construct(&subroot->data, old_subroot->data);
            }
            return subroot;
        }

    public:

        iterator            begin() const
        {
            iterator    iter(*this);
            iter.move_to_min();
            return iter;
        }

        iterator            rend() const
        {
            iterator    iter(begin());

            iter.prev();
            return iter;
        }

        iterator            end() const
        {
            iterator    iter(*this);
            iter.move_to_max();
            iter.next();
            return iter;
        }

        iterator            find_node(const T& data) const
        {
            iterator iter(*this);
            while (true)
            {
                if (iter._curnode == NULL)
                    return end();
                else if (iter._curnode->compare(data))
                    iter.move_to_right();
                else if (iter._curnode->compare_r(data))
                    iter.move_to_left();
                else
                    return iter;
                
            }
        }

        ~AVLtree()
        {
            _root = _cleanup_tree(_root, _data_alloc, _node_alloc);
            _delete_node(_end_node);
            _delete_node(_rend_node);
        }

        AVLtree()
        : _root(NULL)
        , _end_node(_new_node())
        , _rend_node(_new_node())
        {
            _end_node->h = 0;
            _rend_node->h = 0;
        }

        AVLtree(const AVLtree& other_tree)
        : _data_alloc(other_tree._data_alloc)
        , _node_alloc(other_tree._node_alloc)
        , _root(_copy(other_tree._root, _data_alloc, _node_alloc))
        , _end_node(_new_node())
        , _rend_node(_new_node())
        {
            _end_node->h = 0;
            _rend_node->h = 0;
        }

        AVLtree& operator=(const AVLtree& other_tree)
        {
            if (this != &other_tree)
            {
                _root = _cleanup_tree(_root, _data_alloc, _node_alloc);
                _data_alloc = other_tree._data_alloc;
                _node_alloc = other_tree._node_alloc;
                _root = _copy(other_tree._root, _data_alloc, _node_alloc);
            }
            return *this;
        }

        void insert(const T& data)
        {
            NodeType* node = _new_node();

            _data_alloc.construct(&node->data, data);
            _root = _insert(_root, node);
        }

        void remove(const T& data)
        {
            NodeType* deleted;
            _root = _delete(_root, data, deleted);
            if (deleted != NULL) {
                _node_alloc.destroy(deleted);
                _node_alloc.deallocate(deleted, 1);
            }
        }

    };

} // namespace ft
