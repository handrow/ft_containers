#include "map.hpp"
#include <map>

template <typename iterator>
void print_iterators(iterator a, iterator b) {
    while (a != b) {
        std::cout << *a++ << " ";
    }
    std::cout << std::endl;
}

int main()
{
    ft::map<int, int> mapa;
    std::cout <<"FT: " <<  mapa.max_size();

    mapa.insert(ft::pair<int, int>(1, 2));
    mapa.insert(ft::pair<int, int>(2, 3));
    mapa.insert(ft::pair<int, int>(3, 4));
    mapa.insert(ft::pair<int, int>(4, 5));
    mapa.insert(ft::pair<int, int>(5, 6));
    std::cout << std::endl;

    std::map<int, int>  mapp;
    std::cout << "STD: " << mapp.max_size();

    
}