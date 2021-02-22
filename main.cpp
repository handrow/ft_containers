/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:06:18 by handrow           #+#    #+#             */
/*   Updated: 2021/02/22 22:00:22 by handrow          ###   ########.fr       */
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
    //std::cout << bb.capacity() << std::endl;
    bb.push_back(2);
    bb.push_back(2);
    bb.push_back(2);
    bb.push_back(2);
    bb.push_back(2);
    bb.push_back(2);
    //std::cout << bb.capacity();
    std::cout << bb.max_size();
}