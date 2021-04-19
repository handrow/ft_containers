/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:38:12 by handrow           #+#    #+#             */
/*   Updated: 2021/04/19 17:41:56 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../allocator.hpp"

namespace ft
{
    template < class Key, class Compare=std::less<Key>, class Allocator=ft::allocator<Key> >
    class set
    {
    public:
        typedef Key                 key_type;
        typedef Key                 value_type;
        typedef Allocator           allocator_type;
        typedef size_t              size_type;
        typedef ptrdiff_t           difference_type;
        typedef Compare             key_compare;
        typedef Compare             value_compare;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;
        typedef value_type*         pointer;
        typedef const value_type*   const_pointer;
        // typedef AVLtree<key_type, key_compare>  tree_type;

    private:
        allocator_type  _allocator;
        tree_type       _tree;
        pointer         _data;
        key_compare     _comp;
        size_type       _size;

    public:
        // MEMBER FUNCTIONS
        set() { }
        set(const Compare& comp, const allocator_type& alloc=allocator_type());
        set(const set& other);
        //set(iterator first, iterator last, const Compare& comp=Compare(), const allocator_type& alloc=allocator_type() );
        ~set() {}

        // ITERATORS
        // iterator                begin();
        // iterator                end();

        // const_iterator          begin() const;
        // const_iterator          end() const;

        // reverse_iterator        rbegin();
        // reverse_iterator        rend();
        
        // const_reverse_iterator  rbegin() const;
        // const_reverse_iterator  rend() const;

        // CAPACITY
        bool                                empty() const       { return !_size; }
        size_type                           size() const        { return _size; }
        size_type                           max_size() const    { return _allocator.max_size(); }

        // MODIFIERS
        // void                                clear();
        // // pair<iterator,bool>              insert(const value_type& value);
        // // iterator                         insert(iterator hint, const value_type& value);
        // // void                             insert(iterator first, iterator last);
        // void                                erase(iterator pos);
        // void                                erase(iterator first, iterator last);
        // size_type                           erase(const key_type& key);
        // void                                swap(set& other);

        // // LOOKUP
        // size_type                           count(const Key& key) const;
        // iterator                            find(const Key& key);
        // const_iterator                      find(const Key& key) const;

        // pair<iterator,iterator>             equal_range(const Key& key);
        // pair<const_iterator,const_iterator> equal_range(const Key& key) const;
        // iterator                            lower_bound(const Key& key);
        // const_iterator                      lower_bound(const Key& key) const;
        // iterator                            upper_bound(const Key& key);
        // const_iterator                      upper_bound(const Key& key) const;

        // // OBSERVERS
        // key_compare                         key_comp() const;
        // value_compare                       value_comp() const;
    };
    
    template<class T, class Comp, class Alloca>
    set<T, Comp, Alloca>::set(const key_compare& comp, const allocator_type& alloc)
    : _allocator(alloc), _data(NULL), _comp(comp), _size(0)
    {
    }

    
} // namespace ft