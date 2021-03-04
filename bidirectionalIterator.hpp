/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectionalIterator.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:36:14 by handrow           #+#    #+#             */
/*   Updated: 2021/03/04 17:50:39 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template<typename _T>
    struct  node_base
    {
        _T                  data;
        struct node_base*   next;
        struct node_base*   prev;

        node_base(struct node_base* next_node, struct node_base* prev_node)
        : next(next_node), prev(prev_node) { }
    };

    template<typename _T, typename _Node>
    class  list_iterator
    {
    public:
        typedef _T              value_type;
        typedef value_type*     pointer;
        typedef value_type&     reference;

    private:
        _Node*                  _ptr;

    public:

        list_iterator()                             : _ptr(NULL) { }
        list_iterator(const list_iterator& src)     : _ptr(src._ptr) { }
        list_iterator(_Node &other)                 : _ptr(&other) { }
        ~list_iterator() { }

        list_iterator&  operator=(const list_iterator& src)  { _ptr = src._ptr; return *this; }
        reference       operator*() const                    { return _ptr->data; }
        _Node*          operator->() const                   { return _ptr; }
        list_iterator&  operator++()                         { _ptr = _ptr->next; return *this; }
        list_iterator   operator++(int)                      {list_iterator tmp(*this); ++(*this); return tmp; }
        list_iterator&  operator--()                         { _ptr = _ptr->prev; return *this; }
        list_iterator   operator--(int)                      {list_iterator tmp = *this; _ptr = _ptr->prev; return tmp; }
        

        friend bool operator==(const list_iterator& _x, const list_iterator& _y)
        {
            return _x._ptr == _y._ptr;
        }
        
        friend bool operator!=(const list_iterator& _x, const list_iterator& _y)
        {
            return !(_x == _y);
        }
    };
} // namespace ft