/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectionalIterator.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:36:14 by handrow           #+#    #+#             */
/*   Updated: 2021/03/26 19:30:40 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template<typename _T>
    struct  node_base
    {
        _T          data;
        node_base*  next;
        node_base*  prev;

        node_base(struct node_base* next_node, struct node_base* prev_node)
        : next(next_node), prev(prev_node) { }
    };

    template<typename _T>
    class  list_iterator
    {
    public:
        typedef node_base<_T>   node_type;
        typedef _T              value_type;
        typedef value_type*     pointer;
        typedef value_type&     reference;

        static node_type* node_ptr(const list_iterator& iterator) {
            return iterator._ptr;
        }

    private:
        node_type*               _ptr;

    public:

        list_iterator()                             : _ptr(NULL) { }
        list_iterator(const list_iterator& src)     : _ptr(src._ptr) { }
        list_iterator(node_type& other)             : _ptr(&other) { }
        list_iterator(node_type* other)             : _ptr(other) { }
        ~list_iterator() { }

        template < template <typename> class _ConstIter>
        operator _ConstIter<const value_type>() {
            return _ConstIter<const value_type>(*(node_base<const value_type>*)_ptr);
        }

        list_iterator&  operator=(const list_iterator& src)  { _ptr = src._ptr; return *this; }
        reference       operator*() const                    { return _ptr->data; }
        pointer         operator->() const                   { return &_ptr->data; }
        list_iterator&  operator++()                         { _ptr = _ptr->next; return *this; }
        list_iterator   operator++(int)                      { list_iterator tmp(*this); ++(*this); return tmp; }
        list_iterator&  operator--()                         { _ptr = _ptr->prev; return *this; }
        list_iterator   operator--(int)                      { list_iterator tmp = *this; _ptr = _ptr->prev; return tmp; }


        friend bool operator==(const list_iterator& _x, const list_iterator& _y)
        {
            return _x._ptr == _y._ptr;
        }
        
        friend bool operator!=(const list_iterator& _x, const list_iterator& _y)
        {
            return !(_x == _y);
        }
    };

    template<typename Iter>
    class  list_rev_iterator
    {
    public:
        typedef typename Iter::value_type  value_type;
        typedef typename Iter::pointer     pointer;
        typedef typename Iter::reference   reference;

    private:
        Iter        _iter;

    public:

        list_rev_iterator()                             : _iter(NULL) { }
        list_rev_iterator(const list_rev_iterator& src) : _iter(src._iter) { }
        //list_rev_iterator(_Node &other)               : _iter(&other) { }
        ~list_rev_iterator() { }

        Iter                base() const                            { return _iter; }
        list_rev_iterator&  operator=(const list_rev_iterator& src) { _iter = src._iter; return *this; }
        reference           operator*() const                       { return *_iter; }
        pointer             operator->() const                      { return &(*_iter); }
        list_rev_iterator&  operator++()                            { --_iter; return *this; }
        list_rev_iterator   operator++(int)                         {list_rev_iterator tmp(*this); --(*this); return tmp; }
        list_rev_iterator&  operator--()                            { ++_iter; return *this; }
        list_rev_iterator   operator--(int)                         {list_rev_iterator tmp(*this); ++(*this); return tmp; }

        friend bool         operator==(const list_rev_iterator& _x, const list_rev_iterator& _y)
        {
            return _x._iter == _y._iter;
        }
        friend bool         operator!=(const list_rev_iterator& _x, const list_rev_iterator& _y)
        {
            return _x._iter != _y._iter;
        }
        
    };
} // namespace ft