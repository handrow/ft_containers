/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:25:19 by handrow           #+#    #+#             */
/*   Updated: 2021/04/28 01:21:13 by handrow          ###   ########.fr       */
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
            return x.first < y.first
                || (x.first == y.first && x.second < y.second);
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

    template<class K, class V>
    ft::pair<K, V>  make_pair(K key, V value)
    {
        return ft::pair<K, V>(key, value);
    }

    template<class Pair, class KeyComp>
    struct pair_key_comp
    {
        KeyComp _kcomp;

        pair_key_comp(const KeyComp& kc = KeyComp()) : _kcomp(kc) {}

        bool operator()(const Pair& p1, const Pair& p2) const
        {
            return _kcomp(p1.first,p2.first);
        }
    };

    template <class Key, class T, class Compare=ft::less<const Key>, class Allocator=ft::allocator<pair<const Key, T> > >
    class map
    {
    public:
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef ft::pair<const key_type, mapped_type>   value_type;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef Compare                                 key_compare;
        typedef pair_key_comp<value_type, key_compare>  value_compare;
        typedef Allocator                               allocator_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef value_type*                             pointer;
        typedef const value_type*                       const_pointer;
        typedef AVLtree<value_type, value_compare>      tree_type;
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
        map(const key_compare& comp=key_compare(), const allocator_type& alloc=allocator_type());
        template<class Iterator>
        map(Iterator first, Iterator last, const key_compare& comp=key_compare(), const allocator_type& alloc=allocator_type());
        map(const map& other);
        ~map() {}
        
        mapped_type&                        operator[](const key_type& key);
        const mapped_type&                  operator[](const key_type& key) const;

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
        void                                swap(map& other);

        // LOOKUP
        size_type                           count(const key_type& key) const;
        iterator                            find(const key_type& key);
        const_iterator                      find(const key_type& key) const;
        pair<iterator,iterator>             equal_range(const key_type& key);
        pair<const_iterator,const_iterator> equal_range(const key_type& key) const;
        iterator                            lower_bound(const key_type& key);
        const_iterator                      lower_bound(const key_type& key) const;
        iterator                            upper_bound(const key_type& key);
        const_iterator                      upper_bound(const key_type& key) const;

        // OBSERVES
        key_compare                         key_comp() const
        {
            return value_comp()._kcomp;
        }

        value_compare                       value_comp() const
        {
            return _tree.get_compare();
        }

        template<typename __K, typename __T, typename C, typename A>
        friend bool    operator==(const map<__K, __T, C, A>& x, const map<__K, __T, C, A>& y);

        template<typename __K, typename __T, typename C, typename A>
        friend bool    operator!=(const map<__K, __T, C, A>& x, const map<__K, __T, C, A>& y);

        template<typename __K, typename __T, typename C, typename A>
        friend bool    operator<(const map<__K, __T, C, A>& x, const map<__K, __T, C, A>& y);

        template<typename __K, typename __T, typename C, typename A>
        friend bool    operator<=(const map<__K, __T, C, A>& x, const map<__K, __T, C, A>& y);

        template<typename __K, typename __T, typename C, typename A>
        friend bool    operator>(const map<__K, __T, C, A>& x, const map<__K, __T, C, A>& y);

        template<typename __K, typename __T, typename C, typename A>
        friend bool    operator>=(const map<__K, __T, C, A>& x, const map<__K, __T, C, A>& y);
    };

    template<typename K, typename T, typename C, typename A>
    bool    operator==(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
    {
        typename map<K, T, C, A>::const_iterator x_it = x.begin();
        typename map<K, T, C, A>::const_iterator x_end = x.end();
        typename map<K, T, C, A>::const_iterator y_it = y.begin();
        typename map<K, T, C, A>::const_iterator y_end = y.end();

        while (x_it != x_end && y_it != y_end && *x_it == *y_it)
        {
            ++x_it;
            ++y_it;
        }

        return x_it == x_end && y_it == y_end;
    }

    template<typename K, typename T, typename C, typename A>
    bool    operator!=(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
    {
        return !(x == y);
    }

    template<typename K, typename T, typename C, typename A>
    bool    operator<(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
    {

        typename map<K, T, C, A>::const_iterator x_it = x.begin();
        typename map<K, T, C, A>::const_iterator x_end = x.end();
        typename map<K, T, C, A>::const_iterator y_it = y.begin();
        typename map<K, T, C, A>::const_iterator y_end = y.end();

        while (x_it != x_end && y_it != y_end && *x_it == *y_it )
        {
            ++x_it;
            ++y_it;
        }
        return (x_it == x_end && y_it != y_end)
            || (x_it != x_end && y_it != y_end && *x_it < *y_it);
    }

    template<typename K, typename T, typename C, typename A>
    bool    operator<=(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
    {
        return !(x > y);
    }

    template<typename K, typename T, typename C, typename A>
    bool    operator>(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
    {
        return y < x;
    }

    template<typename K, typename T, typename C, typename A>
    bool    operator>=(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
    {
        return !(x < y);
    }

    template <class K, class T, class C, class A>
    map<K, T, C, A>::map(const key_compare& comp, const allocator_type& alloc)
    : _tree(value_compare(comp), alloc)
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
    template<class Iterator>
    map<K, T, C, A>::map(Iterator first, Iterator last, const C& comp, const allocator_type& alloc)
    : _tree(comp, alloc)
    , _size(0)
    {
        insert(first, last);
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::mapped_type&       map<K, T, C, A>::operator[](const key_type& key)
    {
        value_type tmp(key, mapped_type());
        iterator it(_tree.find_node(tmp));
        if (it == end())
            return insert(tmp).first->second;
        return it->second;
    }

    template <class K, class T, class C, class A>
    void    map<K, T, C, A>::clear()
    {
        _tree.clear();
        _size = 0;
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::insert_result    map<K, T, C, A>::insert(const value_type& value)
    {
        iterator it(_tree.find_node(value));
        if (it != end())
            return insert_result(it, false);
        ++_size;
        return insert_result(_tree.insert(value), true);
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
        value_type tmp(key, mapped_type());
        iterator it(_tree.find_node(tmp));
        if (it != end())
            return 1;
        return 0;
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::iterator  map<K, T, C, A>::find(const key_type& key)
    {
        value_type tmp(key, mapped_type());
        return _tree.find_node(tmp);
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::const_iterator  map<K, T, C, A>::find(const key_type& key) const
    {
        return const_iterator(find(key));
    }

    template <class K, class T, class C, class A>
    void    map<K, T, C, A>::swap(map& other)
    {
        _tree.swap(other._tree);
        size_t tmp = _size;
        _size = other._size;
        other._size = tmp;
    }

    template <class K, class T, class C, class A>
    pair<typename map<K, T, C, A>::iterator, typename map<K, T, C, A>::iterator>  map<K, T, C, A>::equal_range(const key_type& key)
    {
        return make_pair(lower_bound(key), upper_bound(key));
    }

    template <class K, class T, class C, class A>
    pair<typename map<K, T, C, A>::const_iterator, typename map<K, T, C, A>::const_iterator>  
    map<K, T, C, A>::equal_range(const key_type& key) const
    {
        return make_pair(lower_bound(key), upper_bound(key));
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::iterator          map<K, T, C, A>::lower_bound(const key_type& key)
    {
        iterator first = begin();
        iterator last = end();
        while (first != last)
        {
            if (!key_comp()(first->first, key))
                return first;
            ++first;
        }
        return last;
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::const_iterator    map<K, T, C, A>::lower_bound(const key_type& key) const
    {
        const_iterator first = begin();
        const_iterator last = end();
        while (first != last)
        {
            if (!key_comp()(first->first, key))
                return first;
            ++first;
        }
        return last;
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::iterator          map<K, T, C, A>::upper_bound(const key_type& key)
    {
        iterator first = this->begin();
        iterator last = this->end();
        while (first != last)
        {
            if (key_comp()(key, first->first))
                return first;
            ++first;
        }
        return last;
    }

    template <class K, class T, class C, class A>
    typename map<K, T, C, A>::const_iterator    map<K, T, C, A>::upper_bound(const key_type& key) const
    {
        const_iterator first = this->begin();
        const_iterator last = this->end();
        while (first != last)
        {
            if (key_comp()(key, first->first))
                return first;
            ++first;
        }
        return last;
    }
} // namespace ft