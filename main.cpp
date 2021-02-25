/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:06:18 by handrow           #+#    #+#             */
/*   Updated: 2021/02/25 19:46:59 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <memory>
#include "vector.hpp"
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
    std::cout << std::endl;
    
    std::cout << "MY VECTOR" << std::endl;
    std::cout << std::endl;

    // ft::vector<int> c;
    // std::cout << c.size() << "|" << c.capacity() << std::endl;
    // c.reserve(2);
    // std::cout << c.size() << "|" << c.capacity() << std::endl;
    // c.push_back(2);
    // c.push_back(2);
    // c.push_back(2);
    // c.push_back(2);
    // c.push_back(2);
    // c.pop_back();
    // c.resize(20);
    // std::cout << c.size() << "|" << c.capacity() << std::endl;
    // for (int i = 0; i < c.size(); ++i)
    //     std::cout << c[i] << " ";
    // std::cout << std::endl;
    // std::cout << "push elem" << std::endl;
    // ft::vector<int>::iterator   it = c.begin();
    // ft::vector<int>::iterator   id = c.end();
    // //while (it != id)
    // //    std::cout << *it++ << " ";
    // std::cout << std::endl;
    
    
    std::cout << "BASE TEST" << std::endl;
    ft::vector<int> vc;
    vc.push_back(1);
    vc.push_back(2);
    vc.push_back(3);
    std::cout << "BEGIN" << std::endl;
     for (int i = 0; i < vc.size(); ++i)
        std::cout << vc[i] << " ";
   // std::vector<int>::iterator it = vc.begin();
    ft::vector<int>::iterator id = vc.begin();
    vc.insert(id + 1, 100);
    std::cout << "FINAL" <<std::endl;
   for (int i = 0; i < vc.size(); ++i)
        std::cout << vc[i] << " ";
}