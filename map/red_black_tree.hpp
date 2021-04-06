/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 18:08:08 by handrow           #+#    #+#             */
/*   Updated: 2021/04/07 00:37:43 by handrow          ###   ########.fr       */
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

        void            rotateLeft(node_pointer n)
        {
            node_pointer pivot = n->right;
 
            pivot->parent = n->parent;
            if (n->parent != NULL)
            {
                if (n->parent->left == n)
                    n->parent->left = pivot;
                else
                    n->parent->right = pivot;
            }

            n->right = pivot->left;
            if (pivot->left != NULL)
                pivot->left->parent = n;
            
            n->parent = pivot;
            pivot->left = n;
        }

        void            rotateRight(node_pointer n)
        {
            node_pointer pivot = n->left;

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

        void            insertCase1(node_pointer n);
        void            insertCase2(node_pointer n);
        void            insertCase3(node_pointer n);
        void            insertCase4(node_pointer n);
        void            insertCase5(node_pointer n);
        void            insert(node_pointer val)
        {
            node_pointer newNode = new node_type(val);
        }
    };

    void    RBT::insertCase1(node_pointer n)
    {
        if (n->parent == NULL)
            n->color = BLACK;
        else
            insertCase2(n);
    }

    void    RBT::insertCase2(node_pointer n)
    {
        if (n->parent->color == BLACK)
            return;
        else
            insertCase3(n);
    }

    void    RBT::insertCase3(node_pointer n)
    {
        node_pointer    u = uncle(n);
        node_pointer    g;

        if (u != NULL && u->color == RED)
        {
            n->parent->color = BLACK;
            u->color = BLACK;
            g = grandparent(n);
            g->color = RED;
            insertCase1(g);
        }
        else
            insertCase4(n);
    }

    void    RBT::insertCase4(node_pointer n)
    {
        node_pointer g = grandparent(n);
        
        if ((n == n->parent->right) && (n->parent == g->left))
        {
            rotateLeft(n->parent);
            n = n->left;
        }
        else if ((n == n->parent->left) && (n->parent == g->right))
        {
            rotateRight(n->parent);
            n = n->right;
        }
        insertCase5(n);
    }

    void    RBT::insertCase5(node_pointer n)
    {
        node_pointer g = grandparent(n);
        
        n->parent->color = BLACK;
        g->color = RED;
        if ((n == n->parent->left) && (n->parent == g->left))
            rotateRight(g);
        else
            rotateLeft(g);
    }    
    
} // namespace ft