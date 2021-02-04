#include "map.hpp"
#include <map>
#include <iostream>

using namespace ft;

int main()
{
    // map_node<int, char> *root;
    // root = new map_node<int, char>(8, 'c');
    // insert<int, char>(root, 4, 'b');
    // insert<int, char>(root, 12, 'd');
    // insert<int, char>(root, 11, 'd');
    // insert<int, char>(root, 13, 'd');
    // insert<int, char>(root, 2, 'd');
    // insert<int, char>(root, 6, 'd');
    // insert<int, char>(root, 10, 'd');
    
    // map_node<int, char> *tmp;
    // tmp = root;
    // while (tmp->left)
    //     tmp = tmp->left;
    // std::cout << tmp->key << std::endl; 
    
    // tmp = root;
    // while (tmp->right)
    //     tmp = tmp->right;
    // std::cout << tmp->key << std::endl; 
    
    // tmp = root;
    // tmp = tmp->left;
    // std::cout << tmp->key << std::endl; 
    // std::cout << tmp->left->key << std::endl; 
    // std::cout << tmp->right->key << std::endl; 

    // search
    // tmp = search(root, 2);
    // if (tmp)
    //     std::cout << tmp->key << std::endl; 
    // tmp = search(root, 10);
    // if (tmp)
    //     std::cout << tmp->key << std::endl; 
    // tmp = search(root, 15);
    // if (tmp)
    //     std::cout << tmp->key << std::endl; 

    // search min
    // tmp = search_min(root->right);
    // std::cout << tmp->key << std::endl;

    // print_in_order(root);
    // // delete
    // delete_map_node(root, 12);
    // delete_map_node(root, 11);
    // delete_map_node(root, 10);
    // delete_map_node(root, 4);
    // delete_map_node(root, 6);
    // delete_map_node(root, 13);
    // delete_map_node(root, 11);
    // std::cout << root->left->key << std::endl;

    std::map<char, int> first;
    first['b'] = 20;
    first['c'] = 30;
    first['a'] = 10;
    std::cout << first.begin()->first << std::endl;
    std::cout << "---" << std::endl;
    // ft::map<char, int> second(first.begin(), first.end());
    // second.print();


}