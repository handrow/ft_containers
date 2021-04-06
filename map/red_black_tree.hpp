/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 18:08:08 by handrow           #+#    #+#             */
/*   Updated: 2021/04/06 20:51:52 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
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
        typedef T                   value_type;
        typedef const T&            const_reference;
        typedef node<value_type>    node_type;
        typedef node_type*          node_pointer;
    //private:
        node_pointer                root;

    public:
        RBT() : root(NULL) {}

        node_pointer    grandparent(node_pointer n)
        {
            if (n != NULL && n->parent != NULL)
                return n->parent->parent;
            else
                return NULL;
        }

        node_pointer    uncle(node_pointer n)
        {
            node_pointer g = grandparent(n);
            if (g == NULL)
                return NULL; // no grandparent means no uncle
            if (n->parent == g->left)
                return g->right;
            else
                return g->left;
        }

        node_pointer    sibling(node_pointer n)
        {
            if (n == n->parent->left)
                return n->parent->right;
            else
                return n->parent->left;
        }

        void            rotateLeft(node_pointer root, node_pointer n)
        {
            node_pointer pivot = n->right;
 
            n->right = pivot->left;
            if (n->right != NULL)
                n->right->parent = n;
            pivot->parent = n->parent;
            if (n->parent == NULL)
                root = pivot;
            else if (n == n->parent->left)
                n->parent->left = pivot;
            else
                n->parent->right = pivot;

            pivot->left = n;
            n->parent = pivot;
        }

        void            rotateRight(node_pointer root, node_pointer n)
        {
            node_pointer pivot = n->left;
            
            n->left = pivot->right;
            if (n->left != NULL)
                n->left->parent = n;
            pivot->parent = n->parent;
            if (n->parent == NULL)
                root = pivot;
            else if (n == n->parent->left)
                n->parent->left = pivot;
            else
                n->parent->right = n;
            
            pivot->right = n;
            n->parent = pivot;
        }
    
        node_pointer    search(const_reference value)
        {
            node_pointer tmp = root;

            // if (tmp == NULL)
            //     return NULL;
            while (tmp)
            {
                if (value == tmp->data)
                    return tmp;
                else if (value < tmp->data)
                    tmp = tmp->left;
                else
                    tmp = tmp->right;
            }
            return NULL;
        }
        
        void            fixViolation(node_pointer root, node_pointer n)
        {
            node_pointer   nParent = NULL;
            node_pointer   nGgrandparent = NULL;

            while (n != root && n->color != BLACK && n->parent->color == RED)
            {
                nParent = n->parent;
                nGgrandparent = grandparent(n);
                
                // Case A: nParent is left child of nGrandparent
                if (nParent == nGgrandparent->left)
                {
                    node_pointer nUncle = nGgrandparent->right;
                    // Case 1: nUncle is red -> flip color
                    if (nUncle != NULL && nUncle->color == RED)
                    {
                        nGgrandparent->color = RED;
                        nParent->color = BLACK;
                        nUncle->color = BLACK;
                        n = nGgrandparent;
                    }
                    else
                    {
                        // Case 2: n is right child -> left rotation required
                        if (n == nParent->right)
                        {
                            rotateLeft(root, nParent);
                            n = nParent;
                            nParent = n->parent;
                        }
                        // Case 3: n is left child -> right rotation required
                        rotateRight(root, nGgrandparent);
                        std::swap(nParent->color, nGgrandparent->color);
                        n = nParent;
                    }
                }
            
                // Case B: nParent is right child of nGrandparent
                else
                {
                    node_pointer nUncle = nGgrandparent->left;
                    // Case 1: uncle is red -> flip color
                    if (nUncle != NULL && nUncle->color == RED)
                    {
                        nGgrandparent->color = RED;
                        nParent->color = BLACK;
                        nUncle->color = BLACK;
                        n = nGgrandparent;
                    }
                    else
                    {
                        // Case 2: n is left child -> right rotation required
                        if  (n == nParent->left)
                        {
                            rotateRight(root, nParent);
                            n = nParent;
                            nParent = n->parent;
                        }
                        // Case 3: n is right child ->left rotation required
                        rotateLeft(root, nGgrandparent);
                        std::swap(nParent->color, nGgrandparent->color);
                        n = nParent;
                    }
                }
            }
            root->color = BLACK;
        }

        node_pointer    RBT_insert(node_pointer root, node_pointer newNode)
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

        void            insert(const_reference val)
        {
            node_pointer newNode = new node_type(val);
            
            root = RBT_insert(root, newNode);
            fixViolation(root, newNode);
        }
    };

    
} // namespace ft