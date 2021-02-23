/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:06:14 by handrow           #+#    #+#             */
/*   Updated: 2021/02/23 21:24:24 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <exception>
#include <limits>

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
        size_type                   length;
        size_type                   cap;

    public:
        // MEMBER FUNCTIONS

        vector(const allocator_type& alloc=allocator_type());                                           // default
        vector(size_type n, const_reference val, const allocator_type& alloc=allocator_type());         // fill
       // vector(iterator first, iterator last, const allocator_type& alloc=allocator_type());            // range
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
        reference           back()                          { return data[length - 1]; }
        const_reference     back() const                    { return data[length - 1]; }

        // CAPACITY
    
        bool                empty() const                   { return !(length); }
        size_type           size() const                    { return length; }
        size_type           max_size() const                { return alloca.max_size(); }
        size_type           capacity() const                { return cap; }
        void                reserve(size_type new_cap);

        // MODIFIERS

        void                clear();
        void                push_back(const_reference value);
        void                pop_back();
        void                resize(size_type count, value_type value = value_type());

        // NON-MEMBER FUNCTIONS

        friend bool         operator==(const vector& lhs, const vector& rhs);
        friend bool         operator!=(const vector& lhs, const vector& rhs);
        friend bool         operator<(const vector& lhs, const vector& rhs);
        friend bool         operator<=(const vector& lhs, const vector& rhs);
        friend bool         operator>(const vector& lhs, const vector& rhs);
        friend bool         operator>=(const vector& lhs, const vector& rhs);
    };

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(const allocator_type& alloc)
    : alloca(alloc), data(NULL), length(0), cap(0)
    {
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(size_type n, const_reference val, const allocator_type& alloc)
    : alloca(alloc), data(alloc.allocate(n)), length(n), cap(n)
    {
        for (size_type i = 0; i < n; ++i)
            alloca.construct(&data[i], val);
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(const vector& src)
    : alloca(src.alloc), data(src.data), length(src.length), cap(src.cap)
    {
        for (size_type i = 0; i < length; ++i)
            alloca.construct(&data[i], src.data[i]);
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::~vector()
    {
        if (data)
        {
            for (size_type i = 0; i < length; ++i)
                alloca.destroy(&data[i]);
            alloca.deallocate(data, length);
            data = NULL;
        }
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>&  vector<T, Alloca>::operator=(const vector& src)
    {
        this->~vector(); // delete this->data
        alloca = src.alloca;
        data = alloca.allocate(src.cap); // create new data
        for (size_type i = 0; i < src.length; ++i)
            alloca.construct(&tmpData[i], src.data[i]);
        length = src.length;
        cap = src.cap;
        return *this;
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::assign(size_type num, const_reference val)
    {
        this->~vector();
        data = alloca.allocate(num);
        for (size_type i = 0; i < num; ++i)
            alloca.construct(&data[i], val);
        length = num;
        cap = num;
    }

    template<typename T, typename Alloca>
    T&      vector<T, Alloca>::at(size_type pos)
    {
        if (pos > length)
            throw std::out_of_range("out of range");
        return data[pos];
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::reserve(size_type new_cap)
    {
        if (new_cap > max_size())
            throw std::length_error("length error");

        if (new_cap > length)
        {
            pointer tmpData = alloca.allocate(new_cap);
            for (size_type i = 0; i < length; ++i)
                tmpData[i] = data[i];
            alloca.deallocate(data, cap);
            cap = new_cap;
        }
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::clear()
    {
        if (data)
        {
            for (size_type i = 0; i < length; ++i)
                alloca.destroy(&data[i]);
        }
        length = 0;
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::push_back(const_reference value)
    {
        if (length == cap)
        {
            size_type   ms = max_size();
            size_type   tmpCap = cap > (ms / 2) ? ms : cap * 2;
            pointer     tmpData = alloca.allocate(tmpCap);
            memcpy(tmpData, data, tmpCap);
            alloca.deallocate(data, cap);
        }
        alloca.construct(&data[length++], value);
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::pop_back()
    {
        alloca.destroy(&data[--length]);
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::resize(size_type count, value_type value)
    {
        reserve(count); // if reserve takes less than capacity it does nothing
        while (length > count)
            alloca.destroy(&data[--length]);
        while (count > length)
            alloca.construct(&data[length++], value);
    }

} // namespace ft
