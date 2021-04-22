/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:48:32 by handrow           #+#    #+#             */
/*   Updated: 2021/04/25 18:48:35 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "type_helpers.hpp"

namespace ft {

    struct iterator_base_tag {};

    template <typename SomeType, bool is_iter = is_base<iterator_base_tag, SomeType>::result >
    struct is_iterator : public integral_constant<bool, is_iter> {};

    template<typename Iter>
    class  reverse_iterator : public iterator_base_tag
    {
    public:
        typedef Iter                            iter_type;
        typedef typename Iter::value_type       value_type;
        typedef typename Iter::reference        reference;
        typedef typename Iter::pointer          pointer;
        typedef ptrdiff_t                       difference_type;

        typedef reverse_iterator                this_type;

    protected:
        iter_type        _iter;

    public:

        template <class _IT, bool>
        operator reverse_iterator<_IT>() {
            return reverse_iterator<_IT>(this->_iter);
        }

        reverse_iterator()                                  : _iter(iter_type()) { }
        reverse_iterator(const this_type& src)              : _iter(src._iter) { }
        reverse_iterator(const iter_type& iter)             : _iter(iter) { }

        this_type&  operator=(const this_type& src)         { _iter = src._iter; return *this; }
        this_type&  operator=(const iter_type& iter)        { _iter = iter; return *this; }

        iter_type   base() const                            { return _iter; } // check

        reference   operator*() const                       { iter_type tmp = this->_iter; return *(--tmp); }
        pointer     operator->() const                      { iter_type tmp = this->_iter; return &(*(--tmp)); }
        reference   operator[](difference_type n) const     { return this->_iter[n]; }

        this_type&  operator++()                            { --_iter; return *this; }
        this_type   operator++(int)                         { this_type tmp(*this); ++(*this); return tmp; }
        this_type&  operator--()                            { ++_iter; return *this; }
        this_type   operator--(int)                         { this_type tmp(*this); --(*this); return tmp; }

        this_type   operator+(difference_type n) const      { return this_type(_iter - n); }
        this_type&  operator+=(difference_type n)           { _iter -= n; return *this; }
        this_type   operator-(difference_type n) const      { return this_type(_iter + n); }
        this_type&  operator-=(difference_type n)           { _iter += n; return *this; }

        friend bool         operator==(const this_type& _x, const this_type& _y)
        {
            return _x._iter == _y._iter;
        }
        friend bool         operator!=(const this_type& _x, const this_type& _y)
        {
            return _x._iter != _y._iter;
        }

        friend bool             operator>=(const this_type& x, const this_type& y)
        {
            return x._iter >= y._iter;
        }

        friend bool             operator<=(const this_type& x, const this_type& y)
        {
            return x._iter <= y._iter;
        }

        friend bool             operator>(const this_type& x, const this_type& y)
        {
            return x._iter > y._iter;
        }

        friend bool             operator<(const this_type& x, const this_type& y)
        {
            return x._iter < y._iter;
        }

        friend difference_type  operator-(const this_type& x, const this_type& y)
        {
            return x._iter + y._iter;
        }

        friend difference_type  operator+(const this_type& x, const this_type& y)
        {
            return x._iter - y._iter;
        }
    };

}