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

void test_ft_constructor()
{
    std::cout << "* FT CONSTRUCTORS *" << std::endl;
    ft::set<std::string> s;

    s.insert("cat");
    s.insert("dog");
    s.insert("horse");
    std::cout << "s contains: " << " ";
    print_iterators(s.begin(), s.end());

    ft::set<std::string> sCopy(s);
    std::cout << "sCopy contains: " << " ";
    print_iterators(sCopy.begin(), sCopy.end());

    ft::set<std::string> sRange(sCopy.begin(), sCopy.end());
    std::cout << "sRange contains: " << " ";
    print_iterators(sRange.begin(), sRange.end());

    ft::set<std::string> sAssign;
    sAssign = sRange;
    std::cout << "sAssign contains: " << " ";
    print_iterators(sAssign.begin(), sAssign.end());
    std::cout << std::endl;
}

void test_std_constructor()
{
    std::cout << "* STD CONSTRUCTORS *" << std::endl;
    std::set<std::string> s;

    s.insert("cat");
    s.insert("dog");
    s.insert("horse");
    std::cout << "s contains: " << " ";
    print_iterators(s.begin(), s.end());

    std::set<std::string> sCopy(s);
    std::cout << "sCopy contains: " << " ";
    print_iterators(sCopy.begin(), sCopy.end());

    std::set<std::string> sRange(sCopy.begin(),sCopy.end());
    std::cout << "sRange contains: " << " ";
    print_iterators(sRange.begin(), sRange.end());
        
    std::set<std::string> sAssign;
    sAssign = sRange;
    std::cout << "sAssign contains: " << " ";
    print_iterators(sAssign.begin(), sAssign.end());
    std::cout << std::endl;
}

void test_ft_capacity()
{
    std::cout << "* FT CAPACITY *" << std::endl;
    ft::set<int> MY_SET;
    MY_SET.insert(1);
    MY_SET.insert(2);
    MY_SET.insert(3);
    MY_SET.insert(4);
    MY_SET.insert(5);
    std::cout << "MY_SET contains: " << " ";
    print_iterators(MY_SET.begin(), MY_SET.end());
    std::cout << "MY_SET SIZE(): " << MY_SET.size() << std::endl;
    std::cout << "MY_SET EMPTY(): " << MY_SET.empty() << std::endl;
    std::cout << "MY_SET MAX_SIZE(): " << MY_SET.max_size() << std::endl;

    ft::set<int> MY_SET2;
    std::cout << "MY_SET2 SIZE(): " << MY_SET2.size() << std::endl;
    std::cout << "MY_SET2 EMPTY(): " << MY_SET2.empty() << std::endl;
    std::cout << "MY_SET2 MAX_SIZE(): " << MY_SET2.max_size() << std::endl;
    std::cout << std::endl;
}

void test_std_capacity()
{
    std::cout << "* FT CAPACITY *" << std::endl;
    std::set<int> MY_SET;
    MY_SET.insert(1);
    MY_SET.insert(2);
    MY_SET.insert(3);
    MY_SET.insert(4);
    MY_SET.insert(5);
    std::cout << "MY_SET contains: " << " ";
    print_iterators(MY_SET.begin(), MY_SET.end());
    std::cout << "MY_SET SIZE(): " << MY_SET.size() << std::endl;
    std::cout << "MY_SET EMPTY(): " << MY_SET.empty() << std::endl;
    std::cout << "MY_SET MAX_SIZE(): " << MY_SET.max_size() << std::endl;

    std::set<int> MY_SET2;
    std::cout << "MY_SET2 SIZE(): " << MY_SET2.size() << std::endl;
    std::cout << "MY_SET2 EMPTY(): " << MY_SET2.empty() << std::endl;
    std::cout << "MY_SET2 MAX_SIZE(): " << MY_SET2.max_size() << std::endl;
    std::cout << std::endl;

}

void test_ft_clear()
{
    std::cout << "* FT CLEAR *" << std::endl;
    ft::set<int> MY_SET;
    MY_SET.insert(1);
    MY_SET.insert(2);
    MY_SET.insert(3);
    MY_SET.insert(4);
    MY_SET.insert(5);
    std::cout << "before clear:" << " ";
    print_iterators(MY_SET.begin(), MY_SET.end());
    std::cout << "MY_SET SIZE(): " << MY_SET.size() << std::endl;
    MY_SET.clear();
    std::cout << "after clear:" << " ";
    print_iterators(MY_SET.begin(), MY_SET.end());
    std::cout << "MY_SET SIZE(): " << MY_SET.size() << std::endl;
    std::cout << std::endl;
}

