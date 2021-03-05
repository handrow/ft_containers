#include <list>
#include "list.hpp"
#include <iostream>

int main()
{
    ft::list<int> l;
    for (int i = 0; i < 11; i++)
        l.push_back(i);
    //l.pop_back();
    //l.pop_front();
    //l.push_front(30);
    //l.push_front(40);
    //l.assign(2, 10);
    ft::list<int>::iterator it1 = l.begin();
    ft::list<int>::iterator it2 = l.end();
   // l.erase(++it1);
    //it1--;
    //l.insert(it1, 50); // does not work if i insert value to begin()
    //it1 = l.begin();
    while (it1 != it2)
        std::cout << *it1++ << " ";
    std::cout << std::endl << l.size();
}