/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USSRtree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:11:30 by handrow           #+#    #+#             */
/*   Updated: 2021/04/12 20:02:03 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <iostream>

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
    const T& _max(const T& a, const T& b)
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
            h = _max(get_height(left), get_height(right)) + 1;
        }
    };

    template <typename T, typename Comp=less<T> , typename Allocator=std::allocator<T> >
    class AVLtree
    {
    public:
        typedef AVLnode<T, Comp>                                        NodeType;
        typedef Allocator                                               DataAllocator;
        typedef typename Allocator::template rebind<NodeType>::other    NodeAllocator;

    private:
        DataAllocator       _data_alloc;
        NodeAllocator       _node_alloc;
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

        static NodeType*    _search(NodeType* subroot, const T& data)
        {
            if (subroot == NULL)
                return NULL;
            else if (subroot->compare(data)) // this < data
                return _search(subroot->right, data);
            else if (subroot->compare_r(data)) // this > data
                return _search(subroot->left, data);
            else // this == data
                return subroot;
        }

        // HELPFULL A LOT
        static void         printBT(const std::string& prefix, const NodeType* node, bool isLeft)
        {
            if( node != NULL )
            {
                std::cout << prefix;

                std::cout << (isLeft ? "├──" : "└──" );

                // print the value of the node
                std::cout << node->data;
                std::cout << std::endl;

                // enter the next tree level - left and right branch
                printBT( prefix + (isLeft ? "│   " : "    "), node->right, true);
                printBT( prefix + (isLeft ? "│   " : "    "), node->left, false);
            }
        }

    public:
        // HELPFUL A LOT
        void printBT() const
        {
            printBT("", _root, false);    
        }

        AVLtree() : _root(NULL)
        {
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
            _node_alloc.destroy(deleted);
            _node_alloc.deallocate(deleted, 1);
        }

        bool contains(const T& data)
        {
            return _search(_root, data);
        }
    };

} // namespace ft
