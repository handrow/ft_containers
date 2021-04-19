#include "USSRtree.hpp"
#include <map>

template <typename K, typename V>
struct pair_less
{
    bool operator()(const std::pair<K,V>& a, const std::pair<K,V>& b) const
    {
        return a.first < b.first;
    }
};

template <typename btree_with_pair>
void print_map(const btree_with_pair& tree)
{
    for (typename btree_with_pair::iterator it = tree.begin();
        !it.is_equal(tree.end());
        it.next()
    ) {
        std::cout << "{" << it.get_data_ref().first << ", " << it.get_data_ref().second << "} ";
    }
    std::cout << std::endl;
}

template <typename btree>
void print_set(const btree& tree)
{
    for (typename btree::iterator it = tree.begin();
        !it.is_equal(tree.end());
        it.next()
    ) {
        std::cout << it.get_data_ref() << " ";
    }
    std::cout << std::endl;
}

typedef ft::AVLtree<std::pair<std::string, int>, pair_less<std::string, int> >           my_map;
typedef ft::AVLtree<std::pair<std::string, int>, pair_less<std::string, int> >::iterator my_map_iter;

typedef ft::AVLtree<std::string>            my_set;
typedef ft::AVLtree<std::string>::iterator  my_set_iter;

int main(void) {
    my_map tree;

    tree.insert(std::make_pair("a", 1));
    tree.insert(std::make_pair("b", 2));
    tree.insert(std::make_pair("c", 3));
    tree.insert(std::make_pair("d", 4));
    tree.insert(std::make_pair("e", 5));
    tree.insert(std::make_pair("lol", 1000));
    tree.insert(std::make_pair("lol", 1001));
    tree.insert(std::make_pair("lol", 1002));
    tree.insert(std::make_pair("lol", 1003));
    print_map(tree);

    return 0;
}