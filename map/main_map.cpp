#include "map.hpp"
#include <map>

template <typename iterator>
void print_iterators(iterator a, iterator b) {
    while (a != b) {
        std::cout << *a++ << " ";
    }
    std::cout << std::endl;
}

template<class _Map>
void print_map(_Map& m)
{
    typename _Map::iterator it = m.begin();
    typename _Map::iterator end = m.end();
    while (it != end)
    {
        std::cout << "{" << it->first << "=" << it->second << "} ";
        it++;
    }
    std::cout << std::endl;
}

void test_ft_constructor()
{
    ft::map<std::string, int> def;
    def.insert(ft::pair<std::string, int>("a", 1));
    def.insert(ft::pair<std::string, int>("b", 2));
    def.insert(ft::pair<std::string, int>("c", 3));
    def.insert(ft::pair<std::string, int>("d", 4));
    def.insert(ft::pair<std::string, int>("e", 5));
    def.insert(ft::pair<std::string, int>("b", 10));
    print_map(def);
}

int main()
{
    test_ft_constructor();
}