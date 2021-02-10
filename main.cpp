#include "map.hpp"
#include <map>
#include <iostream>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

template<class U, class V>
void print(map<U, V> mp)
{
    for (typename map<U, V>::iterator it = mp.begin() ; it != mp.end() ; it++)
        std::cout << "key: " << it->first << " val: " << it->second << std::endl;
}

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
    // insert<int, char>(root, 9, 'd');
    
    // map_node<int, char> *tmp;

    // // search
    // tmp = search(root, 2);
    // if (tmp)
    //     std::cout << tmp->value.first << std::endl; 
    // tmp = search(root, 10);
    // if (tmp)
    //     std::cout << tmp->value.first << std::endl; 
    // tmp = search(root, 15);
    // if (tmp)
    //     std::cout << tmp->value.first << std::endl; 
    // std::cout << "---" << std::endl;

    // // search max
    // tmp = search_max(root);
    // std::cout << tmp->value.first << std::endl;
    // tmp = search_max_parent(root);
    // std::cout << tmp->value.first << std::endl;
    // std::cout << "---" << std::endl;

    // // delete
    // print_in_order(root);
    // std::cout << "---" << std::endl;
    // delete_map_node(root, 12);
    // print_in_order(root);
    // std::cout << "---" << std::endl;
    // delete_map_node(root, 4);
    // print_in_order(root);
    // std::cout << "---" << std::endl;
    // delete_map_node(root, 6);
    // print_in_order(root);
    // std::cout << "---" << std::endl;
    // delete_map_node(root, 2);
    // print_in_order(root);
    // std::cout << "---" << std::endl;
    // delete_map_node(root, 8);
    // print_in_order(root);
    // std::cout << "---" << std::endl;
    // std::cout << "---" << std::endl;
    // // delete_map_node(root, 9);
    // // delete_map_node(root, 10);
    // // delete_map_node(root, 13);
    // // delete_map_node(root, 11);
    // delete_postfix(root);

    map<char, int> first;
    first.insert(std::pair<char, int>('b', 20));
    first.insert(std::pair<char, int>('c', 30));
    first.insert(std::pair<char, int>('a', 10));
    
    // iterator constructor
    map<char, int> second(first.begin(), first.end());
    print(second);
    
    // erase
    second.erase('b');
    second.erase('c');
    print(second);
    second.erase('a');
    print(second);
    
    // clear
    map<char, int> map1(first.begin(), first.end());
    map1.clear();

    // begin
    map<char, int> map2(first.begin(), first.end());
    print(map2);
    std::cout << "---" << std::endl;
    map<char, int>::iterator it;
    it = map2.begin();
    std::cout << it->first << std::endl;
    std::cout << (++it)->first << std::endl;
    std::cout << (++it)->first << std::endl;
    std::cout << "---" << std::endl;

    // insert
    map<int, char> map3;
    std::pair<map<int, char>::iterator, bool> p;
    map<int, char>::iterator it3;
    
    map3.insert(std::pair<char, int>(10, 'a'));
    map3.insert(std::pair<char, int>(5, 'a'));
    map3.insert(std::pair<char, int>(8, 'x'));
    map3.insert(std::pair<char, int>(15, 'a'));
    map3.insert(std::pair<char, int>(7, 'a'));

    // test insert return value
    p = map3.insert(std::pair<char, int>(1, 'a'));
    std::cout << p.second << std::endl;
    p = map3.insert(std::pair<char, int>(1, 'a'));
    std::cout << p.second << std::endl;
    std::cout << "---" << std::endl;
    it3 = p.first;
    std::cout << it3->first << std::endl;
    std::cout << (++it3)->first << std::endl;
    std::cout << (++it3)->first << std::endl;
    std::cout << (++it3)->first << std::endl;
    std::cout << (++it3)->first << std::endl;
    std::cout << (++it3)->first << std::endl;

    // iterator ++ & --
    map<int, char>::iterator it2 = map3.begin();
    map3.erase(10); // root node is erased -> doesnt alter it2
    print(map3);
    std::cout << it2->first << std::endl;
    std::cout << (++it2)->first << std::endl;
    std::cout << (++it2)->first << std::endl;
    std::cout << (++it2)->first << std::endl;
    std::cout << (it2++)->first << std::endl;
    std::cout << (it2)->first << std::endl;
    std::cout << "---" << std::endl;
    std::cout << (it2)->first << std::endl;
    std::cout << (--it2)->first << std::endl;
    std::cout << (--it2)->first << std::endl;
    std::cout << (--it2)->first << std::endl;
    std::cout << (it2--)->first << std::endl;
    std::cout << (it2)->first << std::endl;
    std::cout << "---" << std::endl;

    // iterator comparison
    std::cout << (it2 == map3.begin()) << std::endl;
    std::cout << (++it2 == map3.begin()) << std::endl;
    std::cout << (++it2 != map3.begin()) << std::endl;
    std::cout << "---" << std::endl;

    // construct const_iterator from iterator
    map<int, char>::const_iterator it4(it2);
    
    std::cout << (++it4)->first << std::endl;
    std::cout << (--it4)->first << std::endl;
    std::cout << "---" << std::endl;

    // operator =
    map<int, char> map4;
    map4.insert(std::pair<char, int>(100, 'a'));
    map4 = map3;
    print(map4);

    // // reverse iterator
    map<int, char>::reverse_iterator it5 = map4.rbegin();
    while(it5 != map4.rend())
    {
        std::cout << it5->first << std::endl;
        it5++;
    }




}