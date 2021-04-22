/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_helpers.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:48:25 by handrow           #+#    #+#             */
/*   Updated: 2021/04/25 18:48:27 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

    // integral constant type for a meta-magic
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

    template <bool, typename T>     struct enable_if {};
    template <typename T>           struct enable_if<true, T> { typedef T type; };

}