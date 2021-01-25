
#include <iostream>
#include <vector>
#include "vector.hpp"
#include "Fixed.hpp"


#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void displayvec(vector<int> lst)
{
    vector<int>::iterator it = lst.begin();
    while (it != lst.end())
    {
        std::cout << *it << std::endl;
        it++;
    }
    std::cout << "---" << std::endl;
}

void displayvec_reverse(vector<int> lst)
{
    vector<int>::reverse_iterator it = lst.rbegin();
    while (it != lst.rend())
    {
        std::cout << *it << std::endl;
        it++;
    }
    std::cout << "---" << std::endl;
}

int main()
{
    // capacity & size (1 - with default constuctor)
    vector<int> vec;
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        std::cout << "size: " << vec.size() << std::endl;   
        std::cout << "cap: " << vec.capacity() << std::endl;   
        std::cout << "---" << std::endl;
        vec.push_back(1);
    }
    
    // capacity & size (2 - with fill constructor)
    vector<int> vec1(5, 8);
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        std::cout << "size: " << vec1.size() << std::endl;   
        std::cout << "cap: " << vec1.capacity() << std::endl;   
        std::cout << "---" << std::endl;
        vec1.push_back(1);
    }

    // capacity & size (3 - with iterator constructor)
    vector<int> vec2(vec1.begin(), vec1.end());
    std::cout << "size: " << vec2.size() << std::endl;   
    std::cout << "cap: " << vec2.capacity() << std::endl;   
    std::cout << "---" << std::endl;

    // capacity & size (4 - with copy constructor)
    vector<int> vec3(vec1);
    std::cout << "size: " << vec3.size() << std::endl;   
    std::cout << "cap: " << vec3.capacity() << std::endl;   
    std::cout << "---" << std::endl;



    // iterator
    vector<int> vec4;
    vec4.push_back(2);
    vec4.push_back(4);
    vec4.push_back(6);
    vec4.push_back(8);

    // -- & ++
    vector<int>::iterator it = vec4.begin();
    std::cout << *++it << std::endl;
    std::cout << *++it << std::endl;
    std::cout << *--it << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << "---" << std::endl;

    // += & -=
    it = vec4.begin();
    std::cout << *it << std::endl;
    it += 3;
    std::cout << *it << std::endl;
    it -= 2;
    std::cout << *it << std::endl;
    std::cout << "---" << std::endl;
    
    // access
    it = vec4.begin();
    std::cout << it[0] << std::endl;
    std::cout << it[1] << std::endl;
    std::cout << it[2] << std::endl;
    it[3] = 55;
    std::cout << it[3] << std::endl;
    *it = 12;
    std::cout << *it << std::endl;
    std::cout << "---" << std::endl;

    // + & -
    it = vec4.begin();
    std::cout << *(it + 2) << std::endl;
    std::cout << *(2 + it) << std::endl;
    std::cout << *(it + 3 - 1) << std::endl;
    std::cout << *it << std::endl;
    std::cout << "---" << std::endl;

    // comparison
    vector<int>::iterator it2 = vec4.begin();
    it2++;
    std::cout << *it2 << std::endl;
    std::cout << (it < it2) << std::endl;
    std::cout << (it <= it2) << std::endl;
    std::cout << (it > it2) << std::endl;
    std::cout << (it >= it2) << std::endl;
    std::cout << (it == vec4.begin()) << std::endl;
    std::cout << "---" << std::endl;



    // const_iterator
    const vector<int> vec5(vec4.begin(), vec4.end());
    std::cout << "---" << std::endl;

    // -- & ++
    vector<int>::const_iterator it3 = vec5.begin();
    std::cout << *++it3 << std::endl;
    std::cout << *++it3 << std::endl;
    std::cout << *--it3 << std::endl;
    std::cout << *it3-- << std::endl;
    std::cout << "---" << std::endl;

    // += & -=
    it3 = vec5.begin();
    std::cout << *it3 << std::endl;
    it3 += 3;
    std::cout << *it3 << std::endl;
    it3 -= 2;
    std::cout << *it3 << std::endl;
    std::cout << "---" << std::endl;
    
    // access
    it3 = vec5.begin();
    std::cout << it3[0] << std::endl;
    std::cout << it3[1] << std::endl;
    std::cout << it3[2] << std::endl;
    // it3[3] = 55;
    std::cout << it3[3] << std::endl;
    // *it3 = 12;
    std::cout << *it3 << std::endl;
    std::cout << "---" << std::endl;

    // + & -
    it3 = vec5.begin();
    std::cout << *(it3 + 2) << std::endl;
    std::cout << *(2 + it3) << std::endl;
    std::cout << *(it3 + 3 - 1) << std::endl;
    std::cout << *it3 << std::endl;
    std::cout << "---" << std::endl;

    // comparison
    vector<int>::const_iterator it4 = vec5.begin();
    it4++;
    std::cout << *it4 << std::endl;
    std::cout << (it3 < it4) << std::endl;
    std::cout << (it3 <= it4) << std::endl;
    std::cout << (it3 > it4) << std::endl;
    std::cout << (it3 >= it4) << std::endl;
    std::cout << (it3 == vec5.begin()) << std::endl;
    std::cout << "---" << std::endl;
    
    // build const_iterator from iterator
    vector<int>::const_iterator it5(vec1.begin());
    std::cout << *it5 << std::endl;
    std::cout << "---" << std::endl;
    
    
    // // comp btw iterator and const it
    // vector<int>::const_iterator it3 = vec4.begin();
    // vector<int>::iterator it4 = vec4.begin();
    // std::cout << (it3 == it4) << std::endl;

    // reverse iterator and empty
    vector<int> vec6;
    std::cout << vec6.empty() << std::endl;
    vec6.push_back(2); 
    vec6.push_back(3); 
    vec6.push_back(4); 
    vec6.push_back(5);
    std::cout << vec6.empty() << std::endl;
    displayvec(vec6);
    displayvec_reverse(vec6);

    // pop back
    std::cout << "size: " << vec6.size() << std::endl;   
    std::cout << "cap: " << vec6.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    vec6.pop_back();
    vec6.pop_back();
    vec6.pop_back();
    vec6.pop_back();
    std::cout << "size: " << vec6.size() << std::endl;   
    std::cout << "cap: " << vec6.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    displayvec(vec6);

    // // assign
    vector<int> vec7(4, 6);
    vec7.assign(2, 8);
    std::cout << "size: " << vec7.size() << std::endl;   
    std::cout << "cap: " << vec7.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    displayvec(vec7);
    vec7.assign(3, 7);
    std::cout << "size: " << vec7.size() << std::endl;   
    std::cout << "cap: " << vec7.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    displayvec(vec7);

    // assign with fixed
    // Fixed a(3);
    // vector<Fixed> vec8;
    // vec8.push_back(a);
    // std::cout << "---" << std::endl;
    // vector<Fixed> vec9(4, Fixed(6));
    // std::cout << "---" << std::endl;
    // vec9.assign(1, Fixed(8));
    // std::cout << "---" << std::endl;
    // vec9.assign(3, Fixed(7));
    // std::cout << "---" << std::endl;
}