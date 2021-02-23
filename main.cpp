/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:06:18 by handrow           #+#    #+#             */
/*   Updated: 2021/02/23 21:00:01 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <memory>
int main()
{
    std::vector<std::string> vec;
    vec.push_back("S");
    vec.push_back("S");
    vec.push_back("S");
    vec.at(2);
    for (int i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << std::endl;
    vec.assign(3, "Sam");
    for (int i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << std::endl;
    std::allocator<int> alloc;
    alloc.allocate(8);
    int *a = alloc.allocate(1);
    alloc.construct(a, 5);
    std::cout << "__________________________________________" << std::endl;


    std::vector<int> bb;
    bb.reserve(5);
    bb.push_back(2);
    bb.push_back(2);
    bb.push_back(2);
    bb.push_back(2);
    bb.push_back(2);
    bb.reserve(10);
    bb.reserve(20);
    
    std::cout << bb.size() << "|" << bb.capacity() << std::endl;

    std::cout << "MY VECTOR" << std::endl;

    //ft::vector<int> c;
    
    //c.reserve(3);
    //c.push_back(2);
    //std::cout << c.size() << "|" << c.capacity() << std::endl;
    
}