/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:07:43 by handrow           #+#    #+#             */
/*   Updated: 2021/02/24 21:41:10 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include<cstddef>

template<typename T> 
class   iterator
{
public:
    typedef T                 value_type;
    typedef std::ptrdiff_t    difference_type;
    typedef T*                pointer;
    typedef T&                reference;

private:
    pointer                   it;

public:
    iterator()                                          { it = NULL; }
    iterator(const pointer src)                         { *this = src; }
    ~iterator()                                         { }

    iterator&   operator=(const pointer src)            { it = src; return *this; }
    reference   operator*()                             { return *it; }
    pointer     operator->()                            { return *(&it); }
    iterator    operator+(difference_type n)            { iterator tmp = *this; tmp += n; return tmp; }
    iterator&   operator++()                            { std::cout << " AA ";it++; return *this; }
    iterator    operator++(int)                         { std::cout << " BB ";iterator tmp = *this; ++(*this);std::cout << " CC "; return tmp; }
    iterator&   operator+=(difference_type n)           { it += n; return *this; }
    iterator    operator-(difference_type n)            { iterator tmp = *this; tmp -= n; return tmp; }
    iterator&   operator--()                            { --it; return *this; }
    iterator    operator--(int)                         { iterator tmp = *this; --(*this); return tmp; }
    iterator&   operator-=(difference_type n)           { it -= n; return *this; }
    bool        operator!=(const iterator& src) const        { return this->it != src.it; }
    bool        operator==(const iterator& src) const    { return this->it == src.it; }
    
};

template<typename T>
class   reverse_iterator
{
public:
    typedef T                 value_type;
    typedef std::ptrdiff_t    difference_type;
    typedef T*                pointer;
    typedef T&                reference;

private:
    pointer                   revIt;

public:
    reverse_iterator()                      { revIt = NULL; }
    reverse_iterator(const pointer src)     { *this = src; }
    ~reverse_iterator()                     { }

    
};