#include "map.hpp"
#include <map>


int main()
{
    ft::map<int, int> mapa;
    std::cout <<"FT: " <<  mapa.max_size();

    std::cout << std::endl;

    std::map<int, int>  mapp;
    std::cout << "STD: " << mapp.max_size();

    
}