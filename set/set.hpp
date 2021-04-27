/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:38:12 by handrow           #+#    #+#             */
/*   Updated: 2021/04/27 20:45:10 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../allocator.hpp"
#include "../iterator.hpp"
#include "../algorithm.hpp"
#include "set_iterator.hpp"

namespace ft
{
    template < class Key, class Compare=ft::less<Key>, class Allocator=ft::allocator<Key> >
    class set
    {
    public:
        typedef Key                                     value_type;
        typedef Allocator                               allocator_type;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef Compare                                 value_compare;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef value_type*                             pointer;
        typedef const value_type*                       const_pointer;

        typedef AVLtree<value_type, value_compare>      tree_type;
        typedef typename tree_type::iterator            tree_iter;

        typedef set_iterator<tree_iter>                 iterator;
        typedef set_const_iterator<tree_iter>           const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef typename std::pair<iterator, bool>      insert_result;

    private:
        tree_type       _tree;
        size_type       _size;

    public:
        // MEMBER FUNCTIONS
        set(const Compare& comp=Compare(), const allocator_type& alloc=allocator_type());
        set(const set& other);
        template<typename Iterator>
        set(Iterator first, Iterator last, const Compare& comp=Compare(), const allocator_type& alloc=allocator_type());
        ~set() {}

        // ITERATORS
        iterator                begin()             { return iterator(_tree.begin()); }
        iterator                end()               { return iterator(_tree.end()); }

        const_iterator          begin() const       { return const_iterator(_tree.begin()); }
        const_iterator          end() const         { return const_iterator(_tree.end()); }

        reverse_iterator        rbegin()            { return reverse_iterator(iterator(_tree.end())); }
        reverse_iterator        rend()              { return reverse_iterator(iterator(_tree.begin())); }
        
        const_reverse_iterator  rbegin() const      { return reverse_iterator(const_iterator(_tree.end())); }
        const_reverse_iterator  rend() const        { return reverse_iterator(const_iterator(_tree.begin())); }

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
        size_type                           erase(const value_type& key);
        void                                swap(set& other);

        // LOOKUP
        size_type                           count(const value_type& key) const;
        iterator                            find(const value_type& key);
        const_iterator                      find(const value_type& key) const;

        std::pair<iterator, iterator>            equal_range(const value_type& key);
        std::pair<const_iterator,const_iterator> equal_range(const value_type& key) const;
        iterator                            lower_bound(const value_type& key);
        const_iterator                      lower_bound(const value_type& key) const;
        iterator                            upper_bound(const value_type& key);
        const_iterator                      upper_bound(const value_type& key) const;

        // OBSERVERS
        value_compare                       key_comp() const;
        value_compare                       value_comp() const;

        //NON-MEMBER FUNCTIONS
        template<typename T, typename C, typename A>
        friend bool    operator==(const set<T, C, A>& x, const set<T, C, A>& y);

        template<typename T, typename C, typename A>
        friend bool    operator!=(const set<T, C, A>& x, const set<T, C, A>& y);

        template<typename T, typename C, typename A>
        friend bool    operator<(const set<T, C, A>& x, const set<T, C, A>& y);

        template<typename T, typename C, typename A>
        friend bool    operator<=(const set<T, C, A>& x, const set<T, C, A>& y);

        template<typename T, typename C, typename A>
        friend bool    operator>(const set<T, C, A>& x, const set<T, C, A>& y);

        template<typename T, typename C, typename A>
        friend bool    operator>=(const set<T, C, A>& x, const set<T, C, A>& y);
    };

    template<typename T, typename C, typename A>
    bool    operator==(const set<T, C, A>& x, const set<T, C, A>& y)
    {
        typename set<T,C,A>::const_iterator x_it = x.begin();
        typename set<T,C,A>::const_iterator x_end = x.end();
        typename set<T,C,A>::const_iterator y_it = y.begin();
        typename set<T,C,A>::const_iterator y_end = y.end();

        while (x_it != x_end && y_it != y_end && *x_it == *y_it)
        {
            ++x_it;
            ++y_it;
        }

        return x_it == x_end && y_it == y_end;
    }

    template<typename T, typename C, typename A>
    bool    operator!=(const set<T, C, A>& x, const set<T, C, A>& y)
    {
        return !(x == y);
    }

    template<typename T, typename C, typename A>
    bool    operator<(const set<T, C, A>& x, const set<T, C, A>& y)
    {

        typename set<T,C,A>::const_iterator x_it = x.begin();
        typename set<T,C,A>::const_iterator x_end = x.end();
        typename set<T,C,A>::const_iterator y_it = y.begin();
        typename set<T,C,A>::const_iterator y_end = y.end();

        while (x_it != x_end && y_it != y_end && *x_it == *y_it )
        {
            ++x_it;
            ++y_it;
        }
        return (x_it == x_end && y_it != y_end)
            || (x_it != x_end && y_it != y_end && *x_it < *y_it);
    }

    template<typename T, typename C, typename A>
    bool    operator<=(const set<T, C, A>& x, const set<T, C, A>& y)
    {
        return !(x > y);
    }

    template<typename T, typename C, typename A>
    bool    operator>(const set<T, C, A>& x, const set<T, C, A>& y)
    {
        return y < x;
    }

    template<typename T, typename C, typename A>
    bool    operator>=(const set<T, C, A>& x, const set<T, C, A>& y)
    {
        return !(x < y);
    }
    
    template<class T, class Comp, class Alloca>
    set<T, Comp, Alloca>::set(const value_compare& comp, const allocator_type& alloc)
    : _tree(comp, alloc)
    , _size(0)
    {
    }

    template<class T, class Comp, class Alloca>
    set<T, Comp, Alloca>::set(const set& other)
    : _tree(other._tree)
    , _size(other._size)
    {
    }

    template<class T, class Comp, class Alloca>
    template <typename Iterator>
    set<T, Comp, Alloca>::set(Iterator first, Iterator last, const value_compare& comp, const allocator_type& alloc)
    : _tree(comp, alloc)
    , _size(0)
    {
        insert(first, last);
    }

    template<class T, class Comp, class Alloca>
    void   set<T, Comp, Alloca>::clear()
    {
        _tree.clear();
        _size = 0;
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::insert_result
    set<T, Comp, Alloca>::insert(const value_type& value)
    {
        iterator it(_tree.find_node(value));
        if (it != end()) // if element already here
            return insert_result(it, false);
        ++_size;
        return insert_result(_tree.insert(value), true);
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::iterator  set<T, Comp, Alloca>::insert(iterator hint, const value_type& value)
    {
        hint = iterator(_tree._root);
        iterator it(_tree.find_node(value));
        if (it != end())
            return it;
        ++_size;
        return _tree.insert(value);
    }

    template<class T, class Comp, class Alloca>
    template<class Iterator>
    typename enable_if< is_iterator<Iterator>::value , void >::type
    set<T, Comp, Alloca>::insert(Iterator first, Iterator last)
    {
        while (first != last)
            insert(*first++);
    }

    template<class T, class Comp, class Alloca>
    void   set<T, Comp, Alloca>::erase(iterator pos)
    {
        _tree.remove(*pos);
        --_size;
    }

    template<class T, class Comp, class Alloca>
    void    set<T, Comp, Alloca>::erase(iterator first, iterator last)
    {
        while (first != last)
        {
            _tree.remove(*first++);
            --_size;
        } 
    }

    template<class T, class Comp, class Alloca>
    size_t  set<T, Comp, Alloca>::erase(const value_type& key)
    {
        iterator it(_tree.find_node(key));
        if (it == end())
            return 0;
        _tree.remove(key);
        --_size;
        return (1);
    }

    template<class T, class Comp, class Alloca>
    size_t  set<T, Comp, Alloca>::count(const value_type& key) const
    {
        iterator it(_tree.find_node(key));
        if (it != end())
            return 1;
        return 0;
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::iterator         set<T, Comp, Alloca>::find(const value_type& key)
    {
        return _tree.find_node(key);
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::const_iterator   set<T, Comp, Alloca>::find(const value_type& key) const
    {
        return const_iterator(find(key));
    }

    template<class T, class Comp, class Alloca>
    void    set<T, Comp, Alloca>::swap(set& other)
    {
        _tree.swap(other._tree);
        size_t tmp = _size;
        _size = other._size;
        other._size = tmp;
    }

    template<class T, class Comp, class Alloca>
    std::pair<typename set<T, Comp, Alloca>::iterator, typename set<T, Comp, Alloca>::iterator>     
    set<T, Comp, Alloca>::equal_range(const value_type& key)
    {
        return std::make_pair(lower_bound(key), upper_bound(key));
    }

    template<class T, class Comp, class Alloca>
    std::pair<typename set<T, Comp, Alloca>::const_iterator, typename set<T, Comp, Alloca>::const_iterator>     
    set<T, Comp, Alloca>::equal_range(const value_type& key) const
    {
        return std::make_pair(lower_bound(key), upper_bound(key));
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::iterator         set<T, Comp, Alloca>::lower_bound(const value_type& key)
    {
        iterator first = begin();
        iterator last = end();
        while (first != last)
        {
            if (!key_comp()(*first, key))
                return first;
            ++first;
        }
        return last;
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::const_iterator   set<T, Comp, Alloca>::lower_bound(const value_type& key) const
    {
        const_iterator first = begin();
        const_iterator last = end();
        while (first != last)
        {
            if (!key_comp()(*first, key))
                return first;
            ++first;
        }
        return last;
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::iterator     set<T, Comp, Alloca>::upper_bound(const value_type& key)
    {
        iterator first = this->begin();
        iterator last = this->end();
        while (first != last)
        {
            if (key_comp()(key, *first))
                return first;
            ++first;
        }
        return last;
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::const_iterator   set<T, Comp, Alloca>::upper_bound(const value_type& key) const
    {
        const_iterator first = this->begin();
        const_iterator last = this->end();
        while (first != last)
        {
            if (key_comp()(key, *first))
                return first;
            ++first;
        }
        return last;
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::value_compare   set<T, Comp, Alloca>::key_comp() const
    {
        return _tree.get_compare();
    }

    template<class T, class Comp, class Alloca>
    typename set<T, Comp, Alloca>::value_compare   set<T, Comp, Alloca>::value_comp() const
    {
        return _tree.get_compare();
    }

    
} // namespace ft