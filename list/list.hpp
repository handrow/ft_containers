/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:04:38 by handrow           #+#    #+#             */
/*   Updated: 2021/03/22 20:58:57 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "bidirectionalIterator.hpp"
#include <iostream>
namespace ft
{

    template <typename T>
    bool        pred(const T &a , const T &b)
    {
        return a == b;
    }

    template <typename T>
    bool        cmp(const T &a, const T &b)
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
        typedef typename allocator_type::template rebind<node_type>::other  node_allocator;

        typedef list_iterator<value_type>         iterator;
        typedef list_iterator<const value_type>   const_iterator;

    private:
        allocator_type  allocator;
        node_allocator  node_alloca;       
        node_type*      _head; // begin
        node_type*      _tail; // end
        size_type       _size;
   
        // HELP FUNCTIONS
        size_type   countDist(const_iterator first, const_iterator last)
        {
            size_type i = 0;
            while (first != last)
            {
                i++;
                first++;
            }
            return i;
        }
        node_type*  createNewNode()
        {
            node_type *node = node_alloca.allocate(1);
            node->next = NULL;
            node->prev = NULL;
            return node;
        }
        void        pushFrontNode(node_type* node)
        {
            node->next = _head;
            node->prev = _tail;
            _head->prev = node;
            _tail->next = node;
            _head = node;
        }
        void        pushBackNode(node_type* node)
        {
            if (_head == _tail)
                pushFrontNode(node);
            else
            {
                _tail->prev->next = node;
                node->prev = _tail->prev;
                node->next = _tail;
                _tail->prev = node;
            }
        }
    public:

        // MEMBER FUNCTIONS
        list(const allocator_type& alloc=allocator_type()); // default
        list(size_type count, const_reference value = value_type(), const allocator_type& alloc = allocator_type()); // fill
        list(iterator first, iterator last, const allocator_type& alloc = allocator_type()); // range
        //list(const list& other); // copy
        //~list();

        list&               operator=(const list& other)
        {
            if (_size)
                clear();
            _head->next = _tail;
            _tail->prev = _head;
            _size = 0;
            assign(other.begin(), other.end());
            return *this;
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
        size_type           max_size() const    { return node_alloca.max_size(); }
        
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
        void                merge(list& other);
        template <class Compare>
        void                merge(list& other, Compare comp)
        {
            if (this == &other)
                return;
            iterator        firstThis = begin();
            iterator        lastThis = end();
            iterator        firstOther = other.begin();
            iterator        lastOther = other.end();

            while (firstThis != lastThis && firstOther != lastOther)
            {
                while (comp(*firstThis, *firstOther))
                    firstThis++;
                if (!comp(*firstThis, *firstOther))
                    splice(firstThis, other, firstOther);
                firstOther++;
            }
            if (firstOther != lastOther)
                splice(firstThis, other, firstThis, lastOther);
            // does not work
        }
        void                splice(const_iterator pos, list& other);
        void                splice(const_iterator pos, list& other, const_iterator it);
        void                splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
        void                remove(const_reference value);
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
        template<typename Compare>
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
    : allocator(alloc), _head(createNewNode()), _tail(_head), _size(0)
    {
    }

    template<typename T, typename Alloca>
    list<T, Alloca>::list(size_type count, const_reference value, const allocator_type& alloc)
    : allocator(alloc), _head(createNewNode()), _tail(_head), _size(0)
    {
        while (count-- > 0)
            push_back(value);
    }

    template<typename T, typename Alloca>
    list<T, Alloca>::list(iterator first, iterator last, const allocator_type& alloc)
    : allocator(alloc), _head(createNewNode()), _tail(_head), _size(countDist(first, last))
    {
        while (first != last)
            push_back(*first++);
    }

    // template<typename T, typename Alloca>
    // list<T, Alloca>::~list()
    // {
    //     // printf("A\n");
    //     // node_type* node;
    //     // for (size_type i = 0; i < _size; ++i)
    //     // {
    //     //     node = _head;
    //     //     _head = _head->next;
    //     //     allocator.destroy(&node->data);
    //     //     node_alloca.deallocate(node, 1);
    //     // }
    //     // _size = 0;
    //     // printf("A\n");
    // }
    
    template<typename T, typename Alloca>
    void        list<T, Alloca>::assign(size_type count, const_reference value)
    {
        clear();
        while (count-- > 0)
            push_back(value);
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::assign(iterator first, iterator last)
    {
        clear();
        while (first != last)
            push_back(*first++);
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::clear()
    {
        while (_size)
            pop_back();
    }
    
    template<typename T, typename Alloca>
    typename    list<T, Alloca>::iterator  list<T, Alloca>::insert(iterator pos, const_reference value)
    {
        if (pos == begin())
        {
            push_front(value);
            return begin();
        }
        node_type *ptr = node_alloca.allocate(1);
        node_type *post_insert = iterator::node_ptr(pos);
        ptr->data = value;
        ptr->prev = post_insert->prev;
        ptr->next = post_insert->prev->next;
        post_insert->prev->next = ptr;
        post_insert->prev = ptr;
        ++_size;
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
    typename    list<T, Alloca>::iterator  list<T, Alloca>::erase(iterator pos)
    {
        if (pos == begin())
        {
            pop_front();
            return begin();
        }
        node_type   *ptr = iterator::node_ptr(pos)->prev->next;
        node_type   *post_insert = ptr;
        post_insert->prev->next = post_insert->next;
        post_insert->next->prev = post_insert->prev;
        ++pos;
        delete ptr;
        --_size;
        return pos;
    }

    template<typename T, typename Alloca>
    typename    list<T, Alloca>::iterator  list<T, Alloca>::erase(iterator first, iterator last)
    {
        iterator ptr;
        while (first != last)
            ptr = erase(*first++);
        return ptr;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_front(const_reference value)
    {
  
        node_type* ptr = node_alloca.allocate(1);
        ptr->data = value;
        pushFrontNode(ptr);
        _size++;
    }
    
    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_back(const_reference value)
    {
        node_type    *ptr = node_alloca.allocate(1);
        _tail->data = value;
        _tail->next = ptr;
        _tail = ptr;
        _size++;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::pop_front()
    {
        if (_size)
        {
            node_type    *ptr = _head; 
            _head = _head->next;
            delete ptr;
            _head->prev = NULL;
            --_size;
        }
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::pop_back()
    {
        if (_size)
        {
            node_type    *ptr = _tail;
            _tail = _tail->prev;
            delete ptr;
            //allocator.destroy(&ptr->data);
            _tail->next = NULL;
            --_size;
        }
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
        list<T, Alloca> tmp = *this;
        *this = other;
        other = tmp;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::merge(list& other)
    {
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::splice(const_iterator pos, list& other)
    {
        splice(pos, other, other.begin(), other.end());
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::splice(const_iterator pos, list& other, const_iterator it)
    {
        const_iterator pre = it++;
        splice(pos, other, pre, it);
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last)
    {
            node_type* const post_insert = (node_type*)const_iterator::node_ptr(pos);
            node_type* const pre_insert = post_insert->prev;
            node_type* first_insert = (node_type*)const_iterator::node_ptr(first);
            node_type* end_insert = (node_type*)const_iterator::node_ptr(last);
            node_type* last_insert = end_insert->prev;

            if (first_insert != last_insert)
            {
                // recalculate sizes
                if (this != &other)
                {
                    size_type distance = countDist(first, last);
                    other._size -= distance;
                    _size += distance;
                }
                // unlink insert range from other
                if (other._head == first_insert)
                    other._head = end_insert;
                else
                    first_insert->prev->next = end_insert;
                end_insert->prev = first_insert->prev;
                // link first_insert and pre_insert
                if (pre_insert == NULL) // if pos == head
                    _head = first_insert;
                else
                    pre_insert->next = first_insert;
                first_insert->prev = pre_insert;
                // link last_insert and post_insert
                last_insert->next = post_insert;
                post_insert->prev = last_insert;
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

    template<typename T, typename Alloca>
    bool        operator<(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        typename list<T, Alloca>::const_iterator  x_first = x.begin();
        typename list<T, Alloca>::const_iterator  x_last = x.end();
        typename list<T, Alloca>::const_iterator  y_first = y.begin();

        for (; x_first != x_last; ++x_first, ++y_first)
        {
            if (*x_first == *y_first || cmp(*x_first, *y_first))
                return true;
            if (cmp(*y_first, *x_first))
                return false;
        }
        return false;
    }

    template<typename T, typename Alloca>
    bool        operator!=(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        return !(x == y);
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