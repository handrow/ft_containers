#include "avl_tree.hpp"
#include <iostream>
#include <string>

// template <typename K, typename V>
// struct pair_less
// {
//     bool operator()(const std::pair<K,V>& a, const std::pair<K,V>& b) const
//     {
//         return a.first < b.first;
//     }
// };

// template <typename btree_with_pair>
// void print_map(const btree_with_pair& tree)
// {
//     for (typename btree_with_pair::iterator it = tree.begin();
//         !it.is_equal(tree.end());
//         it.next()
//     ) {
//         std::cout << "{" << it.get_data_ref().first << ", " << it.get_data_ref().second << "} ";
//     }
//     std::cout << std::endl;
// }

template <typename btree_iter>
void print_set(btree_iter first, btree_iter end)
{
    btree_iter it(first);

    while (!it.is_equal(end)) {
        std::cout << it.get_data_ref() << " ";
        it.next();
    }
    std::cout << std::endl;

    do {
        it.prev();
        std::cout << it.get_data_ref() << " ";
    } while (!it.is_equal(first));

    std::cout << std::endl;
}

// typedef ft::AVLtree<std::pair<std::string, int>, pair_less<std::string, int> >           my_map;
// typedef ft::AVLtree<std::pair<std::string, int>, pair_less<std::string, int> >::iterator my_map_iter;

typedef ft::AVLtree<int>            my_set;
typedef ft::AVLtree<int>::iterator  my_set_iter;

int main(void) {
    my_set  a;

    a.insert(2);
    a.insert(1);
    a.insert(4);
    a.insert(3);
    a.insert(6);
    a.insert(5);
    a.insert(8);
    a.insert(7);
    a.insert(10);
    a.insert(7);
    a.insert(7);

    print_set(a.begin(), a.end());

    return 0;
}