#include <list>
#include "list.hpp"
#include <iostream>

template <typename Container>
void print(Container& c, const std::string& prefix = "LIST") {
    typename Container::iterator first = c.begin();
    typename Container::iterator second = c.end();

    std::cout << prefix << ": ";
    std::cout << "sz = " << c.size() << ", ";
    std::cout << "data = [ ";
    while (first != second) {
        std::cout << *first++ << " ";
    }
    std::cout << "]" << std::endl;
}

void test_splice()
{

    ft::list<int> l;
    l.push_back(100);
    l.push_back(100);
    l.push_back(100);
    l.push_back(100);
    l.push_back(100);
    l.push_back(100);

    ft::list<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.push_back(6);

    print(l, "l ");
    print(l1, "l1");

    l.splice((l.end()), l1);
    print(l, "l ");
    print(l1, "l1");
    std::cout << std::endl;
}

void testFillConstructor()
{
    ft::list<int> l(5, 10);
    print(l);
}

int main()
{
    //test_splice();
    //testFillConstructor();
    ft::list<int> l1;
    l1.push_back(5);
    l1.push_back(9);
    l1.push_back(0);
    l1.push_back(1);
    l1.push_back(3);
    ft::list<int> l;

    //std::list<int> s;
    l.push_front(8);
    l.push_back(7);
    l.push_back(2);
    l.push_back(6);
    l.push_front(4);

    l.sort();
    l1.sort();
    l.merge(l1);

    print(l);
    print(l1);
    print(l);
}