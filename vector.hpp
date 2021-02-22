/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:06:14 by handrow           #+#    #+#             */
/*   Updated: 2021/02/22 22:10:43 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <exception>
#include <limits>
#include <iostream>

namespace ft
{
    template < typename _T, typename _Allocator=std::allocator<_T> >
    class vector
    {
    public:

        typedef _T                  value_type;
        typedef _Allocator          allocator_type;
        typedef	size_t              size_type;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;
        typedef value_type*         pointer;
        typedef const value_type*   const_pointer;
        typedef ptrdiff_t           difference_type;

    private:
        allocator_type              alloca;
        pointer                     data;
        size_type                   size;
        size_type                   capacity;

    public:
        // MEMBER FUNCTIONS
        vector(const allocator_type& alloc=allocator_type());                                           // default
        vector(size_type n, const reference val, const allocator_type& alloc=allocator_type());         // fill
        vector(iterator first, iterator last, const allocator_type& alloc=allocator_type());            // range
        vector(const vector& src);                                                                      // copy
        ~vector();

        vector&             operator=(const vector& src);
        void                assign(size_type num, const_reference val);

        // ELEMENT ACCESS
    
        reference           at(size_type pos);
        const_reference     at(size_type pos) const         { return at(pos); }
        reference           operator[](size_type pos)       { return data[pos]; }
        const_reference     operator[](size_type pos) const { return data[pos]; }
        reference           front()                         { return data[0]; }
        const_reference     front() const                   { return data[0]; }
        reference           back()                          { return data[size - 1]; }
        const_reference     back() const                    { return data[size - 1]; }

        // CAPACITY
    
        bool                empty() const                   { return !(size); }
        size_type           size() const                    { return size; }
        size_type           max_size() const;               { return alloca.max_size(); }
        void                reserve(size_type n);
        size_type           capacity() const                { return capacity; }

        // MODIFIERS

        void                clear();
        void                push_back(const_reference value);
        void                pop_back();
        void                resize(size_type count, value_type value = value_type());

        // NON-MEMBER FUNCTIONS

        friend bool         operator==(const vector<T,Alloca>& lhs, const vector<T,Alloca>& rhs);
        friend bool         operator!=(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs);
        friend bool         operator<(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs);
        friend bool         operator<=(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs);
        friend bool         operator>(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs);
        friend bool         operator>=(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs);
    };

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(const allocator_type& alloc)
    : alloca(alloc), data(NULL), size(0), capacity(0)
    {
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(size_type n, const reference val, const allocator_type& alloc)
    : alloca(alloc), data(alloc.allocate(n)), size(n), capacity(n)
    {
        for (size_type i = 0; i < n; ++i)
            alloca.construct(&data[i], val);
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(const vector& src)
    : alloca(src.alloc), data(src.data), size(src.size), capacity(src.capacity)
    {
        for (size_type i = 0; i < size; ++i)
            alloca.construct(&data[i], src.data[i]);
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::~vector()
    {
        if (data)
        {
            for (size_type i = 0; i < size; ++i)
                alloca.destroy(&data[i]);
            alloc.deallocate(data, size);
            data = NULL;
        }
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>&  vector<T, Alloca>::operator=(const vector& src)
    {
        this->~vector(); // delete this->data
        alloca = src.alloca;
        data = alloca.allocate(src.capacity); // create new data
        for (size_type i = 0; i < src.size; ++i)
            alloca.construct(&tmpData[i], src.data[i]);
        size = src.size;
        capacity = src.capacity;
        return *this;
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::assign(size_type num, const_reference val)
    {
        this->~vector();
        data = alloca.allocate(num);
        for (size_type i = 0; i < num; ++i)
            alloca.construct(&data[i], val);
        size = num;
        capacity = num;
    }

    template<typename T, typename Alloca>
    T&      vector<T, Alloca>::at(size_type pos)
    {
        if (pos > size)
            throw std::out_of_range("out of range");
        return data[pos];
    }

} // namespace ft
