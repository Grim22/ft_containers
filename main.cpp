#include "map.hpp"
#include <map>
#include <iostream>

using namespace ft;

int main()
{
    map_node<int, char> *root;
    root = new map_node<int, char>(8, 'c');
    insert<int, char>(root, 4, 'b');
    insert<int, char>(root, 12, 'd');
    insert<int, char>(root, 11, 'd');
    insert<int, char>(root, 13, 'd');
    insert<int, char>(root, 2, 'd');
    insert<int, char>(root, 6, 'd');
    insert<int, char>(root, 10, 'd');
    insert<int, char>(root, 9, 'd');
    
    map_node<int, char> *tmp;

    // search
    tmp = search(root, 2);
    if (tmp)
        std::cout << tmp->key << std::endl; 
    tmp = search(root, 10);
    if (tmp)
        std::cout << tmp->key << std::endl; 
    tmp = search(root, 15);
    if (tmp)
        std::cout << tmp->key << std::endl; 
    std::cout << "---" << std::endl;

    // search max
    tmp = search_max(root);
    std::cout << tmp->key << std::endl;
    tmp = search_max_parent(root);
    std::cout << tmp->key << std::endl;
    std::cout << "---" << std::endl;

    // delete
    print_in_order(root);
    std::cout << "---" << std::endl;
    delete_map_node(root, 12);
    print_in_order(root);
    std::cout << "---" << std::endl;
    delete_map_node(root, 4);
    print_in_order(root);
    std::cout << "---" << std::endl;
    delete_map_node(root, 6);
    print_in_order(root);
    std::cout << "---" << std::endl;
    delete_map_node(root, 2);
    print_in_order(root);
    std::cout << "---" << std::endl;
    delete_map_node(root, 8);
    print_in_order(root);
    std::cout << "---" << std::endl;
    std::cout << "---" << std::endl;

    std::map<char, int> first;
    first['b'] = 20;
    first['c'] = 30;
    first['a'] = 10;
    std::cout << first.begin()->first << std::endl;
    std::cout << "---" << std::endl;
    ft::map<char, int> second(first.begin(), first.end());
    second.print();
    std::cout << second.root->key << std::endl;
    std::cout << second.root->left << std::endl;
    std::cout << second.root->right << std::endl;
    second.erase('b');
    second.erase('c');
    std::cout << "---" << std::endl;
    second.print();
    // second.erase('a'); // not working


}