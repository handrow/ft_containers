/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 02:20:43 by handrow           #+#    #+#             */
/*   Updated: 2021/04/15 09:09:00 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>

namespace ft
{
    template<typename T>
    struct   allocator
    {
        typedef T                   value_type;
        typedef value_type*         pointer;
        typedef value_type&         reference;
        typedef const value_type*   const_pointer;
        typedef const value_type&   const_reference;
        typedef size_t              size_type;
        typedef ptrdiff_t           difference_type;

        template<class U>
        struct  rebind { typedef allocator<U> other; };


        pointer         address(reference x) const                          { return &x; }
        const_pointer   address(const_reference x) const                    { return &x; }
        pointer         allocate(size_type n)                               { return static_cast<pointer>(::operator new(n * sizeof(value_type))); }
        void            deallocate(pointer p, size_type n)                  { ::operator delete(p, &n); }
        size_type       max_size() const throw()                            { return static_cast<size_type>(-1) / sizeof(value_type); }
        void            construct(pointer p, const_reference val)           { new((void *)p) value_type(val); }
        void            destroy(pointer p)                                  { p->~value_type(); }
    };

    template<class T1, class T2>
    bool operator==(const allocator<T1>&, const allocator<T2>&) throw()     { return true; }

    template<class T1, class T2>
    bool operator!=(const allocator<T1>&, const allocator<T2>&) throw()     { return false; }

} // namespace ft