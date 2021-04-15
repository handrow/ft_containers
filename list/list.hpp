/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:04:38 by handrow           #+#    #+#             */
/*   Updated: 2021/04/15 14:54:51 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "bidirectionalIterator.hpp"
#include <iostream>
#include "../allocator.hpp"
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

    template< typename _T, typename _Allocator=ft::allocator<_T> >
    class list
    {
    public:
        typedef _T                                  value_type;
        typedef _Allocator                          allocator_type;
        typedef size_t                              size_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef value_type*                         pointer;
        typedef const value_type*                   const_pointer;
        typedef node_base<value_type>               node_type;
        typedef typename allocator_type::template rebind<node_type>::other  node_allocator_type;

        typedef list_iterator<value_type>           iterator;
        typedef list_iterator<const value_type>     const_iterator;
        typedef list_rev_iterator<iterator>         reverse_iterator;
        typedef list_rev_iterator<const_iterator>   const_rev_iterator;

    private:
        allocator_type          _allocator;
        node_allocator_type     _node_allocator;       
        node_type*              _head;
        node_type*              _tail;
        size_type               _size;
   
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
            node_type *node = _node_allocator.allocate(1);
            node->next = NULL;
            node->prev = NULL;
            return node;
        }
        void        deleteNode(node_type* node)
        {
            _node_allocator.destroy(node);
            _node_allocator.deallocate(node, 1);
        }
        void        pushFrontNode(node_type* node)
        {
            node->next = _head;
            _head->prev = node;
            node->prev = NULL;
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
        list(const allocator_type& alloc=allocator_type());
        list(const list& other);
        list(size_type count, const_reference value = value_type(), const allocator_type& alloc = allocator_type());
        list(iterator first, iterator last, const allocator_type& alloc = allocator_type());
        ~list();

        list&               operator=(const list& other);
        void                assign(size_type count, const_reference value);
        template< typename Tp, template <typename> class InputIt >
        void                assign(InputIt<Tp> first, InputIt<Tp> last);
        
        // ELEMENT ACCESS
        reference           front()             { return _head->data; }
        const_reference     front() const       { return _head->data; }
        reference           back()              { return _tail->prev->data; }
        const_reference     back() const        { return _tail->prev->data; }

        // ITERATORS
        iterator            begin()             { return _head; }
        iterator            end()               { return _tail; }

        const_iterator      begin() const       { return reinterpret_cast<node_base<const value_type>*>(_head); }
        const_iterator      end() const         { return reinterpret_cast<node_base<const value_type>*>(_tail); }

        reverse_iterator    rbegin()            { return reverse_iterator(end()); }
        reverse_iterator    rend()              { return reverse_iterator(begin()); }

        const_rev_iterator  rbegin() const      { return const_rev_iterator(!_size ? _tail : _tail->prev); }
        const_rev_iterator  rend() const        { return _tail; }

        // CAPACITY
        bool                empty() const       { return !_size; }
        size_type           size() const        { return _size; }
        size_type           max_size() const    { return _node_allocator.max_size(); }
        
        // MODIFIERS
        void                clear();
        iterator            insert(const_iterator pos, const_reference value);
        void                insert(iterator pos, size_type count, const_reference value);
        void                insert(iterator pos, iterator first, iterator last); // check standart
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
        template <class CompareFunc>
        void                merge(list& other, CompareFunc comp);
        void                splice(const_iterator pos, list& other);
        void                splice(const_iterator pos, list& other, const_iterator it);
        void                splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
        void                remove(const_reference value);
        template<class UnaryPredicate>
        void                remove_if(UnaryPredicate pred);
        void                reverse();
        void                unique();
        template<class BinaryPredicate>
        void                unique(BinaryPredicate p);
        void                sort();
        template<typename CompareFunc>
        void 				sort(CompareFunc comp);
    };

    template<typename T, typename Alloca>
    list<T, Alloca>::list(const allocator_type& alloc)
    : _allocator(alloc), _head(createNewNode()), _tail(_head), _size(0)
    {
    }

    template<typename T, typename Alloca>
    list<T, Alloca>::list(const list& other)
    : _allocator(other._allocator)
    , _node_allocator(other._node_allocator)
    , _head(createNewNode()), _tail(_head), _size(0)
    {
        assign(other.begin(), other.end());
    }

    template<typename T, typename Alloca>
    list<T, Alloca>::list(size_type count, const_reference value, const allocator_type& alloc)
    : _allocator(alloc), _head(createNewNode()), _tail(_head), _size(0)
    {
        while (count-- > 0)
            push_back(value);
    }

    template<typename T, typename Alloca>
    list<T, Alloca>::list(iterator first, iterator last, const allocator_type& alloc)
    : _allocator(alloc), _head(createNewNode()), _tail(_head), _size(0)
    {
        while (first != last)
            push_back(*first++);
    }

    template<typename T, typename Alloca>
    list<T, Alloca>::~list()
    {
        clear();
        deleteNode(_tail);
    }
    
    template<typename T, typename Alloca>
    list<T, Alloca>&    list<T, Alloca>::operator=(const list& other)
    {
        if (this != &other)
            assign(other.begin(), other.end());
        return *this;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::assign(size_type count, const_reference value)
    {
        clear();
        while (count-- > 0)
            push_back(value);
    }

    template<typename T, typename Alloca>
    template< typename Tp, template <typename> class InputIt >
    void        list<T, Alloca>::assign(InputIt<Tp> first, InputIt<Tp> last)
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
    typename    list<T, Alloca>::iterator  list<T, Alloca>::insert(const_iterator pos, const_reference value)
    {
        if (pos == begin())
        {
            push_front(value);
            return begin();
        }
        node_type *ptr = createNewNode();
        node_type *post_insert = (node_type *)const_iterator::node_ptr(pos);
        ptr->prev = post_insert->prev;
        ptr->next = post_insert;
        _allocator.construct(&ptr->data, value);
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
        node_type   *elem_erase = iterator::node_ptr(pos);
        node_type   *post_erase = elem_erase->next;
        node_type   *pre_erase = elem_erase->prev;

        pre_erase->next = post_erase;
        post_erase->prev = pre_erase;
        deleteNode(elem_erase);
        --_size;
        return *post_erase;
    }

    template<typename T, typename Alloca>
    typename    list<T, Alloca>::iterator  list<T, Alloca>::erase(iterator first, iterator last)
    {
        iterator it;
        while (first != last)
            it = erase(first++);
        return it;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_front(const_reference value)
    {
        node_type* ptr = createNewNode();
        _allocator.construct(&ptr->data, value);
        pushFrontNode(ptr);
        ++_size;
    }
    
    template<typename T, typename Alloca>
    void        list<T, Alloca>::push_back(const_reference value)
    {
        node_type    *ptr = _node_allocator.allocate(1);
        _allocator.construct(&ptr->data, value);
        pushBackNode(ptr);
        ++_size;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::pop_front()
    {
        node_type    *ptr = _head;
        _head = _head->next;
        _head->prev = NULL;
        deleteNode(ptr);
        --_size;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::pop_back()
    {
        node_type    *ptr = _tail->prev;
        _tail->prev = ptr->prev;
        if (ptr->prev != NULL) // if ptr != head
            ptr->prev->next = _tail;
        else
            _head = _tail;
        deleteNode(ptr);
        --_size;
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
        node_type*  our_head = _head;
        node_type*  our_tail = _tail;
        size_type our_size = _size;
        allocator_type our_alloc = _allocator;
        node_allocator_type our_node_alloc = _node_allocator;

        _head = other._head;
        _tail = other._tail;
        _size = other._size;
        _allocator = other._allocator;
        _node_allocator = other._node_allocator;

        other._head = our_head;
        other._tail = our_tail;
        other._size = our_size;
        other._allocator = our_alloc;
        other._node_allocator = our_node_alloc;
    }

    template<typename T, typename Alloca>
    void        list<T, Alloca>::merge(list& other)
    {
        merge(other, cmp<T>);
    }

    template<typename T, typename Alloca>
    template <class CompareFunc>
    void        list<T, Alloca>::merge(list& other, CompareFunc comp)
    {
        if (this == &other)
            return;
        iterator        f1 = begin();
        iterator        l1 = end();
        iterator        f2 = other.begin();
        iterator        l2 = other.end();

        while (f1 != l1 && f2 != l2)
        {
            while (f1 != l1 && comp(*f1,*f2))
                f1++;
            node_type* next_node = (node_type*)iterator::node_ptr(f2)->next;
            splice(f1, other, f2);
            f2 = next_node;
        }
        if (f2 != l2)
            splice(f1, other, f2, l2);
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

            if (first_insert != end_insert)
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
    template<class UnaryPredicate>
    void        list<T, Alloca>::remove_if(UnaryPredicate pred)
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

    template<typename T, typename Alloca>
    void        list<T, Alloca>::reverse()
    {
        if (_size > 2)
        {
            node_type *node = _head;
            while (node->next != _tail)
            {
                std::swap(node->next, node->prev);
                node = node->prev;
            }
            // node on the last elem, which now is the new head
            _head->next = _tail;
            _tail->prev = _head;
            std::swap(node->next, node->prev);
            _head = node;
            _head->prev = NULL;
        }
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
    template<class BinaryPredicate>
    void        list<T, Alloca>::unique(BinaryPredicate p)
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

    template<typename T, typename Alloca>
    void        list<T, Alloca>::sort()
    {
        sort(cmp<T>);
    }

    template<typename T, typename Alloca>
    template<typename CompareFunc>
    void        list<T, Alloca>::sort(CompareFunc comp)
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

    template<typename T, typename Alloca>
    bool        operator==(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        if (x.size() != y.size())
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
            if (cmp(*x_first, *y_first))
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
        typename list<T, Alloca>::const_iterator  x_first = x.begin();
        typename list<T, Alloca>::const_iterator  x_last = x.end();
        typename list<T, Alloca>::const_iterator  y_first = y.begin();

        for (; x_first != x_last; ++x_first, ++y_first)
        {
            if (cmp(*x_first, *y_first))
                return false;
            if (cmp(*y_first, *x_first))
                return true;
        }
        return false;
    }

    template<typename T, typename Alloca>
    bool        operator<=(const list<T,Alloca>& x, const list<T,Alloca>& y)
    {
        return  !(x > y);
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