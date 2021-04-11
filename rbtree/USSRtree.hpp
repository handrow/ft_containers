#pragma once

#include <cstddef>
#include <memory>
#include <algorithm>
#include <iostream>

namespace ft
{

    template<typename T, typename Comp>
    class AVLnode
    {
    private:
        Comp        __cmp_func;

    public:
        AVLnode*     left;
        AVLnode*     right;
        T           data;
        int         h;

    public:
        bool compare(const AVLnode& other) const
        {
            return compare(other.data);
        }
        
        bool compare(const T& other_data) const
        {
            return __cmp_func(data, other_data);
        }

        bool compare_r(const AVLnode& other) const
        {
            return compare_r(other.data);
        }

        bool compare_r(const T& other_data) const
        {
            return __cmp_func(other_data, data);
        }


        static int get_height(const AVLnode* other)
        {
            return other != NULL ? other->h : 0;
        }

        int bfactor() const {
            return get_height(left) - get_height(right);
        }

        void fix_height()
        {
            h = std::max(get_height(left), get_height(right)) + 1;
        }
    };

    template <typename T, typename Comp = std::less<T> , typename Allocator = std::allocator<T> >
    class AVLtree
    {
    public:
        typedef AVLnode<T, Comp>                                         NodeType;
        typedef Allocator                                               DataAllocator;
        typedef typename Allocator::template rebind<NodeType>::other    NodeAllocator;

    private:
        DataAllocator       _data_alloc;
        NodeAllocator       _node_alloc;
        NodeType*           _root;

    private:
        NodeType*       _new_node()
        {
            NodeType* empty_node = _node_alloc.allocate(1);
            empty_node->left = NULL;
            empty_node->right = NULL;
            empty_node->h = 1;
            return empty_node;
        }

        void            _delete_node(NodeType* node)
        {
            _node_alloc.deallocate(node, 1);
        }

        // must return new subroot
        // to use it, make like this: node = rotate_left(node);
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

        static NodeType*    _find_max(NodeType* subroot)
        {
            return subroot->right == NULL ? subroot
                                          : _find_max(subroot->right);
        }

        static NodeType*    _delete_max(NodeType* subroot, NodeType*& deleted)
        {
            if (subroot->right == NULL)
                return deleted = subroot, NULL;
            
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
                    return subroot->left;
                subroot->left = _delete_max(subroot->left, subroot);
                subroot->right = deleted->right;
                subroot->left = deleted->left;
            }
            return _balance(subroot);
        }

    public:

        AVLtree() : _root(NULL) {};

        void insert(const T& data) {
            NodeType* node = _new_node();

            _data_alloc.construct(&node->data, data);
            _root = _insert(_root, node);
        }

        void remove(const T& data) {
            NodeType* deleted;
            _root = _delete(_root, data, deleted);
            _node_alloc.destroy(&deleted);
            _node_alloc.deallocate(&deleted, 1);
        }

        void print(NodeType *node = _root) const {
            if (node == NULL)
                return 0;
            print(node->left)
        }

    };

} // namespace ft
