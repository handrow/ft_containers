#include <map>
#include "red_black_tree.hpp"

int main()
{
    ft::RBT<int> tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);

    // std::cout << tree.root->data << " ";
    // std::cout << tree.root->left->data << " ";
    // std::cout << tree.root->right->left->data << " ";
    // std::cout << tree.root->right->data;

    std::cout << std::endl;
}