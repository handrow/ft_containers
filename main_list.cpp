#include <list>
#include "list.hpp"
#include <iostream>


void test_splice()
{
    ft::list<int> l;
    ft::list<int> l1;

    l.push_back(100);
    l.push_back(100);
    l.push_back(100);
    l.push_back(100);
    l.push_back(100);
    l.push_back(100);

    ft::list<int>::iterator it1 = l.begin();
    ft::list<int>::iterator it2 = l.end();
    while (it1 != it2)
        std::cout << *it1++ << " ";
    std::cout << std::endl;

    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.push_back(6);

    ft::list<int>::iterator it3 = l1.begin();
    ft::list<int>::iterator it4 = l1.end();
    while (it3 != it4)
        std::cout << *it3++ << " ";
    std::cout << std::endl;

    l.splice(--it2, l1, it3, it4);
    ft::list<int>::iterator it5 = l.begin();
    ft::list<int>::iterator it6 = l.end();
    while (it5 != it6)
        std::cout << *it5++ << " ";
    std::cout << std::endl;
}

int main()
{
//     ft::list<int> l;
//     //for (int i = 11; i > 1; i--)
//      //   l.push_back(i);
//     //for (int i = 0; i < 20; i++)
//      //   l.push_back(i);
//      l.push_back(100);
//      l.push_back(100);
//      l.push_back(100);
//      l.push_back(1);
//      l.push_back(1);
//      l.push_back(2);
//      l.push_back(50);
//      l.push_back(50);

//     ft::list<int>::iterator it1 = l.begin();
//     ft::list<int>::iterator it2 = l.end();
//    // l.erase(++it1);
//     //it1--;
//     //l.insert(it1, 50); // does not work if i insert value to begin()
//     //it1 = l.begin();
//     while (it1 != it2)
//         std::cout << *it1++ << " ";
//     //l.remove(100);
//    //l.remove_if([](int n){ return n > 10; });  check remove if
//     std::cout << std::endl;
//     ft::list<int>::iterator it12 = l.begin();
//     ft::list<int>::iterator it21 = l.end();
//         while (it12 != it21)
//         std::cout << *it12++ << " ";
//     std::cout << std::endl << l.size();

    test_splice();
}