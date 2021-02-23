/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:07:43 by handrow           #+#    #+#             */
/*   Updated: 2021/02/23 21:40:29 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include<cstddef>

template<typename T, typename Distance=ptrdiff_t> 
class   iterator
{
public:
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef T*          pointer;
    typedef T&          reference;

private:
    pointer             data;

public:
    iterator()                                 { data = NULL; }
    iterator(const iterator& src)              { data = src.data; }
    ~iterator()                                { }

    iterator&   operator=(const iterator& src) { data = src.data; return *this; }
    reference   operator*()                    { return data; }
    iterator&   operator++()                   { data++; return *this; }
    iterator    operator++(int);               { iterator tmp = *this; ++(*this); return tmp; }
    iterator&   operator--()                   { --data; return *this; }
    bool        operator>=()                    
    
};

