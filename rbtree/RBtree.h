#pragma once

#include <cstddef>
#include <memory>

namespace ft
{

    enum RBcolor { RED, BLACK };

    template<typename T, typename Comp>
    class RBnode
    {
    private:
        Comp        __cmp_func;

    public:
        RBnode*     parent;
        RBnode*     left;
        RBnode*     right;
        T           data;
        RBcolor     color;

    public:
        bool compare(const RBnode& other) const
        {
            return __cmp_func(data, other.data);
        }

        RBnode* grandparent() const
        {
            return parent->parent;
        }

        RBnode* sibling() const
        {
            return (this == parent->right) ? parent->left
                                           : parent->right;
        }

        RBnode* uncle() const
        {
            return parent->sibling();
        }
    };

    template <typename T, typename Comp, typename Allocator = std::allocator<T> >
    class RBtree
    {
    public:
        typedef RBnode<T, Comp>                                 NodeType;
        typedef Allocator                                       DataAllocator;
        typedef Allocator::template rebind<NodeType>::other     NodeAllocator;

    private:
        DataAllocator       _data_alloc;
        NodeAllocator       _node_alloc;
        NodeType*           _root;

    private:
        NodeType*       _new_node() const
        {
            NodeType* empty_node = _node_alloc.allocate(1);
            empty_node->color = RED;
            empty_node->parent = NULL;
            empty_node->left = NULL;
            empty_node->right = NULL;
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

        }

        static NodeType*    _rotate_r(NodeType* subroot)
        {

        }

        static NodeType*    _insert(NodeType* subroot, NodeType* inode)
        {
            if (subroot == NULL)
                return inode;
            else if (subroot->compare(*inode))
            {
                subroot->right = _insert(subroot->right, inode);
                subroot->right->parent = subroot;
            }
            else
            {
                subroot->left = _insert(subroot->left, inode);
                subroot->left->parent = subroot;
            }
            return subroot;
        }

    };

} // namespace ft
