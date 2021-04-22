/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:37:13 by handrow           #+#    #+#             */
/*   Updated: 2021/04/22 04:40:24 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../avl_tree/avl_tree.hpp"

namespace ft
{
    template<typename TreeIter>
    class set_iterator_base
    {
        public:
        typedef TreeIter                        iter_type;
        typedef typename iter_type::ValueType   value_type;
        typedef value_type&                     reference;
        typedef value_type*                     pointer;
        typedef const value_type&               const_reference;
        typedef const value_type*               const_pointer;

    protected:
        iter_type   _iter;

    public:
        set_iterator_base(const set_iterator_base& other)  : _iter(other._iter) {}
        set_iterator_base(const iter_type& tree_iter) : _iter(tree_iter) {}

        set_iterator_base&   operator=(const set_iterator_base& other) { _iter = other._iter; return *this; }

        friend bool     operator==(const set_iterator_base& x, const set_iterator_base& y)
        {
            return x._iter.is_equal(y._iter);
        }

        friend bool     operator!=(const set_iterator_base& x, const set_iterator_base& y)
        {
            return !x._iter.is_equal(y._iter);
        }
    };

    template<typename TreeIter>
    struct set_iterator: public set_iterator_base<TreeIter>
    {
        typedef set_iterator_base<TreeIter>         base_type;
        typedef set_iterator                        this_type;

        typedef typename base_type::value_type      value_type;
        typedef typename base_type::const_reference reference;
        typedef typename base_type::const_pointer   pointer;
        typedef typename base_type::iter_type       iter_type;

        set_iterator(const this_type& other) : base_type(other) {}
        set_iterator(const iter_type& tree_iter) : base_type(tree_iter) {}
        this_type&   operator=(const this_type& other) { base_type::operator=(other); return *this; }

        reference       operator*() const       { return this->_iter.get_data_ref(); }
        pointer         operator->() const      { return &this->_iter.get_data_ref(); }

        this_type&   operator++()       { this->_iter.next(); return *this; }
        this_type    operator++(int)    { this_type tmp(*this); ++(*this); return tmp; }
        this_type&   operator--()       { this->_iter.prev(); return *this; }
        this_type    operator--(int)    { this_type tmp(*this); --(*this); return tmp; }

    };

    template<typename TreeIter>
    struct set_const_iterator: public set_iterator_base<TreeIter>
    {
        typedef set_iterator_base<TreeIter>         base_type;
        typedef set_const_iterator                  this_type;

        typedef typename base_type::value_type      value_type;
        typedef typename base_type::const_reference reference;
        typedef typename base_type::const_pointer   pointer;
        typedef typename base_type::iter_type       iter_type;

        set_const_iterator(const base_type& other) : base_type(other) {}
        set_const_iterator(const iter_type& tree_iter) : base_type(tree_iter) {}
        this_type&   operator=(const base_type& other) { base_type::operator=(other); return *this; }

        reference     operator*() const       { return this->_iter.get_data_const_ref(); }
        pointer       operator->() const      { return &this->_iter.get_data_const_ref(); }

        this_type&   operator++()       { this->_iter.next(); return *this; }
        this_type    operator++(int)    { this_type tmp(*this); ++(*this); return tmp; }
        this_type&   operator--()       { this->_iter.prev(); return *this; }
        this_type    operator--(int)    { this_type tmp(*this); --(*this); return tmp; }
    };
    
} // namespace ft