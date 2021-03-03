/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:06:14 by handrow           #+#    #+#             */
/*   Updated: 2021/03/03 12:25:40 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <exception>
#include "randomAccessIterator.hpp"

namespace ft
{
    template < typename _T, typename _Allocator=std::allocator<_T> >
    class vector
    {
    public:

        typedef _T                                  value_type;
        typedef _Allocator                          allocator_type;
        typedef	size_t                              size_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef value_type*                         pointer;
        typedef const value_type*                   const_pointer;
        typedef ptrdiff_t                           difference_type;
        typedef iterator<value_type>                iterator;
        typedef const iterator                      const_iterator;
        typedef reverse_iterator<iterator>          reverse_iterator;
        typedef const reverse_iterator              const_reverse_iterator;

    private:
        allocator_type                              allocator;
        pointer                                     data;
        size_type                                   length;
        size_type                                   cap;

        // HELP FUNCTIONS
        size_type   __recommend(size_type new_size)
        {
            const size_type     ms = max_size();
            const size_type     _cap = capacity();
    
            if (new_size > ms)
                throw std::length_error("length error");
            if (_cap >= ms / 2)
                return ms;
            return std::max<size_type>(2 * _cap, new_size);
        }

    public:
        // MEMBER FUNCTIONS

        vector(const allocator_type& alloc=allocator_type());                                           // default
        vector(size_type n, const_reference val, const allocator_type& alloc=allocator_type());         // fill
        vector(iterator first, iterator last, const allocator_type& alloc=allocator_type());            // range
        vector(const vector& src);                                                                      // copy
        ~vector();

        vector&                 operator=(const vector& src);
        void                    assign(size_type num, const_reference val);
        void                    assign(iterator first, iterator last );

        // ITERATORS

        iterator                begin()                     { return data; }
        iterator                end()                       { return data + length; }

        const_iterator          begin() const               { return data; }
        const_iterator          end() const                 { return data + length; }

        reverse_iterator        rbegin()                    { return reverse_iterator(end()); }
        reverse_iterator        rend()                      { return reverse_iterator(begin()); }

        const_reverse_iterator  rbegin() const              { return data + length - 1; }
        const_reverse_iterator  rend() const                { return data - 1; }

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
        size_type           max_size() const                { return allocator.max_size(); }
        size_type           capacity() const                { return cap; }
        void                reserve(size_type new_cap); // check if reserve works correct

        // MODIFIERS

        void                clear();
        iterator            insert(iterator pos, const_reference value);
        void                insert(iterator pos, size_type count, const_reference value);
        void                insert(iterator pos, iterator first, iterator last);
        iterator            erase(iterator pos);
        iterator            erase(iterator first, iterator last);
        void                push_back(const_reference value);
        void                pop_back();
        void                resize(size_type count, value_type value = value_type());
        void                swap(vector& other);
    };

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(const allocator_type& alloc)
    : allocator(alloc), data(NULL), length(0), cap(0)
    {
        // std::cout << "DEFAULT CALLED" << std::endl;
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(size_type n, const_reference val, const allocator_type& alloc)
    : allocator(alloc), data(allocator.allocate(n)), length(n), cap(n)
    {
        for (size_type i = 0; i < n; ++i)
            allocator.construct(&data[i], val);
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(const vector& src)
    : allocator(src.allocator), data(NULL), length(src.length), cap(src.cap)
    {
        if (src.data != NULL)
            data = allocator.allocate(src.cap);
        for (size_type i = 0; i < length; ++i)
            allocator.construct(&data[i], src.data[i]);
    }
    
    template<typename T, typename Alloca>
    vector<T, Alloca>::vector(iterator first, iterator last, const allocator_type& alloc)
    : allocator(alloc), data(allocator.allocate(last - first)), length(last - first), cap(last - first)
    {
        assign(first, last);
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>::~vector()
    {
        if (data)
        {
            for (size_type i = 0; i < length; ++i)
                allocator.destroy(&data[i]);
            allocator.deallocate(data, length);
            data = NULL;
        }
    }

    template<typename T, typename Alloca>
    vector<T, Alloca>&  vector<T, Alloca>::operator=(const vector& src)
    {
        if (this != &src)
        {
            this->~vector(); // delete this->data
            allocator = src.allocator;
            data = allocator.allocate(src.cap); // create new data
            for (size_type i = 0; i < src.length; ++i)
                allocator.construct(&data[i], src.data[i]);
            length = src.length;
            cap = src.cap;
        }
        return *this;
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::assign(iterator first, iterator last)
    {
        clear();
        while (first != last)
            push_back(*first++);
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::assign(size_type num, const_reference val)
    {
        this->~vector();
        data = allocator.allocate(num);
        for (size_type i = 0; i < num; ++i)
            allocator.construct(&data[i], val);
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
            pointer tmpData = allocator.allocate(new_cap);
            memcpy(tmpData, data, length * sizeof(value_type));
            allocator.deallocate(data, cap);
            data = tmpData;
            cap = new_cap;
        }
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::clear()
    {
        if (data)
        {
            for (size_type i = 0; i < length; ++i)
                allocator.destroy(&data[i]);
        }
        length = 0;
    }

    // a c d e f g 
    // a c c d e f g : memcpy(data + iidx + 1, data + iidx, (length - iidx) * sizeof(elem_type));
    // a b c d e f g : data[iidx] = val; ++length;

    // a c d e f g
    // a c d e f g: tdata = alloca(tmpCap); memcpy(tmpDara, data, iidx * sizeof(elem_type));
    // a c c d e f g : memcpy(tmpData + iidx + 1, data + iidx, (length - iidx) * sizeof(elem_type));
    // a b c d e f g : tdata[iidx] = val; ++length;
    // deallocate; cap = tcap, data = tdata;
    template<typename T, typename Alloca>
    typename vector<T, Alloca>::iterator    vector<T, Alloca>::insert(iterator pos, const_reference value)
    {
        const size_type insertIdx = pos - begin();
    
        if (data == NULL && length == 0)
        {
            data = allocator.allocate(1);
            cap = 1;
        }
        else if (cap > length)
        {
            memmove(data + insertIdx + 1, data + insertIdx, (length - insertIdx) * sizeof(value_type));
            allocator.construct(&data[insertIdx], value);
            ++length;
        }
        else
        {
            const size_type tmpCap = __recommend(length + 1);
            pointer         tmpData = allocator.allocate(tmpCap);
            memcpy(tmpData, data, insertIdx * sizeof(value_type));
            memcpy(tmpData + insertIdx + 1, data + insertIdx, (length - insertIdx) * sizeof(value_type));
            allocator.construct(&tmpData[insertIdx], value);
            ++length;
            allocator.deallocate(data, cap);
            data = tmpData;
            cap = tmpCap;
        }
        return pos;
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::insert(iterator pos, size_type count, const_reference value)
    {
        size_type           insertIdx = pos - begin();
        size_type           num = count;

        if (data == NULL && length == 0)
        {
            data = allocator.allocate(1);
            cap = 1;
        }
        else if (cap >= length + num)
        {
            memmove(data + insertIdx + count, data + insertIdx, (length - insertIdx) * sizeof(value_type));
            while (count-- > 0)
                allocator.construct(&data[insertIdx++], value);
            length += num;
        }
        else
        {
            const size_type tmpCap = __recommend(length + count);
            pointer         tmpData = allocator.allocate(tmpCap);
            memcpy(tmpData, data, insertIdx * sizeof(value_type));
            memcpy(tmpData + insertIdx + count, data + insertIdx, (length - insertIdx) * sizeof(value_type));
            while (count-- > 0)
                allocator.construct(&tmpData[insertIdx++], value);
            length += num;
            allocator.deallocate(data, cap);
            data = tmpData;
            cap = tmpCap;
        }
    }

    // a b c d e f g h
    // a b c d b c d e f g h
    // a x x x b c d e f g h
    template<typename T, typename Alloca>
    void                vector<T, Alloca>::insert(iterator pos, iterator first, iterator last)
    {
        size_type size = last - first;
        size_type insertIdx = pos - begin();

        if (data == NULL && length == 0)
        {
            data = allocator.allocate(1);
            cap = 1;
        }

        else if (cap >= length + size)
        {
            memmove(data + insertIdx + size, data + insertIdx, (length - insertIdx) * sizeof(value_type));
            while (first != last)
                allocator.construct(&data[insertIdx++], *first++);
            length += size;
        }
        else
        {
            const size_type tmpCap = __recommend(length + size);
            pointer         tmpData = allocator.allocate(tmpCap);
            memcpy(tmpData, data, insertIdx * sizeof(value_type));
            memcpy(tmpData + insertIdx + size, data + insertIdx, (length - insertIdx) * sizeof(value_type));
            while (first != last)
                allocator.construct(&tmpData[insertIdx++], *first++);
            length += size;
            allocator.deallocate(data, cap);
            data = tmpData;
            cap = tmpCap;
        }
    }

    template<typename T, typename Alloca>
    typename vector<T, Alloca>::iterator    vector<T, Alloca>::erase(iterator pos)
    {
        size_type   eraseIdx = pos - begin();

        allocator.destroy(data + eraseIdx);
        memmove(data + eraseIdx, data + eraseIdx + 1, (length - eraseIdx - 1) * sizeof(value_type));
        --length;
        return pos;
    }

    template<typename T, typename Alloca>
    typename vector<T, Alloca>::iterator    vector<T, Alloca>::erase(iterator first, iterator last)
    {
        size_type   eraseIdx = first - begin();
        size_type   distance = last - first;

        for (iterator it = first; it != last; ++it)
            allocator.destroy(&(*it));

        memmove(data + eraseIdx, data + eraseIdx + distance, (length - eraseIdx - distance) * sizeof(value_type));
        length -= distance;
        return last;
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::push_back(const_reference value)
    {
        if (data == NULL && length == 0)
        {
            data = allocator.allocate(1);
            cap = 1;
        }
        else if (length == cap)
        {
            size_type   tmpCap = __recommend(length + 1);
            pointer     tmpData = allocator.allocate(tmpCap);
            memcpy(tmpData, data, length * sizeof(value_type));
            allocator.deallocate(data, cap);
            data = tmpData;
            cap = tmpCap;
        }
        allocator.construct(&data[length++], value);
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::pop_back()
    {
        allocator.destroy(&data[--length]);
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::resize(size_type count, value_type value)
    {
        reserve(count); // if reserve takes less than capacity it does nothing
        while (length > count)
            allocator.destroy(&data[--length]);
        while (count > length)
            allocator.construct(&data[length++], value);
    }

    template<typename T, typename Alloca>
    void    vector<T, Alloca>::swap(vector& other)
    {
        pointer         tmp_data = data;
        size_type       tmp_cap = cap;
        size_type       tmp_length = length;
        allocator_type  tmp_allocator = allocator;

        data = other.data;
        cap = other.cap;
        length = other.length;
        allocator = other.allocator;

        other.data = tmp_data;
        other.cap = tmp_cap;
        other.length = tmp_length;
        other.allocator = tmp_allocator;
    }

    template<typename T, typename Alloca>
    void    swap(vector<T, Alloca>& lhs, vector<T, Alloca>& rhs)
    {
        lhs.swap(rhs);
    }

    // NON-MEMBER FUNCTIONS

    template<typename T, typename Alloca>
    bool    operator==(const vector<T, Alloca>& x, const vector<T, Alloca>& y)
    {
        typename vector<T, Alloca>::iterator x_begin = x.begin();
        typename vector<T, Alloca>::iterator x_end = x.end();
        typename vector<T, Alloca>::iterator y_begin = y.begin();
        typename vector<T, Alloca>::iterator y_end = y.end();

        while (x_begin != x_end && y_begin != y_end)
        {
            if (*x_begin != *y_begin)
                return false;
            x_begin++;
            y_begin++;
        }
        if (x.size() != y.size())
            return false;
        return true; // check std::lexicographical compare
    }

    template<typename T, typename Alloca>
    bool    operator!=(const vector<T, Alloca>& x, const vector<T, Alloca>& y)
    {
        return !(x == y);
    }

    template<typename T, typename Alloca>
    bool    operator<(const vector<T, Alloca>& lhs, const vector<T, Alloca>& rhs)
    {
        
    }

    template<typename T, typename Alloca>
    bool    operator<=(const vector<T, Alloca>& lhs, const vector<T, Alloca>& rhs)
    {
        
    }

    template<typename T, typename Alloca>
    bool    operator>(const vector<T, Alloca>& lhs, const vector<T, Alloca>& rhs)
    {
        
    }

    template<typename T, typename Alloca>
    bool    operator>=(const vector<T, Alloca>& lhs, const vector<T, Alloca>& rhs)
    {
        
    }


} // namespace ft
