#include "set.hpp"
#include <iostream>
#include <set>

template <typename iterator>
void print_iterators(iterator a, iterator b) {
    while (a != b) {
        std::cout << *a++ << " ";
    }
    std::cout << std::endl;
}

#ifndef NameSpace
# define NameSpace ft
#endif

int main(void) {
    // NameSpace::set<int>    MY_SET;
    // NameSpace::set<int>    MY_SET_2;

    ft::set<int>    MY_SET;
    // ft::set<int>    MY_SET_2(MY_SET.begin(), MY_SET.end());
    MY_SET.insert(100);
    MY_SET.insert(200);
    MY_SET.insert(300);
    MY_SET.insert(400);
    MY_SET.insert(500);

    //MY_SET_2.insert(MY_SET.rbegin(), MY_SET.rend());

    // MY_SET.insert(++++MY_SET.begin(), 3); // check insert hint
    print_iterators(MY_SET.begin(), MY_SET.end());
    // print_iterators(MY_SET_2.begin(), MY_SET_2.end());
    std::cout << MY_SET.size() << std::endl;    
    // std::cout << *MY_SET.lower_bound(550) << std::endl;

    // NameSpace::set<int>::iterator i = MY_SET.begin();
    // NameSpace::set<int>::const_iterator ci = i;
    // NameSpace::set<int>::reverse_iterator ri = i;
    // NameSpace::set<int>::const_reverse_iterator cri = ri; // TODO: fix it

    // MY_SET.erase(MY_SET.begin(), ----MY_SET.end());
}