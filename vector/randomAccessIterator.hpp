/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:07:43 by handrow           #+#    #+#             */
/*   Updated: 2021/04/27 02:37:20 by handrow          ###   ########.fr       */
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

    // template<class Iter> 
    // class   reverse_iterator
    // {
    // public:
    //     typedef Iter                        value_type;
    //     typedef std::ptrdiff_t              difference_type;
    //     typedef typename Iter::pointer      pointer;
    //     typedef typename Iter::reference    reference;
        

    // private:
    //     Iter                  _ptr;

    // public:
    //     reverse_iterator()                              : _ptr(NULL) { }
    //     reverse_iterator(const reverse_iterator& src)   : _ptr(src._ptr) { }
    //     reverse_iterator(const Iter& ptr)               : _ptr(ptr) { }
    //     ~reverse_iterator() { }

    //    Iter                 base() const                            { return _ptr; }

    //     reverse_iterator&   operator=(const pointer ptr)            { _ptr = ptr; return *this; }
    //     reverse_iterator&   operator=(const reverse_iterator& src)  { _ptr = src._ptr; return *this; }
    //     reference           operator*() const                       { Iter tmp = _ptr; return *(--tmp); }
    //     pointer             operator->()                            { return _ptr; }
    //     reference           operator[]( difference_type n ) const   { return _ptr[n]; }
    //     reverse_iterator    operator+(difference_type n) const      { return reverse_iterator(_ptr - n); }
    //     reverse_iterator&   operator++()                            { --_ptr; return *this; }
    //     reverse_iterator    operator++(int)                         { return reverse_iterator(_ptr--); }
    //     reverse_iterator&   operator+=(difference_type n)           { _ptr -= n; return *this; }
    //     reverse_iterator    operator-(difference_type n) const      { return reverse_iterator(_ptr + n); }
    //     reverse_iterator&   operator--()                            { ++_ptr; return *this; }
    //     reverse_iterator    operator--(int)                         { return reverse_iterator(_ptr++); }
    //     reverse_iterator&   operator-=(difference_type n)           { _ptr += n; return *this; }


    //     friend bool             operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs)
    //     {
    //         return lhs._ptr != rhs._ptr;
    //     }

    //     friend bool             operator==(const reverse_iterator& lhs, const reverse_iterator& rhs)
    //     {
    //         return lhs._ptr == rhs._ptr;
    //     }

    //     friend bool             operator>=(const reverse_iterator& lhs, const reverse_iterator& rhs)
    //     {
    //         return lhs._ptr >= rhs._ptr;
    //     }

    //     friend bool             operator<=(const reverse_iterator& lhs, const reverse_iterator& rhs)
    //     {
    //         return lhs._ptr <= rhs._ptr;
    //     }

    //     friend bool             operator>(const reverse_iterator& lhs, const reverse_iterator& rhs)
    //     {
    //         return lhs._ptr > rhs._ptr;
    //     }

    //     friend bool             operator<(const reverse_iterator& lhs, const reverse_iterator& rhs)
    //     {
    //         return lhs._ptr < rhs._ptr;
    //     }

    //     friend difference_type  operator-(const reverse_iterator& lhs, const reverse_iterator& rhs)
    //     {
    //         return lhs._ptr + rhs._ptr;
    //     }

    //     friend difference_type  operator+(const reverse_iterator& lhs, const reverse_iterator& rhs)
    //     {
    //         return lhs._ptr - rhs._ptr;
    //     }
        
    // };
} // namespace ft