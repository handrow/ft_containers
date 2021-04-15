/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:11:42 by handrow           #+#    #+#             */
/*   Updated: 2021/04/12 21:12:26 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../avl_tree/USSRtree.hpp"
#include "map.hpp"
#include "../stack/stack.hpp"

namespace ft
{
    template<class Node, class T>
    class map_iterator 
    {
    private:
        stack<Node*> q;
    
    public:
        map_iterator(Node* root)
        {
            Node* curr = root;
            while (curr != NULL)
                q.push(curr), curr = curr->left;
        }

        Node* curr()
        {
            return q.top();
        }

        void next()
        {
            Node* curr = q.top()->right;
            q.pop();
            while (curr != NULL)
                q.push(curr), curr = curr->left;
        }
    
        bool isEnd()
        {
            return !(q.size());
        }

        void iterate(map_iterator it)
        {
            while (!it.isEnd())
                std::cout << it.curr()->data << " ", it.next();
        }
    };

} // namespace ft
