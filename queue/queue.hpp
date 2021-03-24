/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 06:19:03 by handrow           #+#    #+#             */
/*   Updated: 2021/03/24 07:51:26 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "../list/list.hpp"

namespace ft
{
    template< typename _T, typename _Allocator=std::allocator<_T>, class _Container=list<_T, _Allocator> > 
    class queue
    {
    public:
        typedef _Container                               container_type;
        typedef typename container_type::value_type      value_type;
        typedef typename container_type::reference       reference;
        typedef typename container_type::const_reference const_reference;
        typedef typename container_type::size_type       size_type;
    private:
        container_type  c;
    public:
        // MEMBER FUNCTIONS
        queue(const _Container& cont=_Container()) : c(cont) {}
        queue(const queue& other) : c(other.c) {}
        ~queue() {}

        queue&              operator=(const queue& other)   { c = other.c; return *this; }
        
        // ELEMENT ACCESS
        reference           front()                         { return c.begin(); }
        const_reference     front() const                   { return c.begin(); }
        reference           back()                          { return c.back(); }
        const_reference     back() const                    { return c.back(); }
        
        // CAPACITY
        bool                empty() const                   { return c.empty(); }
        size_type           size() const                    { return c.size(); }

        // MODIFIERS
        void                push(const value_type& value)   { c.push_back(value); }
        void                pop()                           { c.pop_back(); }
        void                swap(queue& other);

        // NON-MEMBER FUNCTIONS
        friend bool     operator==(const stack<_T, _Container>& x, const stack<_T, _Container>& y)
        {
            return x.c == y.c;
        }

        friend bool     operator!=(const queue<_T, _Container>& x, const queue<_T, _Container>& y)
        {
            return !(x == y);
        }

        friend bool     operator<(const queue<_T, _Container>& x, const queue<_T, _Container>& y)
        {
            return x.c < y.c;
        }

        friend bool     operator<=(const queue<_T, _Container>& x, const queue<_T, _Container>& y)
        {
            return !(y > x);
        }

        friend bool     operator>(const queue<_T, _Container>& x, const queue<_T, _Container>& y)
        {
            return y < x;
        }

        friend bool     operator>=(const queue<_T, _Container>& x, const queue<_T, _Container>& y)
        {
            return !(x < y);
        }

    };

    template< class T, class Alloca, class Container >
    void swap(queue<T,Alloca, Container>& x, queue<T,Alloca, Container>& y)
    {
        x.swap(y);
    }
    
} // namespace ft