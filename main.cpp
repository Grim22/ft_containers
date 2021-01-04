#include "list.hpp"
#include <iostream>


int main()
{
    ft::list lst;
    lst.push_back(5);
    lst.push_back(6);
    std::cout << lst.front() << std::endl;
    ft::list lst2(4, 7);
    std::cout << lst2.back() << std::endl;
}