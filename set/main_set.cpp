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
    NameSpace::set<int>    MY_SET;

    MY_SET.insert(100);
    MY_SET.insert(200);
    MY_SET.insert(300);
    MY_SET.insert(400);
    MY_SET.insert(500);

    // NameSpace::set<int>::iterator i = MY_SET.begin();
    // NameSpace::set<int>::const_iterator ci = i;
    // NameSpace::set<int>::reverse_iterator ri = i;
    // NameSpace::set<int>::const_reverse_iterator cri = ri;

    MY_SET.erase(MY_SET.begin(), --MY_SET.end());
    print_iterators(MY_SET.begin(), MY_SET.end());
}