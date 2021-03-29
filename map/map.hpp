/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:25:19 by handrow           #+#    #+#             */
/*   Updated: 2021/03/30 21:36:13 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>

namespace ft
{

    template<class K, class V>
    struct node
    {
        K           key;
        V           value;
        node<K, V>  left;
        node<K, V>  rigth;
        node<K, V>  parent;
        bool        isLeftChild;
        bool        black; // if true, the node is black else the node is red
        pair<K, V>  pair;
        
        node(K _k, V _v) 
        :   key(_k), 
            value(_v),
            left(NULL),
            rigth(NULL),
            parent(NULL),
            isLeftChild(false),
            black(false)
            pair(pair.make_pair<K, V>) {}
    };
    
    template<class K, class V>
    struct pair
    {
        typedef K  first_type;
        typedef V  second_type;
        
        K          first;
        V          second;

        // MEMBER FUNCTIONS
        pair(): first(), second() {}
        pair(first_type const& k, second_type const& v) : first(k), second(v) {}
        template< class U1, class U2 >
        pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
        pair&               operator=(const pair& p)
        {
            first = p.first;
            second = p.second;
            return *this;
        }

        // NON-MEMBER FUNCTIONS
        friend pair<K,V>  make_pair(K key, V value)
        {
            return pair<K, V>(key, value);
        }

        friend bool         operator==(const pair<T1,T2>& x, const pair<T1,T2>& y)
        {
            
        }
        friend bool         operator!=(const pair<T1,T2>& x, const pair<T1,T2>& y)
        {
            
        }
        friend bool         operator<(const pair<T1,T2>& x, const pair<T1,T2>& y)
        {
            
        }
        friend bool         operator<=(const pair<T1,T2>& x, const pair<T1,T2>& y)
        {
            
        }
        friend bool         operator>(const pair<T1,T2>& x, const pair<T1,T2>& y)
        {
            
        }
        friend bool         operator>=(const pair<T1,T2>& x, const pair<T1,T2>& y)
        {
            
        }
    };

    template<class Key, class T, class Compare=std::less<Key>, class Allocator=std::allocator<pair<const Key, T> > >
    class value_compare
    {
    public:
        typedef bool    result_type;
        typedef T       first_argument_type;
        typedef T       second_argument_type;

    private:
        Compare         comp;

    protected:
        value_compare(Compare c) : comp(c) {}
    
    public:
        bool    operator()(const T& x, const T& y) const
        {
            return comp(x.first_argument_type, y.first_argument_type);
        }
    };

    template <class Key, class T, class Compare=std::less<Key>, class Allocator=std::allocator<std::pair<const Key, T> > >
    class map
    {
    public:
        typedef Key                                key_type;
        typedef T                                  mapped_type;
        typedef pair<const key_type, mapped_type>  value_type;
        typedef size_t                             size_type;
        typedef std::ptrdiff_t                     difference_type;
        typedef Compare                            key_compare;
        typedef Allocator                          allocator_type;
        typedef value_type&                        reference;
        typedef const value_type&                  const_reference;
        typedef value_type*                        pointer;
        typedef const value_type*                  const_pointer;
        typedef node<key_type, mapped_type>        node_type;
        typedef typename allocator_type::template  rebind<node_type>::other node_allocator_type;

    private:
        allocator_type      _allocator;
        node_allocator_type _node_allocator;
        key_compare         _comp;
        node_type           _root;
        size_type           _size;
    
        void    insertNode(K _k, V _v)
        {
            node<K, V> newNode = _node_allocator.allocate(1);
            if (_root == NULL)
            {
                _root = newNode;
                root.black = true;
                ++_size;
            }
            else
            {
                insertNode(_root, newNode);
                ++_size;
            }
        }
    public:
        // MEMBER FUNCTIONS
        map();
        map(const key_compare& comp, const allocator_type& alloc=allocator_type());
        map(const map& other);
        ~map();
    };

    template<class Key, class T, class Compare, class Alloca>
    map<Key, T, Compare, Alloca>::map(const key_compare& comp, const allocator_type& alloc)
    : _allocator(alloc), _comp(comp), _root(NULL), _size(0)
    { 
    }
    
    template<class Key, class T, class Compare, class Alloca>
    map<Key, T, Compare, Alloca>::map(const map& other)
    : _allocator(other._allocator), _node_allocator(other._node_allocator), _comp(other._comp), _root(other._root), _size(other._size)
    {
        
    }
} // namespace ft