#include "map.hpp"
#include <iostream>

int main()
{
    map_base<int, char> map(3, 'a');
    map.insert(4, 'b');
}