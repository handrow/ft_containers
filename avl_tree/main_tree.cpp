#include "USSRtree.hpp"
#include <map>

int main(void) {
    ft::AVLtree<int>  tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);

    tree.printBT();
    tree.remove(1);
    std::cout << "=================\n";
    tree.printBT();
    tree.remove(2);
    std::cout << "=================\n";
    tree.printBT();
    tree.remove(3);
    std::cout << "=================\n";
    tree.printBT();
    tree.remove(4);
    std::cout << "=================\n";
    tree.printBT();
    tree.remove(5);
    std::cout << "=================\n";
    tree.printBT();
    tree.remove(6);
    std::cout << "=================\n";
    tree.printBT();
    tree.remove(7);
    std::cout << "=================\n";
    tree.printBT();
    tree.remove(8);
    std::cout << "=================\n";
    tree.printBT();
    return 0;
}