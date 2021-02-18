/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:06:14 by handrow           #+#    #+#             */
/*   Updated: 2021/02/18 18:39:22 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

namespace ft
{
	template < typename _T, typename _Allocator=std::allocator<_T> >
	class vector
	{
	public:

		typedef _T					value_type;
		typedef _Allocator			allocator_type;
		typedef	size_t				size_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef ptrdiff_t			difference_type;

	private:
		pointer			data;
		allocator_type	alloca;
		size_type		size;
		size_type		capacity;

	public:
		// MEMBER FUNCTIONS
		vector(); 																		//	default 
		vector(size_type n, const reference val, const allocator_type& alloc); 			//	fill
		vector(InputIterator first, InputIterator last, const allocator_type& alloc);	//	range
		vector(const vector& copy); 													//	copy
		~vector();

		vector&				operator=(const vector& copy);
		void				assign(size_type num, reference u);

		// ELEMENT ACCESS
		size_type&			at(size_type pos);
		const size_type&	at(size_type pos) const;
		size_type&			operator[](size_type pos);
		const size_type&	operator[](size_type pos) const;

		// ITERATOR
		template <typename _T, typename _Distance = std::ptrdiff_t, typename _Pointer = _T*, typename _Reference = _T&>
		class	iterator
		{
		public:
			typedef	_T					value_type;
			typedef	_Distance			difference_type;
			typedef	_Pointer			pointer;
			typedef	iterator<_T>		iterator;
			typedef iterator<const _T>	const_iterator;

			iterator		begin();
			iterator		end();

			const_iterator	begin() const;
			const_iterator	end() const;
		};
	};
}
