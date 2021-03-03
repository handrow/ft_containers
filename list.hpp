/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:04:38 by handrow           #+#    #+#             */
/*   Updated: 2021/03/03 21:49:40 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

namespace ft
{
    template<typename _T>
    struct  node_base
    {
        _T                  data;
        struct node_base*   next;
        struct node_base*   prev;

        node_base(struct node_base* next_node, struct node_base* prev_node)
        : next(next_node), prev(prev_node) { }
    };

    template< typename _T, typename _Allocator=std::allocator<_T> >
    class list
    {

    public:
        typedef _T                  value_type;
        typedef _Allocator          allocator_type;
        typedef size_t              size_type;
        typedef std::ptrdiff_t      difference_type;
        typedef value_type&         reference;  // check if it is c++11
        typedef const value_type&   const_reference;
        typedef value_type*         pointer;
        typedef const value_type*   const_pointer;
        typedef node_base<_T>       node;

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
       // ~list();

        list&   operator=(const list& other);
        void    assign(size_type count, const_reference value);
        
        // ELEMENT ACCESS
        reference           front();
        const_reference     front() const;
        reference           back();
        const_reference     back() const;


        // CAPACITY
        bool                empty() const       { return !_size; }
        size_type           size() const        { return _size; }
        size_type           max_size() const    { return allocator.max_size(); }
        
        // MODIFIERS
        void                push_front(const_reference value);
        void                push_back(const_reference value);
        void                pop_back();
    };

    template<typename T, typename Alloca>
    list<T, Alloca>::list(const allocator_type& alloc)
    : allocator(alloc), _head(NULL), _tail(NULL), _size(0)
    {
        _head = new node(NULL, NULL);
        _tail = _head;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_front(const_reference value)
    {
        node *ptr = new node(_head, NULL);
        ptr->data = value;
        // ptr->next = _head;
        // ptr->prev = NULL;
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
    void        list<T, Alloca>::pop_back()
    {
        node    *ptr = _tail;

        _tail = _tail->prev;
        delete ptr;
        _tail->next = NULL;
        _size--;
    }
} // namespace ft