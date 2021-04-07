/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 18:08:08 by handrow           #+#    #+#             */
/*   Updated: 2021/04/07 21:07:07 by handrow          ###   ########.fr       */
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

      

        // node(_DataType _data)
        // :   data(_data),
        //     left(NULL),
        //     right(NULL),
        //     parent(NULL),
        //     color(RED) {}
        
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
        node_pointer                sentinel;
        typedef  sentinel           NIL;

            sentinel->parent = 0;
            sentinel->left = NIL;
            sentinel->right =NIL;
            sentinel->color = BLACK;
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

        void            rotateLeft(node_pointer n)
        {
            node_pointer pivot = n->right;
 
            n->right = pivot->left;
            if (pivot->left != NULL)
                pivot->left->parent = n;
            
            if (pivot != NULL)
                pivot->parent = n->parent;
            if (n->parent)
            {
                if (n == n->parent->left)
                    n->parent->left = pivot;
                else
                    n->parent->right = pivot;
            }
            else
                root = pivot;
            
            pivot->left = n;
            if (n != NULL)
                n->parent = pivot;
        }

        void            rotateRight(node_pointer n)
        {
            node_pointer pivot = n->left;

            n->left = pivot->right;
            if (pivot->right != NULL)
                pivot->right->parent = n;
            
            if (pivot != NULL)
                pivot->parent = n->parent;
            if (n->parent)
            {
                if (n == n->parent->right)
                    n->parent->right = pivot;
                else
                    n->parent->left = pivot;
            }
            else
                root = pivot;

            pivot->right = n;
            if (n != NULL)
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

        // void            insertCase1(node_pointer n);
        // void            insertCase2(node_pointer n);
        // void            insertCase3(node_pointer n);
        // void            insertCase4(node_pointer n);
        // void            insertCase5(node_pointer n);

        node_pointer    insert(const_reference value)
        {
            node_pointer    n = root;
            node_pointer    parent = NULL;
            node_pointer    newNode = new node_type(value);

            while (n != NULL)
            {
                if (value == n->data)
                    return n;
                parent = n;
                if (value < n->data)
                    n = n->left;
                else
                    n = n->right;
            }
            newNode->parent = parent;
            if (parent)
            {
                if (value < parent->data)
                    parent->left = n;
                else
                    parent->right = n;
            }
            else
                root = n;
            fixInsertion(n);
            return n;
        }

        void            fixInsertion(node_pointer n)
        {
            if (n != root && n->parent->color == RED)
            {
                if (n->parent == n->parent->parent->left)
                {
                    node_pointer u = n->parent->parent->right;
                    if (u->color == RED)
                    {
                        n->parent->color = BLACK;
                        u->color = BLACK;
                        n->parent->parent->color = RED;
                        n = n->parent->parent;
                    }
                    else
                    {
                        if (n == n->parent->right)
                        {
                            n = n->parent;
                            rotateLeft(n);
                        }
                        n->parent->color = BLACK;
                        n->parent->parent->color = RED;
                        rotateRight(n->parent->parent);
                    }
                }
            }
            else
            {
                node_pointer u = n->parent->parent->left;
                if (u->color == RED)
                {
                    n->parent->color = BLACK;
                    u->color = BLACK;
                    n->parent->parent->color = RED;
                    n = n->parent->parent;
                }
                else
                {
                    if (n == n->parent->left)
                    {
                        n = n->parent;
                        rotateRight(n);
                    }
                    n->parent->color = BLACK;
                    n->parent->parent->color = RED;
                    rotateLeft(n->parent->parent);
                }
            }
            root->color = BLACK;
        }
    };

    // template<class T>
    // void    RBT<T>::insertCase1(node_pointer n)
    // {
    //     if (n->parent == NULL)
    //         n->color = BLACK;
    //     else
    //         insertCase2(n);
    // }

    // template<class T>
    // void    RBT<T>::insertCase2(node_pointer n)
    // {
    //     if (n->parent->color == BLACK)
    //         return;
    //     else
    //         insertCase3(n);
    // }

    // template<class T>
    // void    RBT<T>::insertCase3(node_pointer n)
    // {
    //     node_pointer    u = uncle(n);
    //     node_pointer    g;

    //     if (u != NULL && u->color == RED)
    //     {
    //         n->parent->color = BLACK;
    //         u->color = BLACK;
    //         g = grandparent(n);
    //         g->color = RED;
    //         insertCase1(g);
    //     }
    //     else
    //         insertCase4(n);
    // }

    // template<class T>
    // void    RBT<T>::insertCase4(node_pointer n)
    // {
    //     node_pointer g = grandparent(n);
        
    //     if ((n == n->parent->right) && (n->parent == g->left))
    //     {
    //         rotateLeft(n->parent);
    //         n = n->left;
    //     }
    //     else if ((n == n->parent->left) && (n->parent == g->right))
    //     {
    //         rotateRight(n->parent);
    //         n = n->right;
    //     }
    //     insertCase5(n);
    // }

    // template<class T>
    // void    RBT<T>::insertCase5(node_pointer n)
    // {
    //     node_pointer g = grandparent(n);
        
    //     n->parent->color = BLACK;
    //     g->color = RED;
    //     if ((n == n->parent->left) && (n->parent == g->left))
    //         rotateRight(g);
    //     else
    //         rotateLeft(g);
    // }
    
} // namespace ft