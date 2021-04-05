/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 18:08:08 by handrow           #+#    #+#             */
/*   Updated: 2021/04/05 21:17:19 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

    enum e_color
    {
        RED,
        BLACK    
    };
    
    template<class _DataType>
    struct node
    {
        _DataType   data;
        node*       left;
        node*       right;
        node*       parent;
        bool        color;

        node(_DataType _data)
        :   data(_data),
            left(NULL),
            right(NULL),
            parent(NULL),
            color(RED) {}
    };

    template<class T>
    class RBT
    {
    public:
        typedef node<T> node;
    private:
        node*     root;

    public:
        RBT() : root(NULL) {}

        node*   grandparent(node* n)
        {
            if (n != NULL && n->parent != NULL)
                return n->parent->parent;
            else
                return NULL;
        }

        node*   uncle(node* n)
        {
            node* g = grandparent(n);
            if (g == NULL)
                return NULL; // no grandparent means no uncle
            if (n->parent == g->left)
                return g->right;
            else
                return g->left;
        }

        node*   sibling(node* n)
        {
            if (n == n->parent->left)
                return n->parent->right;
            else
                return n->parent->left;
        }

        void    rotateLeft(node* n)
        {
            node* pivot = n->right;
            pivot->parent = n->parent;
            if (n->parent != NULL)
            {
                if (n->parent->left == n)
                    n->parent->left = pivot;
                else
                    n->parent->right = parent;
            }
            n->right = pivot->left;
            if (pivot->left != NULL)
                pivot->left->parent = n;
            n->parent = pivot;
            pivot->left = n;
        }

        void    rotateRight(node* n)
        {
            node* pivot = n->left;
            pivot->parent = n->parent;
            if (n->parent != NULL)
            {
                if (n->parent->left == n)
                    n->parent->left = pivot;
                else
                    n->parent->right = pivot;
            }
            n->left = pivot->right;
            if (pivot->right != NULL)
                pivot->right->parent = n;
            
            n->parent = pivot;
            pivot->right = n;
        }

        void    fixViolation(node* root, node* n)
        {
            node*   parent_n = NULL;
            node*   grandParent_n = NULL;

            while (n != root && n->color != BLACK && n->parent->color == RED)
            {
                parent_n = n->parent;
                grandParent_n = n->parent->parent;
                
            }
        }

        node*   RBT_insert(node* root, node *newNode)
        {
            if (root == NULL)
                return newNode;
            
            if (newNode->data < root->data)
            {
                root->left = RBT_insert(root->left, newNode);
                root->left->parent = root;
            }
            else if (newNode->data > root->data)
            {
                root->right = RBT_insert(root->right, newNode);
                root->right->parent = root;
            }
            return root;
        }

        void    insert(const T& data)
        {
            node* newNode = new node(data);
            
            root = RBT_insert(root, newNode);
        }
    };

    
} // namespace ft