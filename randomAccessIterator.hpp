/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:07:43 by handrow           #+#    #+#             */
/*   Updated: 2021/03/02 17:31:01 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iostream>

namespace ft
{

    template<typename T> 
    class   iterator
    {
    public:
        typedef T                 value_type;
        typedef std::ptrdiff_t    difference_type;
        typedef T*                pointer;
        typedef T&                reference;

    private:
        pointer                   _ptr;

    public:
        iterator()                      : _ptr(NULL) { }
        iterator(const iterator& src)   : _ptr(src._ptr) { }
        iterator(const pointer ptr)     : _ptr(ptr) { }
        ~iterator() { }

        iterator&   operator=(const pointer ptr)            { _ptr = ptr; return *this; }
        iterator&   operator=(const iterator& src)          { _ptr = src._ptr; return *this; }
        reference   operator*() const                       { return *_ptr; }
        pointer     operator->()                            { return _ptr; }
        reference   operator[]( difference_type n ) const   { return  _ptr[n]; }
        iterator    operator+(difference_type n) const      { return iterator(_ptr + n); }
        iterator&   operator++()                            { ++_ptr; return *this; }
        iterator    operator++(int)                         { return iterator(_ptr++); }
        iterator&   operator+=(difference_type n)           { _ptr += n; return *this; }
        iterator    operator-(difference_type n) const      { return iterator(_ptr - n); }
        iterator&   operator--()                            { --_ptr; return *this; }
        iterator    operator--(int)                         { return iterator(_ptr--); }
        iterator&   operator-=(difference_type n)           { _ptr -= n; return *this; }


        friend bool             operator!=(const iterator& lhs, const iterator& rhs) 
        {
            return lhs._ptr != rhs._ptr;
        }

        friend bool             operator==(const iterator& lhs, const iterator& rhs)
        {
            return lhs._ptr == rhs._ptr; 
        }

        friend bool             operator>=(const iterator& lhs, const iterator& rhs)
        {
            return lhs._ptr >= rhs._ptr;
        }

        friend bool             operator<=(const iterator& lhs, const iterator& rhs)
        {
            return lhs._ptr <= rhs._ptr;    
        }

        friend bool             operator>(const iterator& lhs, const iterator& rhs)
        {
            return lhs._ptr > rhs._ptr;
        }

        friend bool             operator<(const iterator& lhs, const iterator& rhs)
        {
            return lhs._ptr < rhs._ptr;
        }

        friend difference_type  operator-(const iterator& lhs, const iterator& rhs)
        {
            return lhs._ptr - rhs._ptr;
        }

        friend difference_type  operator+(const iterator& lhs, const iterator& rhs)
        {
            return lhs._ptr + rhs._ptr;
        }
    };

    template<class Iter> 
    class   reverse_iterator
    {
    public:
        typedef Iter                        value_type;
        typedef std::ptrdiff_t              difference_type;
        typedef typename Iter::pointer      pointer;
        typedef typename Iter::reference    reference;
        

    private:
        Iter                  _ptr;

    public:
        reverse_iterator()                              : _ptr(NULL) { }
        reverse_iterator(const reverse_iterator& src)   : _ptr(src._ptr) { }
        reverse_iterator(const Iter& ptr)               : _ptr(ptr) { }
        ~reverse_iterator() { }

       Iter                 base() const                            { return _ptr; }

        reverse_iterator&   operator=(const pointer ptr)            { _ptr = ptr; return *this; }
        reverse_iterator&   operator=(const reverse_iterator& src)  { _ptr = src._ptr; return *this; }
        reference           operator*() const                       { Iter tmp = _ptr; return *(--tmp); }
        pointer             operator->()                            { return _ptr; }
        reference           operator[]( difference_type n ) const   { return _ptr[n]; }
        reverse_iterator    operator+(difference_type n) const      { return reverse_iterator(_ptr - n); }
        reverse_iterator&   operator++()                            { --_ptr; return *this; }
        reverse_iterator    operator++(int)                         { return reverse_iterator(_ptr--); }
        reverse_iterator&   operator+=(difference_type n)           { _ptr -= n; return *this; }
        reverse_iterator    operator-(difference_type n) const      { return reverse_iterator(_ptr + n); }
        reverse_iterator&   operator--()                            { ++_ptr; return *this; }
        reverse_iterator    operator--(int)                         { return reverse_iterator(_ptr++); }
        reverse_iterator&   operator-=(difference_type n)           { _ptr += n; return *this; }


        friend bool             operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs)
        {
            return lhs._ptr != rhs._ptr;
        }

        friend bool             operator==(const reverse_iterator& lhs, const reverse_iterator& rhs)
        {
            return lhs._ptr == rhs._ptr;
        }

        friend bool             operator>=(const reverse_iterator& lhs, const reverse_iterator& rhs)
        {
            return lhs._ptr >= rhs._ptr;
        }

        friend bool             operator<=(const reverse_iterator& lhs, const reverse_iterator& rhs)
        {
            return lhs._ptr <= rhs._ptr;
        }

        friend bool             operator>(const reverse_iterator& lhs, const reverse_iterator& rhs)
        {
            return lhs._ptr > rhs._ptr;
        }

        friend bool             operator<(const reverse_iterator& lhs, const reverse_iterator& rhs)
        {
            return lhs._ptr < rhs._ptr;
        }

        friend difference_type  operator-(const reverse_iterator& lhs, const reverse_iterator& rhs)
        {
            return lhs._ptr + rhs._ptr;
        }

        friend difference_type  operator+(const reverse_iterator& lhs, const reverse_iterator& rhs)
        {
            return lhs._ptr - rhs._ptr;
        }
        
    };
} // namespace ft