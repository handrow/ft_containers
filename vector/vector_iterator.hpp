/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:07:43 by handrow           #+#    #+#             */
/*   Updated: 2021/04/27 20:17:54 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iostream>

#include "../iterator.hpp"

namespace ft
{

    template<typename T> 
    class   vector_iterator : public iterator_base_tag
    {
    public:
        typedef T                 value_type;
        typedef std::ptrdiff_t    difference_type;
        typedef T*                pointer;
        typedef T&                reference;

    private:
        pointer                   _ptr;

    public:
        vector_iterator()                               : _ptr(NULL) { }
        vector_iterator(const vector_iterator& src)     : _ptr(src._ptr) { }
        vector_iterator(pointer ptr)                    : _ptr(ptr) { }
        ~vector_iterator() { }

        vector_iterator&   operator=(const pointer ptr)            { _ptr = ptr; return *this; }
        vector_iterator&   operator=(const vector_iterator& src)   { _ptr = src._ptr; return *this; }
        reference   operator*() const                       { return *_ptr; }
        pointer     operator->()                            { return _ptr; }
        reference   operator[](difference_type n) const     { return  _ptr[n]; }
        vector_iterator    operator+(difference_type n) const      { return vector_iterator(_ptr + n); }
        vector_iterator&   operator++()                            { ++_ptr; return *this; }
        vector_iterator    operator++(int)                         { return vector_iterator(_ptr++); }
        vector_iterator&   operator+=(difference_type n)           { _ptr += n; return *this; }
        vector_iterator    operator-(difference_type n) const      { return vector_iterator(_ptr - n); }
        vector_iterator&   operator--()                            { --_ptr; return *this; }
        vector_iterator    operator--(int)                         { return vector_iterator(_ptr--); }
        vector_iterator&   operator-=(difference_type n)           { _ptr -= n; return *this; }


        friend bool             operator!=(const vector_iterator& lhs, const vector_iterator& rhs) 
        {
            return lhs._ptr != rhs._ptr;
        }

        friend bool             operator==(const vector_iterator& lhs, const vector_iterator& rhs)
        {
            return lhs._ptr == rhs._ptr; 
        }

        friend bool             operator>=(const vector_iterator& lhs, const vector_iterator& rhs)
        {
            return lhs._ptr >= rhs._ptr;
        }

        friend bool             operator<=(const vector_iterator& lhs, const vector_iterator& rhs)
        {
            return lhs._ptr <= rhs._ptr;    
        }

        friend bool             operator>(const vector_iterator& lhs, const vector_iterator& rhs)
        {
            return lhs._ptr > rhs._ptr;
        }

        friend bool             operator<(const vector_iterator& lhs, const vector_iterator& rhs)
        {
            return lhs._ptr < rhs._ptr;
        }

        friend difference_type  operator-(const vector_iterator& lhs, const vector_iterator& rhs)
        {
            return lhs._ptr - rhs._ptr;
        }
    };

} // namespace ft