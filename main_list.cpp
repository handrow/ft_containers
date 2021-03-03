#include <list>
#include "list.hpp"
#include <iostream>

int main()
{
    ft::list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_front(4);
    l.pop_back();
    std::cout << l.size();
}