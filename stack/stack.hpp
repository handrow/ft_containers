/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 04:02:55 by handrow           #+#    #+#             */
/*   Updated: 2021/03/26 22:24:32 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "../list/list.hpp"

namespace ft
{
    template< typename _T, class _Container=list<_T> >
    class stack
    {
    public:
        typedef  _Container                           container_type;	
        typedef typename _Container::value_type       value_type;
        typedef typename _Container::size_type        size_type;
        typedef typename _Container::reference        reference;
        typedef typename _Container::const_reference  const_reference;

    protected:
        container_type  c;

    public:
        // MEMBER FUNCTIONS
        stack(const _Container& cont=_Container()) : c(cont) {}
        stack(const stack& other) : c(other.c) {}
        ~stack() {}

        stack&          operator=(const stack& other)   { c = other.c; return *this; }

        // ELEMENT ACCESS
        reference       top()                           { return c.back(); }
        const_reference top() const                     { return c.back(); }

        // CAPACITY
        bool            empty() const                   { return c.empty(); }
        size_type       size() const                    { return c.size(); }

        // MODIFIERS
        void            push(const_reference value)     { c.push_back(value); }
        void            pop()                           { c.pop_back(); }
        void            swap(stack& other);////////////////


        friend bool     operator==(const stack<_T, _Container>& x, const stack<_T, _Container>& y)
        {
            return x.c == y.c;
        }

        friend bool     operator!=(const stack<_T, _Container>& x, const stack<_T, _Container>& y)
        {
            return !(x == y);
        }

        friend bool     operator<(const stack<_T, _Container>& x, const stack<_T, _Container>& y)
        {
            return x.c < y.c;
        }

        friend bool     operator<=(const stack<_T, _Container>& x, const stack<_T, _Container>& y)
        {
            return !(y > x);
        }

        friend bool     operator>(const stack<_T, _Container>& x, const stack<_T, _Container>& y)
        {
            return y < x;
        }

        friend bool     operator>=(const stack<_T, _Container>& x, const stack<_T, _Container>& y)
        {
            return !(x < y);
        }

    };
    template< class T, class Container >
    void swap(stack<T, Container>& x, stack<T, Container>& y)
    {
        x.swap(y);
    }
} // namespace ft

