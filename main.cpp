/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrow <handrow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:06:18 by handrow           #+#    #+#             */
/*   Updated: 2021/02/17 18:23:33 by handrow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

int main()
{
	std::vector<std::string> vec;
	vec.push_back("S");
	vec.push_back("S");
	vec.push_back("S");
	for (int i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << std::endl;
	vec.assign(3, "Sam");
		for (int i = 0; i < vec.size(); ++i)
			std::cout << vec[i] << std::endl;
}