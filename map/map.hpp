/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:25:19 by handrow           #+#    #+#             */
/*   Updated: 2021/04/26 16:48:04 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "../avl_tree/avl_tree.hpp"
#include "map_iterator.hpp"
#include "../algorithm.hpp"

namespace ft
{
    template<class K, class V>
    struct pair
    {
        typedef K       first_type;
        typedef V       second_type;
        
        first_type      first;
        second_type     second;

        // MEMBER FUNCTIONS
        pair()  : first(), second() {}
        pair(first_type const& key, second_type const& val) 
        : first(key), second(val) {}
        template< class U1, class U2 >
        pair(const pair<U1, U2>& p) 
        : first(p.first), second(p.second) {}
        pair&    operator=(const pair& other)
        {
            first = other.first;
            second = other.second;
            return *this;
        }

        // NON-MEMBER FUNCTIONS

        friend bool         operator==(const pair& x, const pair& y)
        {
            return x.first == y.first && x.second == y.second;
        }

        friend bool         operator!=(const pair& x, const pair& y)
        {
            return !(x == y);
        }

        friend bool         operator<(const pair& x, const pair& y)
        {
            return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
        }

        friend bool         operator<=(const pair& x, const pair& y)
        {
            return !(y < x);
        }

        friend bool         operator>(const pair& x, const pair& y)
        {
            return y < x;
        }

        friend bool         operator>=(const pair& x, const pair& y)
        {
            return !(x < y);
        }
    };

    template<class Key, class T, class Compare=ft::less<Key>, class Allocator=ft::allocator<pair<const Key, T> > >
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

    template <class Key, class T, class Compare=less<Key>, class Allocator=ft::allocator<pair<const Key, T> > >
    class map
    {
    public:
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef ft::pair<const key_type, mapped_type>   value_type;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef Compare                                 key_compare;
        typedef Allocator                               allocator_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef value_type*                             pointer;
        typedef const value_type*                       const_pointer;
        typedef AVLtree<value_type, key_compare>        tree_type;
        typedef typename tree_type::NodeType            node_type;
        typedef typename allocator_type::template       rebind<node_type>::other node_allocator_type;

        typedef typename tree_type::iterator            tree_iter;
        typedef map_iterator<tree_iter>                 iterator;
        typedef map_const_iterator<tree_iter>           const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

        typedef ft::pair<iterator, bool>                insert_result;
        
    private:
        tree_type           _tree;
        size_type           _size;

    public:
        // MEMBER FUNCTIONS
        map() {} // doesnt work without it
        map(const key_compare& comp, const allocator_type& alloc=allocator_type());
        // template<class Iterator>
        // map(Iterator first, Iterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type());    
        map(const map& other);
        ~map() {}

        map&    operator=(const map& other)                     { _tree.operator=(other); return *this; }
        
        // ITERATORS
        iterator                            begin()             { return iterator(_tree.begin()); }
        iterator                            end()               { return iterator(_tree.end()); }

        const_iterator                      begin() const       { return iterator(_tree.begin()); }
        const_iterator                      end() const         { return iterator(_tree.end()); }

        reverse_iterator                    rbegin()            { return reverse_iterator(iterator(_tree.end())); }
        reverse_iterator                    rend()              { return reverse_iterator(iterator(_tree.begin())); }

        const_reverse_iterator              rend() const        { return reverse_iterator(iterator(_tree.end())); }
        const_reverse_iterator              rbegin() const      { return reverse_iterator(iterator(_tree.end())); }

        // CAPACITY
        bool                                empty() const       { return !_size; }
        size_type                           size() const        { return _size; }
        size_type                           max_size() const    { return _tree._node_alloc.max_size(); }

        // MODIFIERS
        void                                clear();
        insert_result                       insert(const value_type& value);
        iterator                            insert(iterator hint, const value_type& value);
        template<class Iterator> typename enable_if< is_iterator<Iterator>::value , void >
        ::type                              insert(Iterator first, Iterator last);
        void                                erase(iterator pos);
        void                                erase(iterator first, iterator last);
        size_type                           erase(const key_type& key);
        // void                                swap(map& other);

        // LOOKUP
        size_type                           count(const key_type& key) const;
        iterator                            find(const key_type& key);
        const_iterator                      find(const key_type& key) const;
        // pair<iterator,iterator>             equal_range(const key_type& key);
        // pair<const_iterator,const_iterator> equal_range(const key_type& key) const;
        // iterator                            lower_bound(const key_type& key);
        // const_iterator                      lower_bound(const key_type& key);
        // iterator                            upper_bound(const key_type& key);
        // const_iterator                      upper_bound(const key_type& key);
        
        // // OBSERVES
        // key_compare                         key_comp() const;
        // value_compare                       value_comp() const;
        value_type  make_pair(key_type key, mapped_type value)
        {
            return ft::pair<key_type, mapped_type>(key, value);
        }
        
    };

    template <class K, class T, class C, class A>
    map<K, T, C, A>::map(const key_compare& comp, const allocator_type& alloc)
    : _tree(comp, alloc)
    , _size(0)
    {
    }

    template <class K, class T, class C, class A>
    map<K, T, C, A>::map(const map& other)
    : _tree(other._tree)
    , _size(other._size)
    {
    }

    template <class K, class T, class C, class A>
    void    map<K, T, C, A>::clear()
    {
        _tree._root = tree_type::_cleanup_tree(_tree._root, _tree._data_alloc, _tree._node_alloc);
        _size = 0;
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::insert_result    map<K, T, C, A>::insert(const value_type& value)
    {
        iterator it(_tree.find_node(value));
        if (it != end())
            return insert_result(it, false);
        ++_size;
        return insert_result(it, true);
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::iterator  map<K, T, C, A>::insert(iterator hint, const value_type& value)
    {
        hint = iterator(_tree._root);
        iterator it(_tree.find_node(value));
        if (it != end())
            return it;
        ++_size;
        return _tree.insert(value);
    }

    template <class K, class T, class C, class A>
    template<class Iterator>
    typename enable_if< is_iterator<Iterator>::value , void >::type
    map<K, T, C, A>::insert(Iterator first, Iterator last)
    {
        while (first != last)
            insert(*first++);
    }

    template <class K, class T, class C, class A>
    void   map<K, T, C, A>::erase(iterator pos)
    {
        _tree.remove(*pos);
        --_size;
    }
    
    template <class K, class T, class C, class A>
    void    map<K, T, C, A>::erase(iterator first, iterator last)
    {
        while (first != last)
            _tree.remove(*first++);
    }
    
    template <class K, class T, class C, class A>
    size_t   map<K, T, C, A>::erase(const key_type& key)
    {
        iterator it(_tree.find_node(key));
        if (it == end())
            return 0;
        _tree.remove(key);
        --_size;
        return (1);
    }

    template <class K, class T, class C, class A>
    size_t   map<K, T, C, A>::count(const key_type& key) const
    {
        iterator it(_tree.find_node(key));
        if (it != end())
            return 1;
        return 0;
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::iterator  map<K, T, C, A>::find(const key_type& key)
    {
        return _tree.find_node(key);
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::const_iterator  map<K, T, C, A>::find(const key_type& key) const
    {
        return const_iterator(find(key));
    }
} // namespace ft