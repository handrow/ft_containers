#include "randomAccessIterator.hpp"
#include "vector.hpp"
#include <vector>

void test_assing()
{
	std::cout << "TEST ASSIGN" << std::endl;

	ft::vector<int> test1;

	test1.push_back(10);
	test1.assign(4, 1);
	test1.push_back(10);
	test1.push_back(11);
	ft::vector<int>::iterator it1 = test1.begin();
	ft::vector<int>::iterator it2 = test1.end();
	ft::vector<int>::iterator it3 = test1.begin();
	while(it1 != it2)
	{
		std::cout << *it1 << ",";
		it1++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	ft::vector<int> test2;

	test2.assign(it3, it2);
	test2.push_back(10);
	test2.pop_back();
	it3 = test2.begin();
	ft::vector<int>::iterator it4 = test2.end();
	while(it3 != it4)
	{
		std::cout << *it3 << ",";
		it3++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;

}

void test_insert()
{
	std::cout << "TEST INSERT" << std::endl;
	ft::vector<int> test1;

	for (int i = 9; i < 20; i++)
		test1.push_back(i);
	ft::vector<int>::iterator it1 = test1.begin();

	// ft::vector<int>::iterator it5 = test1.insert(it1 + 1, 5);
	test1.insert(it1 + 2, 10);
	it1 = test1.begin();
	ft::vector<int>::iterator it2 = test1.end();
	
	it1 = test1.begin();
	it2 = test1.end();

	while(it1 != it2)
	{
		std::cout << *it1 << ",";
		it1++;
	}
	std::cout << "\n";

	ft::vector<int> test2;

	for (int i = 20; i < 30; i++)
		test2.push_back(i);
	it1 = test1.begin();
	ft::vector<int>::iterator it7 = test2.begin();
	test2.insert(it7 + 3, it1, it2);
	it7 = test2.begin();
	it7 = test2.begin();
	it7 = test2.begin();
	ft::vector<int>::iterator it8 = test2.end();
	while(it7 != it8)
	{
		std::cout << *it7 << ",";
		it7++;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;


	std::vector<int> t;
	for (int i = 10; i < 20; i++)
		t.push_back(i);
	std::vector<int>::iterator it3 = t.begin();
	// std::vector<int>::iterator it6 = t.end();
	it3++;
	std::vector<int>::iterator it4 = t.insert(it3, 5);
	for (unsigned long i = 0; i < t.size(); i++)
		std::cout << t[i] << " ";
	std::cout << *it4;
}

void test_arase()
{
	std::cout << "TEST ERASE" << std::endl;

	std::vector<int> test1;

	for (int i = 10; i < 20; i++)
		test1.push_back(i);
	for(unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";
	std::cout << std::endl;
	std::vector<int>::iterator it1 = test1.begin();
	it1 = test1.erase(it1 + 1);
	for(unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";

	std::cout << "\nreturn iterator " << *it1 << std::endl;
	std::cout << std::endl;

	ft::vector<int> test2;

	for (int i = 10; i < 20; i++)
		test2.push_back(i);
	for(unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";
	std::cout << std::endl;
	ft::vector<int>::iterator it2 = test2.begin();
	it2 = test2.erase(it2 + 1);
	for(unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";

	std::cout << "\nreturn iterator " << *it2 << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::vector<int> test3;

	for (int i = 10; i < 20; i++)
		test3.push_back(i);
	for(unsigned long i = 0; i < test3.size(); i++)
		std::cout << test3[i] << " ";
	std::cout << std::endl;
	std::vector<int>::iterator it3 = test3.begin();
	it3 = test3.erase(it3 + 1, it3 + 3);
	for(unsigned long i = 0; i < test3.size(); i++)
		std::cout << test3[i] << " ";

	std::cout << "\nreturn iterator " << *it3 << std::endl;
	std::cout << std::endl;

	ft::vector<int> test4;

	for (int i = 10; i < 20; i++)
		test4.push_back(i);
	for(unsigned long i = 0; i < test4.size(); i++)
		std::cout << test4[i] << " ";
	std::cout << std::endl;
	ft::vector<int>::iterator it4 = test4.begin();
	it4 = test4.erase(it4 + 1, it4 + 3);
	for(unsigned long i = 0; i < test4.size(); i++)
		std::cout << test4[i] << " ";
	
	std::cout << "\nreturn iterator " << *it4 << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;
}

void	test_swap()
{
	std::cout << "TEST SWAP" << std::endl;

	std::vector<int>	test1(5, 200);
	std::vector<int>	test2(5, 100);

	for (unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";
	std::cout << std::endl;
	for (unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";
	test1.swap(test2);
	std::cout << std::endl;
	std::cout << std::endl;
	for (unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";
	std::cout << std::endl;
	for (unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";
	
	std::cout << std::endl;
	std::cout << std::endl;

	ft::vector<int>	test3(5, 200);
	ft::vector<int>	test4(5, 100);

	for (unsigned long i = 0; i < test3.size(); i++)
		std::cout << test3[i] << " ";
	std::cout << std::endl;
	for (unsigned long i = 0; i < test4.size(); i++)
		std::cout << test4[i] << " ";
	std::cout << std::endl;
	test3.swap(test4);
	std::cout << std::endl;
	for (unsigned long i = 0; i < test3.size(); i++)
		std::cout << test3[i] << " ";
	std::cout << std::endl;
	for (unsigned long i = 0; i < test4.size(); i++)
		std::cout << test4[i] << " ";

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;
}

void test_clear()
{
	ft::vector<int> myvector;
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();
  myvector.push_back (1101);
  myvector.push_back (2202);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void test_at()
{
	ft::vector<int> myvector (10, 21);   // 10 zero-initialized ints

  // assign some values:
	for (unsigned i = 0; i < myvector.size(); i++)
	myvector.at(i) = i;

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';
}

void test_reserve()
{
	std::cout << "TEST RESERVE" << std::endl;

	ft::vector<int> test;

	for (int i = 0; i < 7; i++)
		test.push_back(i);
	std::cout << test.capacity();
	std::cout << std::endl;
	test.reserve(8);
	std::cout << test.capacity();
	std::cout << std::endl;
	test.reserve(16);
	std::cout << test.capacity();
	std::cout << std::endl;
	for (unsigned long i = 0; i < test.size(); i++)
		std::cout << test[i] << " ";

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;
}

void test_reverse_iterator()
{
	std::cout << "TEST REVERSE ITERATOR" << std::endl;
	ft::vector<int> test1;

	for (int i = 0; i < 11; i++)
		test1.push_back(i);
	
	ft::vector<int>::reverse_iterator it1 = test1.rbegin();
	std::cout << *it1 << " ";

	std::vector<int> test2;

	for (int i = 0; i < 11; i++)
		test2.push_back(i);

	std::vector<int>::reverse_iterator it2 = test2.rbegin();
	std::cout << *it2 << " ";

	ft::vector<int>::reverse_iterator it3(test1.rbegin());

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;
}

void test_base()
{
	std::cout << "TEST BASE" << std::endl;
	std::cout << std::endl;

	ft::vector<int> v;

	for (unsigned long i = 0; i < 6; i++)
		v.push_back(i);

    ft::vector<int>::iterator it = v.begin() + 3;
    ft::vector<int>::reverse_iterator r_it = v.rend() - 3;
 
    std::cout << "*it == " << *it << ", *r_it.base() == " << *r_it.base()
    << '\n' << "*r_it == " << *r_it <<", *(r_it.base()-1) == " << *(r_it.base()-1) << "\n";
	std::cout << std::endl;

	std::vector<int> v1;

	for (unsigned long i = 0; i < 6; i++)
		v1.push_back(i);

    std::vector<int>::iterator it1 = v1.begin() + 3;
    std::vector<int>::reverse_iterator r_it1 = v1.rend() - 3;
 
    std::cout << "*it == " << *it1 << ", *r_it.base() == " << *r_it1.base()
    << '\n' << "*r_it == " << *r_it1 <<", *(r_it.base()-1) == " << *(r_it1.base()-1) << "\n";
  
//   {
//     RevIt r_end(v.begin());
//     RevIt r_begin(v.end());
 
//     for (auto it = r_end.base(); it != r_begin.base(); ++it) {
//       std::cout << *it << " ";
//     }
//     std::cout << "\n";
//   }
	std::cout << std::endl;

	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_end (myvector.begin());
	ft::reverse_iterator<iter_type> rev_begin (myvector.end());

	std::cout << "myvector:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::vector<int> myvector1;
	for (int i=0; i<10; i++) myvector1.push_back(i);

	typedef std::vector<int>::iterator iter_type1;

	std::reverse_iterator<iter_type1> rev_end1 (myvector1.begin());
	std::reverse_iterator<iter_type1> rev_begin1 (myvector1.end());

	std::cout << "myvector:";
	for (iter_type1 it = rev_end1.base(); it != rev_begin1.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;
}

void test_resize()
{
	std::vector<int> test1(5, 5);
	for (unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";
	std::cout << std::endl;
	test1.resize(10, 7);
	for (unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";
	std::cout << std::endl;
	test1.resize(4);
	for (unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";
	std::cout << std::endl;
	test1.resize(5);
	for (unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";
	std::cout << std::endl;

	ft::vector<int> test2(5, 5);
	for (unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";
	std::cout << std::endl;
	test2.resize(10, 7);
	for (unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";
	std::cout << std::endl;
	test2.resize(4);
	for (unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";
	std::cout << std::endl;
	test2.resize(5);
	for (unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";
	std::cout << std::endl;
}

void test_constructor()
{
	std::cout << "TEST CONSTRUCTOR" << std::endl;
	std::cout << std::endl;
	ft::vector<int> test1(5, 6);

	for (unsigned long i = 0; i < test1.size(); i++)
		std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	ft::vector<int> test2(test1);
	for (unsigned long i = 0; i < test2.size(); i++)
		std::cout << test2[i] << " ";
	std::cout << std::endl;
	
	test2[2] = 2;
	ft::vector<int>::iterator it = test2.begin();
	ft::vector<int> test3(it + 1, it + 4);

	for (unsigned long i = 0; i < test3.size(); i++)
		std::cout << test3[i] << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std::vector<int> test4(5, 6);
	test4[2] = 2;
	std::vector<int>::iterator it1 = test4.begin();
	std::vector<int> test5(it1 + 1, it1 + 4);

	for (unsigned long i = 0; i < test5.size(); i++)
		std::cout << test5[i] << " ";

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;

}

int main()
{
	test_constructor();
	// test_assing();
	// test_insert();
	// test_arase();
	// test_swap();
	// test_clear();
	// test_at();
	// test_reserve();
	// test_reverse_iterator();
	// test_base();
	// test_resize();

	// std::cout << "MY INSERT ITERATOR TEST" << std::endl;

	// ft::vector<int> test;
	// for (int i = 1; i < 10; i++)
	// 	test.push_back(i);
	// for (int i = 0; i < test.size(); i++)
	// 	std::cout << test[i] << " ";
	// ft::vector<int>::iterator it = test.begin();
	// std::cout << std::endl;

	// ft::vector<int> test2;
	// for (int i = 9; i > 0; i--)
	// 	test2.push_back(i);
	// for (int i = 0; i < test2.size(); i++)
	// 	std::cout << test2[i] << " ";
	// ft::vector<int>::iterator it1 = test2.begin();
	// std::cout << std::endl;


	// test2.insert(it1 + 1, it + 1, test.end());
	// for (int i = 0; i < test2.size(); i++)
	// 	std::cout << test2[i] << " ";

	// std::cout << "TEST OPERATOR=" << std::endl;

	// ft::vector<int>	test;
	// for (int i = 1; i < 10; i++)
	// 	test.push_back(i);
	// ft::vector<int> test2 = test;
	// // test2.push_back(1);
	// // test2 = test;
	// for(int i = 0; i < test2.size(); i++)
	// 	std::cout << test2[i] << " ";
	// while(1){}

	// std::cout << "TEST ERASE POS" << std::endl;
	// ft::vector<int> d;
	// for (int i = 1; i < 10; i++)
	// 	d.push_back(i);
	// for (int i = 0; i < d.size(); i++)	
	// 	std::cout << d[i] << " ";
	// std::cout<< "|" << d.size() << "|" << " BEGIN SIZE" << std::endl;
	// ft::vector<int>::iterator	ie = d.begin();

	// //d.reserve(20); //check it
	// d.erase(ie + 4, ie + 9);
	// for (int i = 0; i < d.size(); i++)	
	// 	std::cout << d[i] << " ";
	// std::cout<< "|" << d.size() << "|" << " END SIZE" << std::endl;
	// return 0;

}