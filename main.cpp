#include "list.hpp"
#include <iostream>


int main()
{
    list lst(3, 12);
    std::cout << lst.back() << std::endl;
}