/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:48:40 by handrow           #+#    #+#             */
/*   Updated: 2021/04/25 18:48:43 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template<class T>
    struct less
    {
        bool operator()(const T& x, const T& y) const
        {
            return x < y;
        }
    };

    template<class T>
    const T& max(const T& a, const T& b)
    {
        return (a > b) ? a : b;
    }

}
