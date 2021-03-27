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

void testStdMerge()
{

    std::cout << "STD LIST" << std::endl;
    std::list<int> l1;
    l1.push_back(-10);
    l1.push_back(500);
    l1.push_back(-400);
    l1.push_back(12);
    l1.push_back(3);

    std::list<int> l;
    l.push_front(0);
    l.push_back(400);
    l.push_back(2);
    l.push_back(-10);
    l.push_front(4);
    l.push_front(0);
    l.push_back(400);
    l.push_back(2);
    l.push_back(-10);
    l.push_front(4);

    l.sort();
    l1.sort();
    print(l);
    print(l1);
    l.merge(l1, std::less<int>());

    print(l);
}

void testMyMerge()
{
    std::cout << "MY LIST" << std::endl;
    ft::list<int> l1;
    l1.push_back(-10);
    l1.push_back(500);
    l1.push_back(-400);
    l1.push_back(12);
    l1.push_back(3);

    ft::list<int> l;
    l.push_front(0);
    l.push_back(400);
    l.push_back(2);
    l.push_back(-10);
    l.push_front(4);
    l.push_front(0);
    l.push_back(400);
    l.push_back(2);
    l.push_back(-10);
    l.push_front(4);

    l.sort();
    l1.sort();
    print(l);
    print(l1);
    l.merge(l1, std::less<int>());

    print(l);
}

int main()
{
    //test_splice();
    testStdMerge();
    testMyMerge();
}