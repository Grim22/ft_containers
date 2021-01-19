
#include <iostream>
#include <vector>
#include "vector.hpp"

// using namespace std;
using namespace ft;

int main()
{
    // push back on empty vector
    vector<int> vec;
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        std::cout << "size: " << vec.size() << std::endl;   
        std::cout << "cap: " << vec.capacity() << std::endl;   
        std::cout << "---" << std::endl;
        vec.push_back(1);
    }
    
    // push back on fill vector
    vector<int> vec1(4, 8);
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        std::cout << "size: " << vec1.size() << std::endl;   
        std::cout << "cap: " << vec1.capacity() << std::endl;   
        std::cout << "---" << std::endl;
    }

    test iterator constructor: TO DO
    vector<int> vec2(vec1.begin(), vec2.end());

    
}