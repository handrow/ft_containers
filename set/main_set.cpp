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

void test_ft_swap()
{
    std::cout << "* FT SWAP *" << std::endl;
    ft::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    std::cout << "s contains:" << " ";
    print_iterators(s.begin(), s.end());

    ft::set<int> s1;
    s1.insert(10);
    s1.insert(8);
    s1.insert(9);
    std::cout << "s1 contains:" << " ";
    print_iterators(s1.begin(), s1.end());

    s.swap(s1);
    std::cout << "after swap:" << std::endl;
    std::cout << "s contains:" << " ";
    print_iterators(s.begin(), s.end());
    std::cout << "s1 contains:" << " ";
    print_iterators(s1.begin(), s1.end());
    std::cout << std::endl;
}

void test_std_swap()
{
    std::cout << "* STD SWAP *" << std::endl;
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    std::cout << "s contains:" << " ";
    print_iterators(s.begin(), s.end());

    std::set<int> s1;
    s1.insert(10);
    s1.insert(8);
    s1.insert(9);
    std::cout << "s1 contains:" << " ";
    print_iterators(s1.begin(), s1.end());

    s.swap(s1);
    std::cout << "after swap:" << std::endl;
    std::cout << "s contains:" << " ";
    print_iterators(s.begin(), s.end());
    std::cout << "s1 contains:" << " ";
    print_iterators(s1.begin(), s1.end());
    std::cout << std::endl;
}

void test_ft_count()
{
    std::cout << "* FT COUNT *" << std::endl;
    ft::set<int> s;
    s.insert(100);
    s.insert(150);
    s.insert(200);
    if (s.count(200))
        std::cout << "The key 200 is present" << std::endl;
    else
        std::cout << "The key 200 is not present" << std::endl;

    if (s.count(500))
        std::cout << "The key 500 is present" << std::endl;
    else
        std::cout << "The key 500 is not present" << std::endl;
}

void test_std_count()
{
    std::cout << "* STD COUNT *" << std::endl;
    std::set<int> s;
    s.insert(100);
    s.insert(150);
    s.insert(200);
    if (s.count(200))
        std::cout << "The key 200 is present" << std::endl;
    else
        std::cout << "The key 200 is not present" << std::endl;

    if (s.count(500))
        std::cout << "The key 500 is present" << std::endl;
    else
        std::cout << "The key 500 is not present" << std::endl;
}

void test_ft_find()
{
    ft::set<int> s;
    s.insert(100);
    s.insert(200);
    s.insert(300);

    if (s.find(300) == s.end())
        std::cout << "300 is Not found" << std::endl;
    else
        std::cout << "300 is Found" << std::endl;

    if (s.find(1000) != s.end())
        std::cout << "1000 is Found" << std::endl;
    else
        std::cout << "1000 is Not found" << std::endl;
}

