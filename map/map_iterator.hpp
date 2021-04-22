/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:11:42 by handrow           #+#    #+#             */
/*   Updated: 2021/04/22 23:02:42 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../avl_tree/avl_tree.hpp"
#include "../iterator.hpp"

namespace ft
{
    template<class TreeIter>
    class map_iterator_base : public iterator_base_tag
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
        map_iterator_base()                                 : _iter(NULL, NULL) {}
        map_iterator_base(const map_iterator_base& other)   : _iter(other._iter) {}
        map_iterator_base(const iter_type& tree_iter)       : _iter(tree_iter) {}

        map_iterator_base&   operator=(const map_iterator_base& other) { _iter = other._iter; return *this; }

        friend bool         operator==(const map_iterator_base& x, const map_iterator_base& y)
        {
            return x._iter.is_equal(y._iter);
        }

        friend bool         operator!=(const map_iterator_base& x, const map_iterator_base& y)
        {
            return !x._iter.is_equal(y._iter);
        }
    };

    template<typename TreeIter>
    struct map_iterator: public map_iterator_base<TreeIter>
    {
        typedef map_iterator_base<TreeIter>         base_type;
        typedef map_iterator                        this_type;

        typedef typename base_type::value_type      value_type;
        typedef typename base_type::const_reference reference;
        typedef typename base_type::const_pointer   pointer;
        typedef typename base_type::iter_type       iter_type;

        map_iterator() {}
        map_iterator(const this_type& other)        : base_type(other) {}
        map_iterator(const iter_type& tree_iter)    : base_type(tree_iter) {}

        this_type&   operator=(const this_type& other) { base_type::operator=(other); return *this; }

        reference    operator*() const       { return this->_iter.get_data_ref(); }
        pointer      operator->() const      { return &this->_iter.get_data_ref(); }

        this_type&   operator++()            { this->_iter.next(); return *this; }
        this_type    operator++(int)         { this_type tmp(*this); ++(*this); return tmp; }
        this_type&   operator--()            { this->_iter.prev(); return *this; }
        this_type    operator--(int)         { this_type tmp(*this); --(*this); return tmp; }

    };

    template<typename TreeIter>
    struct map_const_iterator: public map_iterator_base<TreeIter>
    {
        typedef map_iterator_base<TreeIter>         base_type;
        typedef map_const_iterator                  this_type;

        typedef typename base_type::value_type      value_type;
        typedef typename base_type::const_reference reference;
        typedef typename base_type::const_pointer   pointer;
        typedef typename base_type::iter_type       iter_type;

        map_const_iterator() {}
        map_const_iterator(const base_type& other) : base_type(other) {}
        map_const_iterator(const iter_type& tree_iter) : base_type(tree_iter) {}

        this_type&   operator=(const base_type& other) { base_type::operator=(other); return *this; }

        reference    operator*() const      { return this->_iter.get_data_const_ref(); }
        pointer      operator->() const     { return &this->_iter.get_data_const_ref(); }

        this_type&   operator++()           { this->_iter.next(); return *this; }
        this_type    operator++(int)        { this_type tmp(*this); ++(*this); return tmp; }
        this_type&   operator--()           { this->_iter.prev(); return *this; }
        this_type    operator--(int)        { this_type tmp(*this); --(*this); return tmp; }
    };

} // namespace ft
