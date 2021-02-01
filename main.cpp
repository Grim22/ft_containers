
#include <iostream>
#include <vector>
#include "vector.hpp"
#include <list>
// #include "Fixed.hpp"


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
    std::list<int> lst(4, 8);
    
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
    // input iterator sent
    vector<int> vec2b(lst.begin(), lst.end());
    std::cout << "size: " << vec2b.size() << std::endl;   
    std::cout << "cap: " << vec2b.capacity() << std::endl;   
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

    // reserve
    vector<int>vec10(4, 8);
    vec10.reserve(15);

    std::cout << "size: " << vec10.size() << std::endl;   
    std::cout << "cap: " << vec10.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    displayvec(vec10);

    // op =
    vector<int>vec11(5, 9);
    vec11 = vec10;
    std::cout << "size: " << vec11.size() << std::endl;   
    std::cout << "cap: " << vec11.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    displayvec(vec11);
    vec11 = vector<int>(6, 10);
    std::cout << "size: " << vec11.size() << std::endl;   
    std::cout << "cap: " << vec11.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    displayvec(vec11);

    // assign iterator
    vector<int> vec12(3, 9);
    vec12.assign(vec10.begin(), vec10.end());
    std::cout << "size: " << vec12.size() << std::endl;   
    std::cout << "cap: " << vec12.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    displayvec(vec12);

    // assign iterator with inputiterator
    vec12.assign(++lst.begin(), --lst.end());
    std::cout << "size: " << vec12.size() << std::endl;   
    std::cout << "cap: " << vec12.capacity() << std::endl;   
    std::cout << "---" << std::endl;
    displayvec(vec12);

    // resize
    vector<int> vec13;
    vec13.push_back(3);
    vec13.push_back(3);
    vec13.push_back(3);
    vec13.push_back(3);
    vec13.push_back(3);
    std::cout << "size: " << vec13.size() << std::endl;   
    std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.resize(17); // n > 2 * cap
    std::cout << "size: " << vec13.size() << std::endl;   
    std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.push_back(3);
    std::cout << "size: " << vec13.size() << std::endl;   
    std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.resize(40, 4); // n < 2 * cap && n > cap
    std::cout << "size: " << vec13.size() << std::endl;   
    // std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.resize(50, 5); // n < cap && n > size
    std::cout << "size: " << vec13.size() << std::endl;
    // std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.resize(45); // n < size
    std::cout << "size: " << vec13.size() << std::endl;
    // std::cout << "cap: " << vec13.capacity() << std::endl;
    displayvec(vec13);

    // max size
    std::cout << vec13.max_size() << std::endl;

    // element access
    std::cout << vec13.back() << std::endl;
    std::cout << vec13.front() << std::endl;
    std::cout << vec13[3] << std::endl;
    std::cout << vec13[5] << std::endl;
    std::cout << vec13[15] << std::endl;
    try
    {
        std::cout << vec13.at(115) << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    // insert with iterators
    vector<int> vec14;
    vec14.push_back(0);
    vec14.push_back(1);
    vec14.push_back(2);
    vec14.push_back(3);
    vec14.push_back(4);
    vector<int> vec15;
    vec15.push_back(8);
    vec15.push_back(9);
    vec15.push_back(10);
    vec15.push_back(11);
    vec14.insert(vec14.begin() + 2, vec15.begin(), vec15.begin() + 2);
    std::cout << "size: " << vec14.size() << std::endl;
    // std::cout << "cap: " << vec14.capacity() << std::endl;
    vec14.insert(vec14.end(), vec15.begin(), vec15.end());
    std::cout << "size: " << vec14.size() << std::endl;
    // std::cout << "cap: " << vec14.capacity() << std::endl;
    vec14.insert(vec14.begin(), vec15.begin(), vec15.end());
    std::cout << "size: " << vec14.size() << std::endl;
    // std::cout << "cap: " << vec14.capacity() << std::endl;
    vec14.insert(vec14.begin(), vec15.begin(), vec15.begin());
    std::cout << "size: " << vec14.size() << std::endl;
    // std::cout << "cap: " << vec14.capacity() << std::endl;
    displayvec(vec14);

    // insert with input iterators
    vec14.insert(vec14.begin(), lst.begin(), lst.end());
    std::cout << "size: " << vec14.size() << std::endl;
    displayvec(vec14);

    vector<int> vec17;
    vec17.insert(vec17.begin(), vec15.begin(), vec15.end());
    std::cout << "size: " << vec14.size() << std::endl;
    // std::cout << "cap: " << vec14.capacity() << std::endl;
    displayvec(vec14);

    // insert range
    vec17.insert(vec17.begin(), 4, 70);
    std::cout << "size: " << vec17.size() << std::endl;
    // std::cout << "cap: " << vec17.capacity() << std::endl;
    vec17.insert(vec17.begin(), 20, 90);
    std::cout << "size: " << vec17.size() << std::endl;
    // std::cout << "cap: " << vec17.capacity() << std::endl;
    displayvec(vec17);

    // insert single
    std::cout << "ret: " << *vec15.insert(vec15.begin(), 99) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    // std::cout << "cap: " << vec15.capacity() << std::endl;
    std::cout << "ret: " << *vec15.insert(vec15.begin(), 96) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    // std::cout << "cap: " << vec15.capacity() << std::endl;
    std::cout << "ret: " << *vec15.insert(vec15.begin(), 93) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    // std::cout << "cap: " << vec15.capacity() << std::endl;
    std::cout << "ret: " << *vec15.insert(vec15.begin(), 90) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    // std::cout << "cap: " << vec15.capacity() << std::endl;
    std::cout << "ret: " << *vec15.insert(vec15.end(), 87) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    // std::cout << "cap: " << vec15.capacity() << std::endl;
    displayvec(vec15);

    // erase iterator / single
    vector<int>vec18;
    vec18.push_back(1);
    vec18.push_back(2);
    vec18.push_back(3);
    vec18.push_back(4);
    vec18.push_back(5);
    vec18.push_back(6);
    vec18.push_back(7);
    std::cout << "size: " << vec18.size() << std::endl;
    std::cout << "cap: " << vec18.capacity() << std::endl;
    std::cout << "---" << std::endl;
    
    vector<int>::iterator it6;
    it6 = vec18.erase(vec18.begin(), vec18.begin() + 1);
    if (it6 != vec18.end())
        std::cout << "ret: " << *it6 << std::endl;
    std::cout << "size: " << vec18.size() << std::endl;
    std::cout << "cap: " << vec18.capacity() << std::endl;
    displayvec(vec18);
    
    it6 = vec18.erase(vec18.begin() + 1, vec18.begin() + 2);
    if (it6 != vec18.end())
        std::cout << "ret: " << *it6 << std::endl;
    std::cout << "size: " << vec18.size() << std::endl;
    std::cout << "cap: " << vec18.capacity() << std::endl;
    displayvec(vec18);
    
    it6 = vec18.erase(vec18.end() - 2, vec18.end());
    if (it6 != vec18.end())
        std::cout << "ret: " << *it6 << std::endl;
    std::cout << "size: " << vec18.size() << std::endl;
    std::cout << "cap: " << vec18.capacity() << std::endl;
    displayvec(vec18);
    
    it6 = vec18.erase(vec18.begin()); // erase single
    if (it6 != vec18.end())
        std::cout << "ret: " << *it6 << std::endl;
    std::cout << "size: " << vec18.size() << std::endl;
    std::cout << "cap: " << vec18.capacity() << std::endl;
    displayvec(vec18);

    it6 = vec18.erase(vec18.begin(), vec18.end());
    if (it6 != vec18.end())
        std::cout << "ret: " << *it6 << std::endl;
    std::cout << "size: " << vec18.size() << std::endl;
    std::cout << "cap: " << vec18.capacity() << std::endl;
    displayvec(vec18);

    // clear
    vec15.clear();
    std::cout << "size: " << vec15.size() << std::endl;
    std::cout << "cap: " << vec15.capacity() << std::endl;
    displayvec(vec15);
    vector<int>vec19;
    vec19.clear();
    std::cout << "size: " << vec19.size() << std::endl;
    std::cout << "cap: " << vec19.capacity() << std::endl;
    displayvec(vec19);

    //  swap
    vec15.assign(3, 5);
    vec15.swap(vec19);
    std::cout << "size: " << vec19.size() << std::endl;
    std::cout << "cap: " << vec19.capacity() << std::endl;
    displayvec(vec19);
    std::cout << "size: " << vec15.size() << std::endl;
    std::cout << "cap: " << vec15.capacity() << std::endl;
    displayvec(vec15);
    vec15.swap(vec19);
    std::cout << "size: " << vec19.size() << std::endl;
    std::cout << "cap: " << vec19.capacity() << std::endl;
    displayvec(vec19);
    std::cout << "size: " << vec15.size() << std::endl;
    std::cout << "cap: " << vec15.capacity() << std::endl;
    displayvec(vec15);

   // relationnal op
   vec19.clear();
   vec18.clear();
   vec17.clear();
   vec17.assign(4, 12);
   vec18.assign(3, 12);
   vec19.push_back(12);
   vec19.push_back(12);
   vec19.push_back(10);
   vec19.push_back(12);
   vector<int> vec20(4, 12);
   std::cout << (vec17 == vec18) << std::endl;
   std::cout << (vec17 == vec19) << std::endl;
   std::cout << (vec17 == vec20) << std::endl;
    std::cout << "---" << std::endl;
   std::cout << (vec17 != vec18) << std::endl;
   std::cout << (vec17 != vec19) << std::endl;
   std::cout << (vec17 != vec20) << std::endl;
    std::cout << "---" << std::endl;
   std::cout << (vec17 > vec18) << std::endl;
   std::cout << (vec17 > vec19) << std::endl;
   std::cout << (vec17 > vec20) << std::endl;
    std::cout << "---" << std::endl;
   std::cout << (vec17 >= vec18) << std::endl;
   std::cout << (vec17 >= vec19) << std::endl;
   std::cout << (vec17 >= vec20) << std::endl;
    std::cout << "---" << std::endl;
   std::cout << (vec17 < vec18) << std::endl;
   std::cout << (vec17 < vec19) << std::endl;
   std::cout << (vec17 < vec20) << std::endl;
    std::cout << "---" << std::endl;
   std::cout << (vec17 <= vec18) << std::endl;
   std::cout << (vec17 <= vec19) << std::endl;
   std::cout << (vec17 <= vec20) << std::endl;

    
}