void test_std_find()
{
    std::set<int> s;
    s.insert(100);
    s.insert(200);
    s.insert(300);

    if (s.find(300) == s.end())
        std::cout << "300 is Not found" << std::endl;
    else
        std::cout << "300 is Found" << std::endl;

    if (s.find(1000) != s.end())
        std::cout << "1000 is Found" << std::endl;
    else
        std::cout << "1000 is Not found" << std::endl;
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

void test_ft_equal_range()
{
    ft::set<int> myset;

    for (int i = 1; i <= 5; i++) 
        myset.insert(i*10);

    std::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> ret;
    ret = myset.equal_range(30);

    std::cout << "the lower bound points to: " << *ret.first << std::endl;
    std::cout << "the upper bound points to: " << *ret.second << std::endl;
}

void test_std_equal_range()
{
    std::set<int> myset;

    for (int i = 1; i <= 5; i++) 
        myset.insert(i*10);

    std::pair<std::set<int>::const_iterator,std::set<int>::const_iterator> ret;
    ret = myset.equal_range(30);

    std::cout << "the lower bound points to: " << *ret.first << std::endl;
    std::cout << "the upper bound points to: " << *ret.second << std::endl;
}

void test_ft_operators()
{
    std::cout << "* FT OPERATORS *" << std::endl;
    ft::set<int> alice;
    alice.insert(1);
    alice.insert(2);
    alice.insert(3);

    ft::set<int> bob;
    for (int i = 7; i < 10; ++i)
        bob.insert(i);

    ft::set<int> eve;
    eve.insert(1);
    eve.insert(2);
    eve.insert(3);
 
    // Compare non equal containers
    std::cout << "alice == bob returns " << (alice == bob) << std::endl;
    std::cout << "alice != bob returns " << (alice != bob) << std::endl;
    std::cout << "alice <  bob returns " << (alice < bob) << std::endl;
    std::cout << "alice <= bob returns " << (alice <= bob) << std::endl;
    std::cout << "alice >  bob returns " << (alice > bob) << std::endl;
    std::cout << "alice >= bob returns " << (alice >= bob) << std::endl;
 
    std::cout << std::endl;
 
    // Compare equal containers
    std::cout << "alice == eve returns " << (alice == eve) << std::endl;
    std::cout << "alice != eve returns " << (alice != eve) << std::endl;
    std::cout << "alice <  eve returns " << (alice < eve) << std::endl;
    std::cout << "alice <= eve returns " << (alice <= eve) << std::endl;
    std::cout << "alice >  eve returns " << (alice > eve) << std::endl;
    std::cout << "alice >= eve returns " << (alice >= eve) << std::endl;
}

void test_std_operators()
{
    std::cout << "* STD OPERATORS *" << std::endl;
    std::set<int> alice;
    alice.insert(1);
    alice.insert(2);
    alice.insert(3);

    std::set<int> bob;
    for (int i = 7; i < 10; ++i)
        bob.insert(i);

    std::set<int> eve;
    eve.insert(1);
    eve.insert(2);
    eve.insert(3);
 
    // Compare non equal containers
    std::cout << "alice == bob returns " << (alice == bob) << std::endl;
    std::cout << "alice != bob returns " << (alice != bob) << std::endl;
    std::cout << "alice <  bob returns " << (alice < bob) << std::endl;
    std::cout << "alice <= bob returns " << (alice <= bob) << std::endl;
    std::cout << "alice >  bob returns " << (alice > bob) << std::endl;
    std::cout << "alice >= bob returns " << (alice >= bob) << std::endl;
 
    std::cout << std::endl;
 
    // Compare equal containers
    std::cout << "alice == eve returns " << (alice == eve) << std::endl;
    std::cout << "alice != eve returns " << (alice != eve) << std::endl;
    std::cout << "alice <  eve returns " << (alice < eve) << std::endl;
    std::cout << "alice <= eve returns " << (alice <= eve) << std::endl;
    std::cout << "alice >  eve returns " << (alice > eve) << std::endl;
    std::cout << "alice >= eve returns " << (alice >= eve) << std::endl;
}

void test_ft_key_comp()
{
    std::cout << "* FT KEY_COMP *" << std::endl;
    ft::set<int> myset;
    int highest;

    ft::set<int>::value_compare mycomp = myset.key_comp();

    for (int i=0; i<=5; i++) myset.insert(i);

    std::cout << "myset contains:";

    highest=*myset.rbegin();
    ft::set<int>::iterator it=myset.begin();
    do
        std::cout << ' ' << *it;
    while ( mycomp(*(++it),highest));

    std::cout << std::endl;
}

void test_std_key_comp()
{
    std::cout << "* STD KEY_COMP *" << std::endl;
    std::set<int> myset;
    int highest;

    std::set<int>::value_compare mycomp = myset.key_comp();

    for (int i=0; i<=5; i++) myset.insert(i);

    std::cout << "myset contains:";

    highest=*myset.rbegin();
    std::set<int>::iterator it=myset.begin();
    do
        std::cout << ' ' << *it;
    while ( mycomp(*(++it),highest));

    std::cout << std::endl;
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
    test_ft_swap();
    test_std_swap();
    test_ft_count();
    test_std_count();
    test_ft_find();
    test_std_find();
    test_ft_lower_upper_bound();
    test_std_lower_upper_bound();
    test_ft_equal_range();
    test_std_equal_range();
    test_ft_operators();
    test_std_operators();
    test_ft_key_comp();
    test_std_key_comp();
}