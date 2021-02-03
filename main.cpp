#include "map.hpp"
#include <iostream>

int main()
{
    node<int, char> *root;
    root = new node<int, char>(8, 'c');
    insert<int, char>(root, 4, 'b');
    insert<int, char>(root, 12, 'd');
    insert<int, char>(root, 11, 'd');
    insert<int, char>(root, 13, 'd');
    insert<int, char>(root, 2, 'd');
    insert<int, char>(root, 6, 'd');
    insert<int, char>(root, 10, 'd');
    
    node<int, char> *tmp;
    tmp = root;
    while (tmp->left)
        tmp = tmp->left;
    std::cout << tmp->key << std::endl; 
    
    tmp = root;
    while (tmp->right)
        tmp = tmp->right;
    std::cout << tmp->key << std::endl; 
    
    tmp = root;
    tmp = tmp->left;
    std::cout << tmp->key << std::endl; 
    std::cout << tmp->left->key << std::endl; 
    std::cout << tmp->right->key << std::endl; 

    // map.insert(10, 'd');
    // map.insert(40, 'f');
    // map.insert(1, 't');
    // std::cout << map.base->key << " " << map.base->value;
    // std::cout << map.base->left->key << " " << map.base->value;
    // std::cout << map.base->right->key << " " << map.base->value;
}