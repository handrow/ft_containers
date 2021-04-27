/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_helpers.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:48:25 by handrow           #+#    #+#             */
/*   Updated: 2021/04/27 21:33:39 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{

    // some struct that has static _T _val inside 
    template <typename _T, _T _val>
    struct integral_constant { const static _T value = _val; };

    // true and false type for a meta-magic
    struct true_type : public integral_constant<bool, true> {};
    struct false_type : public integral_constant<bool, false> {};

    // is same types
    template <typename A, typename B>
    struct is_same { const static bool result = false; };
    template <typename A>
    struct is_same<A, A> { const static bool result = true; };

    // is inherited from
    template <typename Base, typename Inheritor>
    class is_base
    {
    private:
        typedef struct { char _1; }             yes;
        typedef struct { char _1; char _2; }    no;

        static yes check(const Base&);
        static no  check(...);

    public:
        const static bool result = (sizeof(check(Inheritor())) == sizeof(yes));
    };

    template <typename Some>
    class is_pointer : public false_type {};
    template <typename Some>
    class is_pointer<Some*> : public true_type {};
    

    template <bool, typename T>     struct enable_if {};
    template <typename T>           struct enable_if<true, T> { typedef T type; };

    template <class AnyIterator>
    void print_collection(AnyIterator a, AnyIterator b)
    {
        while (a != b) std::cout << *a++ << " ";
        std::cout << "\n";
    }

}