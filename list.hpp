/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:04:38 by handrow           #+#    #+#             */
/*   Updated: 2021/03/16 20:45:10 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "bidirectionalIterator.hpp"

namespace ft
{
    template <typename T>
    bool pred(const T &a , const T &b)
    {
        return a == b;
    }

    template <typename T>
    bool cmp(const T &a, const T &b)
    {
        return a < b;
    }

    template< typename _T, typename _Allocator=std::allocator<_T> >
    class list
    {
    public:
        typedef _T                      value_type;
        typedef _Allocator              allocator_type;
        typedef size_t                  size_type;
        typedef std::ptrdiff_t          difference_type;
        typedef value_type&             reference;
        typedef const value_type&       const_reference;
        typedef value_type*             pointer;
        typedef const value_type*       const_pointer;
        typedef node_base<value_type>   node_type;

        typedef list_iterator<value_type>         iterator;
        typedef list_iterator<const value_type>   const_iterator;

    private:
        allocator_type  allocator;       
        node_type*      _head; // begin
        node_type*      _tail; // end
        size_type       _size;
    public:
        
        size_type   countDist(const_iterator first, const_iterator last)
        {
            size_type i = 0;
            while (first++ != last)
                i++;
            return i;
        }

        // MEMBER FUNCTIONS
        list(const allocator_type& alloc=allocator_type()); // default
        //list(size_type count, const reference value = value_type(), const allocator_type& alloc = allocator_type()); // fill
        //list(iterator first, iterator last, const allocator_type& alloc = allocator_type()); // range
       // list(const list& other); // copy
        //~list();

        list&               operator=(const list& other)
        {
            clear();
            _head->next = _tail;
            _tail->prev = _head;
            _size = 0;
            assign(other.begin(), other.end());
            return (*this);
        }
        void                assign(size_type count, const_reference value);
        void                assign(iterator first, iterator last);
        
        // ELEMENT ACCESS
        reference           front();
        const_reference     front() const;
        reference           back();
        const_reference     back() const;

        // ITERATORS
        iterator            begin()             { return *_head; }
        iterator            end()               { return *_tail; }

        const_iterator      begin() const       { return *_head; }
        const_iterator      end() const         { return *_tail; }

        // CAPACITY
        bool                empty() const       { return !_size; }
        size_type           size() const        { return _size; }
        size_type           max_size() const    { return allocator.max_size(); }
        
        // MODIFIERS
        void                clear();
        iterator            insert(iterator pos, const_reference value);
        void                insert(iterator pos, size_type count, const_reference value);
        void                insert(iterator pos, iterator first, iterator last);
        iterator            erase(iterator pos);
        iterator            erase(iterator first, iterator last);
        void                push_front(const_reference value);
        void                push_back(const_reference value);
        void                pop_front();
        void                pop_back();
        void                resize(size_type count, value_type value = value_type());
        void                swap(list& other);

        // OPERATIONS
        //void                merge(list& other);
        void                splice(const_iterator pos, list& other);
        //void                splice(const_iterator pos, list& other, const_iterator it);
        void                splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
        void                remove(const_reference value);
        // check remove_if
        template<class UnaryPredicate>
        void                remove_if(UnaryPredicate pred)
        {
            iterator    first = begin();
            iterator    last = end();
            
            while (first != last)
            {
                if (pred(*first))
                    first = erase(first);
                else
                    first++;
            }
        }

        void                reverse();
        void                unique();
        template<class BinaryPredicate>
        void                unique(BinaryPredicate p)
        {
            if (_size > 1)
            {
                iterator    i1 = begin();
                iterator    i2 = i1;

                while (++i1 != end())
                {
                    if (p(*i1,*i2))
                    {
                        erase(i1);
                        i1 = i2;
                    }
                    else
                        i2 = i1;
                }
            }
        }
        void                sort();
        template <typename Compare>
        void 				sort(Compare comp)
        {
            if (_size > 1)
            {
                iterator i1 = begin();
                iterator i2 = i1;
                iterator i3 = i2;

                while(i1 != end())
                {
                    i2 = i1;
                    i1++;
                    i3 = i1;
                    while(i1 != end() && !comp(*i2,*i1))
                    {
                        std::swap(*i1, *i2);
                        if (i2 == begin())
                            break ;
                        i1 = i2;
                        --i2;
                    }
                    i1 = i3;
                }
            }
        }
    };

    template<typename T, typename Alloca>
    list<T, Alloca>::list(const allocator_type& alloc)
    : allocator(alloc)
    , _head(new node_type(NULL, NULL))
    , _tail(_head)
    , _size(0)
    {
    }

    // template<typename T, typename Alloca>
    // list<T, Alloca>::~list()
    // {
    // }
    
    template<typename T, typename Alloca>
    void    list<T, Alloca>::assign(size_type count, const_reference value)
    {
        //~list(); // does not work
        while (count-- > 0)
            push_back(value);
    }

    template<typename T, typename Alloca>
    void    list<T, Alloca>::assign(iterator first, iterator last)
    {
        // here is destructor or clean
        while (first != last)
            push_back(*first++);
    }

    template<typename T, typename Alloca>
    void     list<T, Alloca>::clear()
    {
        while (_size)
            pop_back();
    }
    
    template<typename T, typename Alloca>
    typename list<T, Alloca>::iterator  list<T, Alloca>::insert(iterator pos, const_reference value)
    {
        if (pos == begin())
        {
            push_front(value);
            return begin();
        }
        node_type *ptr = new node_type(_head, NULL);
        ptr->data = value;
        ptr->prev = pos->prev;
        ptr->next = pos->prev->next;
        pos->prev->next = ptr;
        pos->prev = ptr;
        _size++;
        return *ptr; 
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::insert(iterator pos, size_type count, const_reference value)
    {
        for (size_type i = 0; i < count; ++i)
            insert(pos, value);
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::insert(iterator pos, iterator first, iterator last)
    {
        while (first != last)
            insert(pos, *first++);
    }
    
    template<typename T, typename Alloca>
    typename list<T, Alloca>::iterator  list<T, Alloca>::erase(iterator pos)
    {
        if (pos == begin())
        {
            pop_front();
            return begin();
        }
        node_type    *ptr = pos->prev->next;
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        ++pos;
        delete ptr;
        _size--;
        return pos;
    }

    template<typename T, typename Alloca>
    typename list<T, Alloca>::iterator  list<T, Alloca>::erase(iterator first, iterator last)
    {
        iterator ptr;
        while (first != last)
            ptr = erase(*first++);
        return ptr;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_front(const_reference value)
    {
        node_type *ptr = new node_type(_head, NULL); // allocate(1) then construct
        ptr->data = value;
        _head->prev = ptr;
        _head = ptr;
        _size++;
    }
    
    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_back(const_reference value)
    {
        node_type    *ptr = new node_type(NULL, _tail);
        _tail->data = value;
        _tail->next = ptr;
        _tail = ptr;
        _size++;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::pop_front()
    {
        node_type    *ptr = _head; 
        _head = _head->next;
        delete ptr;
        _head->prev = NULL;
        _size--;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::pop_back()
    {
        node_type    *ptr = _tail;
        _tail = _tail->prev;
        delete ptr;
        _tail->next = NULL;
        _size--;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::resize(size_type count, value_type value)
    {
        while (count > _size)
            push_back(value);
        while (count < _size)
            pop_back();
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::swap(list& other)
    {
        allocator_type  tmp_allocator = allocator;
        size_type       tmp_size = _size;   
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::splice(const_iterator pos, list& other)
    {
        if (!other.empty())
        {
            // pre_insert -> post_insert
            // pre_insert -> [begin_insert -> ... -> end_insert ] -> post_insert
            node_type* const post_insert = (node_type*)const_iterator::node_ptr(pos);
            node_type* const pre_insert = post_insert->prev;
            node_type* const other_tail = other._tail;
            node_type* const begin_insert = other._head;
            node_type* const end_insert = other._tail->prev;

            post_insert->prev = end_insert;
            if (pre_insert == NULL) // if post_insert was a _head
                _head = begin_insert;
            else
                pre_insert->next = begin_insert;
            
            begin_insert->prev = pre_insert;
            end_insert->next = post_insert;

            _size += other._size;
            other._head = other_tail;
            other._size = 0;
        }
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last)
    {
        if (!other.empty() && first != last)
        {
            node_type* const post_insert = (node_type*)const_iterator::node_ptr(pos);
            node_type* pre_insert = post_insert->prev;
            node_type* begin_insert = (node_type*)const_iterator::node_ptr(first);
            --last;
            node_type* end_insert = (node_type*)const_iterator::node_ptr(last);
            size_type insert_len = countDist(first, last);

            post_insert->prev = end_insert;
            if (pre_insert == NULL)
                _head = begin_insert;
            else
                pre_insert->next = begin_insert;
            
            other._size -= insert_len;
            _size += insert_len;
            
            begin_insert->prev->next = end_insert->next;
            end_insert->next->prev = begin_insert->prev;
            
            pre_insert->next = begin_insert;
            begin_insert->prev = pre_insert;
            pre_insert = end_insert->prev;
            end_insert->prev->next = post_insert;
        }
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::remove(const_reference value)
    {
        iterator first = begin();
        iterator last = end();

        while (first != last)
        {
            if (*first == value)
               first = erase(first);
            else
                first++;
        }
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::reverse()
    {
        iterator first = begin();
        iterator last = end();

        for (size_type i = 0; i < _size; i += 2)
            std::swap(*first++, *--last);
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::unique()
    {
    if (_size > 1)
    {
        iterator    i1 = begin();
        iterator    i2 = i1;

        while (++i1 != end())
        {
            if (*i1 == *i2)
            {
                erase(i1);
                i1 = i2;
            }
            else
                i2 = i1;
        }
    }
}

    template<typename T, typename Alloca>
    void       list<T, Alloca>::sort()
    {
        sort(cmp<T>); // WHY DOES IT WORK
    }

    template<typename T, typename Alloca>
    bool        operator==(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        if (x._size != y._size)
            return false;

        typename list<T, Alloca>::const_iterator  x_first = x.begin();
        typename list<T, Alloca>::const_iterator  x_last = x.end();
        typename list<T, Alloca>::const_iterator  y_first = y.begin();

        while (x_first != x_last)
        {
            if (*x_first++ != *y_first++)
                return false;
        }
        return true;
    }

    // template<typename T, typename Alloca>
    // bool        operator<(const list<T,Alloca>& x, const list<T,Alloca>& y)
    // {
    // }

    template<typename T, typename Alloca>
    bool        operator!=(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        return x == y ? false : true;
    }

    template<typename T, typename Alloca>
    bool        operator>(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        return y < x;
    }

    template<typename T, typename Alloca>
    bool        operator<=(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        return !(y < x);
    }

    template<typename T, typename Alloca>
    bool        operator>=(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        return !(x < y);
    }

    template<typename T, typename Alloca>
    void        swap(list<T,Alloca>& x, list<T,Alloca>& y)
    {
        x.swap(y);
    }

} // namespace ft