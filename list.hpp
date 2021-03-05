/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:04:38 by handrow           #+#    #+#             */
/*   Updated: 2021/03/05 19:22:16 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "bidirectionalIterator.hpp"

namespace ft
{

    template< typename _T, typename _Allocator=std::allocator<_T> >
    class list
    {

    public:
        typedef _T                      value_type;
        typedef _Allocator              allocator_type;
        typedef size_t                  size_type;
        typedef std::ptrdiff_t          difference_type;
        typedef value_type&             reference;  // check if it is c++11
        typedef const value_type&       const_reference;
        typedef value_type*             pointer;
        typedef const value_type*       const_pointer;
        typedef node_base<value_type>   node;

        typedef list_iterator<value_type, node>         iterator;
        typedef const list_iterator<value_type, node>   const_iterator;

    private:
        allocator_type  allocator;       
        node            *_head; // begin
        node            *_tail; // end
        size_type       _size;
    public:
        
        // MEMBER FUNCTIONS
        list(const allocator_type& alloc=allocator_type()); // default
        //list(size_type count, const reference value = value_type(), const allocator_type& alloc = allocator_type()); // fill
        //list(iterator first, iterator last, const allocator_type& alloc = allocator_type()); // range
       // list(const list& other); // copy
        //~list();

        list&               operator=(const list& other);
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
    };

    template<typename T, typename Alloca>
    list<T, Alloca>::list(const allocator_type& alloc)
    : allocator(alloc), _head(NULL), _tail(NULL), _size(0)
    {
        _head = new node(NULL, NULL);
        _tail = _head;
    }

    template<typename T, typename Alloca>
    void    list<T, Alloca>::assign(size_type count, const_reference value)
    {
        ~list(); // does not work
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
        node *ptr = new node(_head, NULL);
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
    typename list<T, Alloca>::iterator      list<T, Alloca>::erase(iterator pos)
    {
        node    *ptr = pos->prev->next;
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        ++pos;
        delete ptr;
        _size--;
        return pos;
    }

    template<typename T, typename Alloca>
    typename list<T, Alloca>::iterator      list<T, Alloca>::erase(iterator first, iterator last)
    {
        iterator ptr;
        while (first != last)
            ptr = erase(*first++);
        return ptr;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_front(const_reference value)
    {
        node *ptr = new node(_head, NULL); // allocate(1) then construct
        ptr->data = value;
        _head->prev = ptr;
        _head = ptr;
        _size++;
    }
    
    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_back(const_reference value)
    {
        node    *ptr = new node(NULL, _tail);
        _tail->data = value;
        _tail->next = ptr;
        _tail = ptr;
        _size++;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::pop_front()
    {
        node    *ptr = _head; 
        _head = _head->next;
        delete ptr;
        _head->prev = NULL;
        _size--;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::pop_back()
    {
        node    *ptr = _tail;
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
} // namespace ft