void test_std_clear()
{
    std::cout << "* STD CLEAR *" << std::endl;
    std::set<int> MY_SET;
    MY_SET.insert(1);
    MY_SET.insert(2);
    MY_SET.insert(3);
    MY_SET.insert(4);
    MY_SET.insert(5);
    std::cout << "before clear:" << " ";
    print_iterators(MY_SET.begin(), MY_SET.end());
    std::cout << "MY_SET SIZE(): " << MY_SET.size() << std::endl;
    MY_SET.clear();
    std::cout << "after clear:" << " ";
    print_iterators(MY_SET.begin(), MY_SET.end());
    std::cout << "MY_SET SIZE(): " << MY_SET.size() << std::endl;
    std::cout << std::endl;
}

void test_ft_insert()
{
    std::cout << "* FT INSERT *" << std::endl;
    ft::set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);
    ft::set<int>::iterator first = s.begin();
    ft::set<int>::iterator last = s.end();
    std::cout << "s contains:" << " ";
    print_iterators(first, last);
    std::cout << "trying to insert 40 again" << " ";
    s.insert(40);
    first = s.begin();
    last = s.end();
    print_iterators(first, last);
    
    s.insert(++s.begin(), 100);
    print_iterators(s.begin(), s.end());
    s.insert(--s.end(), 5);
    print_iterators(s.begin(), s.end());

    ft::set<int> s1;
    s1.insert(s.begin(), ----s.end()); // insert first four elems from s
    std::cout << "s1 contains:" << " ";
    print_iterators(s1.begin(), s1.end());
    std::cout << std::endl;
}

void test_std_insert()
{
    std::cout << "* STD INSERT *" << std::endl;
    std::set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);
    std::set<int>::iterator first = s.begin();
    std::set<int>::iterator last = s.end();
    std::cout << "s contains:" << " ";
    print_iterators(first, last);
    std::cout << "trying to insert 40 again" << " ";
    s.insert(40);
    first = s.begin();
    last = s.end();
    print_iterators(first, last);

    s.insert(++s.begin(), 100);
    print_iterators(s.begin(), s.end());
    s.insert(--s.end(), 5);
    print_iterators(s.begin(), s.end());

    std::set<int> s1;
    s1.insert(s.begin(), ----s.end());
    std::cout << "s1 contains:" << " ";
    print_iterators(s1.begin(), s1.end());
    std::cout << std::endl;
}

void test_ft_erase()
{
    std::cout << "* FT ERASE *" << std::endl;
    ft::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(7);
    s.insert(8);
    s.insert(9);
    std::cout << "s contains:" << std::endl;
    print_iterators(s.begin(), s.end());
    // erase all odd numbers from s
    for(ft::set<int>::iterator it = s.begin(); it != s.end(); ) 
    {
        ft::set<int>::iterator tmp(it++);
        if(*tmp % 2 != 0)
            s.erase(tmp);
    }
    std::cout << "after erase:" << " ";
    print_iterators(s.begin(), s.end());
    
    std::cout << "after second erase:" << " ";
    s.erase(++s.begin(), s.end());
    print_iterators(s.begin(), s.end());
    std::cout << std::endl;
}

void test_std_erase()
{
    std::cout << "* STD ERASE *" << std::endl;
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(7);
    s.insert(8);
    s.insert(9);
    std::cout << "s contains:" << std::endl;
    print_iterators(s.begin(), s.end());
    // erase all odd numbers from s
    for(std::set<int>::iterator it = s.begin(); it != s.end(); ) 
    {
        std::set<int>::iterator tmp(it++);
        if(*tmp % 2 != 0)
            s.erase(tmp);
    }
    std::cout << "after erase:" << " ";
    print_iterators(s.begin(), s.end());
    
    std::cout << "after second erase:" << " ";
    s.erase(++s.begin(), s.end());
    print_iterators(s.begin(), s.end());
    std::cout << std::endl;
}

void test_ft_lower_upper_bound()
{
    ft::set<int>    mySet;
    mySet.insert(100);
    mySet.insert(200);
    mySet.insert(300);
    mySet.insert(400);
    mySet.insert(500);
    std::cout << "My Set contains: " << " ";
    print_iterators(mySet.begin(), mySet.end());
    std::cout << "lower_bound: "<< *mySet.lower_bound(200) << std::endl;
    std::cout << "upper_bound: "<< *mySet.upper_bound(200) << std::endl;
}

void test_std_lower_upper_bound()
{
    std::set<int>    mySet;
    mySet.insert(100);
    mySet.insert(200);
    mySet.insert(300);
    mySet.insert(400);
    mySet.insert(500);
    std::cout << "My Set contains: " << " ";
    print_iterators(mySet.begin(), mySet.end());
    std::cout << "lower_bound: "<< *mySet.lower_bound(200) << std::endl;
    std::cout << "upper_bound: "<< *mySet.upper_bound(200) << std::endl;
}

int main(void)
{
    test_ft_constructor();
    test_std_constructor();
    test_ft_capacity();
    test_std_capacity();
    test_ft_clear();
    test_std_clear();
    test_ft_insert();
    test_std_insert();
    test_ft_erase();
    test_std_erase();
    test_ft_lower_upper_bound();
    test_std_lower_upper_bound();
}