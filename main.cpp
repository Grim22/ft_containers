#include "list.hpp"
#include "map.hpp"
#include "vector.hpp"
#include "queue.hpp"
#include "stack.hpp"

#include <stack>
#include <map>
#include <queue>
#include <vector>
#include <list>

#include <iostream>
#include <cmath> // fabs

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void displaylst(list<int> lst)
{
    list<int>::iterator it = lst.begin();
    while (it != lst.end())
    {
        std::cout << *it << std::endl;
        it++;
    }
    std::cout << "---" << std::endl;
}
void displaylst_reverse(list<int> lst)
{
    list<int>::reverse_iterator it = lst.rbegin();
    while (it != lst.rend())
    {
        std::cout << *it << std::endl;
        it++;
    }
    std::cout << "---" << std::endl;
}

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

template<class U, class V>
void print(map<U, V> mp)
{
    for (typename map<U, V>::iterator it = mp.begin() ; it != mp.end() ; it++)
    {
        std::cout << "key: " << it->first;
        std::cout << " val: " << it->second;
        std::cout << std::endl;
    }
    std::cout << "---" << std::endl;
    
}

// a predicate implemented as a function:
bool single_digit(const int& value)
{ 
    return (value<10); 
}

// a predicate implemented as a class:
struct is_odd 
{
    bool operator() (const int& value) 
    { 
        return (value%2)==1; 
    }
};

// a binary predicate implemented as a function:
bool same_parity (int first, int second)
{ return ( first % 2 == second % 2 ); }

// a binary comp function
bool compare_custom(int first, int second)
{
    if (first % 10 < second % 10)
        return true;
    return false;
    // return (first % 10 < second % 10);
}

// useful because template arguments dont have to be specified: they are deduced from the function argument
// (class template argument deduction is not available untin c++17, so when using std::pair, template arguments have to be provided explicitely)
template<class U, class V>
std::pair<U,V> make_pairs(U u, V v)
{
    return std::pair<U, V>(u, v);
}

template<class T>
bool my_less(T a, T b)
{
    return (a < b);
}

template<class T>
class my_less_class
{
    public:
    bool operator()(T a, T b) const
    {
        return (a < b);
    }
};

template<class T>
class my_less_class_with_state
{
    private:
    int state;
    public:
    my_less_class_with_state(): state(0) {};
    my_less_class_with_state(int state): state(state) {};
    bool operator()(T a, T b) const
    {
        if (state >= 0)
            return (a < b);
        else
            return (a > b);
    }
};

template<class T>
class my_reverse_less_class
{
    public:
    bool operator()(T a, T b) const
    {
        return (a > b);
    }
};


int main()
{
#ifdef LIST
{
    std::cout << std::endl;
    std::cout << "LIST" << std::endl;
    std::cout << std::endl;
    
    list<int> lst;
    lst.push_back(9);
    lst.push_back(19);
    lst.push_back(49);
    displaylst_reverse(lst);
    list<int> lst2(5, 7);
    std::cout << lst2.size() << std::endl;
    list<int> lst3(lst2);
    std::cout << lst3.size() << std::endl;
    lst3 = lst;
    std::cout << lst3.size() << std::endl;

    // pop_back, pop front, assign
    list<int> lst4(4, 8);
    lst4.push_front(5);
    std::cout << "back:" << lst4.back() << std::endl;
    displaylst(lst4);
    lst4.pop_back();
    lst4.pop_back();
    lst4.pop_back();
    lst4.pop_back();
    // lst4.pop_back();
    // lst4.pop_back();
    displaylst(lst4);
    list<int> lst5;
    lst5.push_front(22);
    lst5.push_back(50);
    lst5.pop_front();
    lst5.pop_front();
    // lst5.pop_front();
    displaylst(lst5);
    lst5.assign(4, 9);
    displaylst(lst5);
    lst5 = lst4;
    displaylst(lst5);

    // swap
    list<int> lst6(4, 8);
    list<int> lst7(3, 7);
    lst6.swap(lst7);
    displaylst(lst6);
    displaylst(lst7);
    swap(lst6, lst7);
    displaylst(lst6);
    displaylst(lst7);

    // resize
    list<int> lst8;
    lst8.push_front(2);
    lst8.push_front(22);
    lst8.push_front(222);
    lst8.push_front(2222);
    lst8.resize(8, 3);
    displaylst(lst8);
    lst8.resize(1);
    displaylst(lst8);

    // remove
    list<int> lst9(4, 2);
    lst9.push_back(3);
    lst9.push_front(4);
    lst9.remove(4);
    lst9.remove(2);
    // lst9.remove(3);
    displaylst(lst9);

    // remove if
    list<int> lst10;
    lst10.push_back(3);
    lst10.push_back(5);
    lst10.push_back(6);
    lst10.push_back(60);
    lst10.push_back(61);
    lst10.remove_if(single_digit);
    lst10.remove_if(is_odd());
    displaylst(lst10);

    // unique
    list<int> lst11;
    lst11.push_back(5);
    lst11.push_back(4);
    lst11.push_back(5);
    lst11.push_back(6);
    lst11.push_back(6);
    lst11.push_back(5);
    lst11.push_back(5);
    lst11.unique();
    displaylst(lst11);

    // unique with binarypred
    list<int> lst12;
    lst12.push_back(5);
    lst12.push_back(8);
    lst12.push_back(10);
    lst12.push_back(12);
    lst12.push_back(5);
    lst12.push_back(5);
    lst12.push_back(50);
    lst12.push_back(7);
    lst12.push_back(9);
    lst12.unique(same_parity);
    displaylst(lst12);

    // sort
    list<int> lst13;
    lst13.push_back(5);
    lst13.push_back(8);
    lst13.push_back(3);
    lst13.push_back(8);
    lst13.push_back(1);
    displaylst(lst13);
    lst13.sort();
    displaylst(lst13);

    // sort with binary compare
    list<int> lst14;
    lst14.push_back(18);
    lst14.push_back(48);
    lst14.push_back(42);
    lst14.push_back(1000);
    lst14.push_back(188);
    displaylst(lst14);
    lst14.sort(compare_custom);
    displaylst(lst14);

    //reverse
    list<int> lst15;
    lst15.push_back(4);
    lst15.push_back(22);
    lst15.push_back(23);
    lst15.push_back(12);
    lst15.reverse();
    displaylst(lst15);

    // iterator
    list<int> lst16;
    lst16.push_back(2);
    lst16.push_back(4);
    lst16.push_back(9);
    for (list<int>::iterator it = lst16.begin(); it != lst16.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    // const iterator
    list<int> lst17(4, 8);
    const list<int> lst18(lst17);
    for (list<int>::const_iterator it = lst18.begin(); it != lst18.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    // reverse iterator
    list<int> lst19;
    lst19.push_back(4);
    lst19.push_back(3);
    lst19.push_back(1);
    lst19.push_back(9);
    for (list<int>::reverse_iterator it = lst19.rbegin(); it != lst19.rend(); it++)
    {
        std::cout << *it << std::endl;
    }

    // iterator constructor
    list<int> lst20;
    lst20.push_back(12);
    lst20.push_back(14);
    lst20.push_back(134);
    lst20.push_back(1354);
    list<int> lst21a(lst20.begin(), lst20.end());
    displaylst(lst21a);
    list<int>::iterator it = lst20.begin();
    ++it;
    list<int> lst21b(it, ++it); // 1st arg is also incremented: both args are ++it
    displaylst(lst21b);
    
    // // // iterator assign
    list<int> lst22(2, 4);
    std::cout << "it is: " << *it << std::endl;
    lst22.assign(it, lst20.end());
    displaylst(lst22);

    // insert
    list<int> lst23;
    lst23.push_back(12);
    lst23.push_back(122);
    lst23.push_back(212);
    lst23.push_back(12222);
    list<int>::iterator it3 = lst23.begin();
    list<int>::iterator it4 = lst23.insert(++it3, 88);
    displaylst(lst23);
    std::cout << "inserted element is: " << *it4 << std::endl;
    std::cout << "---" << std::endl;

    // // insert multiple
    list<int> lst25;
    lst25.push_back(3);
    lst25.push_back(6);
    lst25.push_back(0);
    lst25.insert(lst25.begin(), 3, 8);
    displaylst(lst25);
    

    // // // // insert multiple with iterator
    list<int> lst26;
    lst26.push_back(9);
    lst26.push_back(1);
    lst26.push_back(12);
    lst26.insert(++lst26.begin(), ++lst25.begin(), lst25.end());
    displaylst(lst26);

    // erase
    list<int> lst27;
    lst27.push_back(4);
    lst27.push_back(42);
    lst27.push_back(422);
    lst27.push_back(8422);
    list<int>::iterator it6 = lst27.begin();
    it6 = lst27.erase(it6++);
    displaylst(lst27);
    std::cout << "element that followed: " <<  *it6 << std::endl;
    std::cout << "---" << std::endl;
    lst27.erase(++it6);
    displaylst(lst27);

    // erase with iterator
    list<int> lst28;
    lst28.push_back(4);
    lst28.push_back(49);
    lst28.push_back(44);
    lst28.push_back(45);
    lst28.erase(lst28.begin(), ++lst28.begin());
    displaylst(lst28);

    // // splice (whole list<int>)
    list<int> lst29;
    lst29.push_back(4);
    lst29.push_back(42);
    lst29.push_back(44);
    list<int> lst30;
    lst30.push_back(8);
    lst30.push_back(12);
    lst29.splice(++lst29.begin(), lst30);
    displaylst(lst29);
    displaylst(lst30);
    
    // // // splice (one elem)
    lst30.push_back(5);
    lst30.push_back(512);
    lst29.splice(lst29.begin(), lst30, lst30.begin());
    displaylst(lst29);
    displaylst(lst30);
    // special case where the two list<int>s are the same
    lst29.splice(lst29.begin(), lst29, ++lst29.begin());
    displaylst(lst29);

    // // // splice (elems between two iterators)
    list<int> lst31;
    lst31.push_back(66);
    lst31.push_back(166);
    lst31.push_back(766);
    lst31.push_back(3166);
    lst29.splice(lst29.begin(), lst31, lst31.begin(), ++lst31.begin());
    displaylst(lst29);

    // // merge
    list<int> lst32;
    lst32.push_back(2);
    lst32.push_back(4);
    lst32.push_back(9);
    list<int> lst33;
    lst33.push_back(2);
    lst33.push_back(5);
    lst33.push_back(7);
    lst33.push_back(19);
    lst33.push_back(29);
    lst32.merge(lst33);
    displaylst(lst32);
    displaylst(lst33);

    // // merge with comp
    list<int> lst34;
    lst34.push_back(33);
    lst34.push_back(27);
    lst34.push_back(2);
    lst34.sort(compare_custom);
    displaylst(lst34);
    list<int> lst35;
    lst35.push_back(4);
    lst35.push_back(110);
    lst35.push_back(11);
    lst35.push_back(222);
    lst35.sort(compare_custom);
    displaylst(lst35);
    lst34.merge(lst35, compare_custom);
    displaylst(lst34);
    displaylst(lst35);

    // relationnal operators

    list<int> lst36;
    lst36.push_back(3);
    lst36.push_back(5);
    lst36.push_back(7);
    list<int> lst37;
    lst37.push_back(3);
    lst37.push_back(5);
    lst37.push_back(7);
    list<int> lst38;
    lst38.push_back(3);
    lst38.push_back(5);
    lst38.push_back(7);
    lst38.push_back(17);
    list<int> lst39;
    lst39.push_back(2);
    lst39.push_back(4);
    lst39.push_back(6);

    std::cout << (lst36 == lst37) << std::endl;
    std::cout << (lst36 == lst38) << std::endl;
    std::cout << (lst36 == lst39) << std::endl;
    std::cout << "---" << std::endl;
    std::cout << (lst36 != lst37) << std::endl;
    std::cout << (lst36 != lst38) << std::endl;
    std::cout << (lst36 != lst39) << std::endl;
    std::cout << "---" << std::endl;
    std::cout << (lst36 < lst37) << std::endl;
    std::cout << (lst36 < lst38) << std::endl;
    std::cout << (lst36 < lst39) << std::endl;
    std::cout << "---" << std::endl;
    std::cout << (lst36 <= lst37) << std::endl;
    std::cout << (lst36 <= lst38) << std::endl;
    std::cout << (lst36 <= lst39) << std::endl;
    std::cout << "---" << std::endl;
    std::cout << (lst36 > lst37) << std::endl;
    std::cout << (lst36 > lst38) << std::endl;
    std::cout << (lst36 > lst39) << std::endl;
    std::cout << "---" << std::endl;
    std::cout << (lst36 >= lst37) << std::endl;
    std::cout << (lst36 >= lst38) << std::endl;
    std::cout << (lst36 >= lst39) << std::endl;

    list<int> lst40;
    std::cout << lst40.max_size() << std::endl;

    // const_iterator built from iterator
    list<int> lst41(4, 8);
    list<int>::iterator it7(lst41.begin());
    std::cout << *it7 << std::endl;

    // compare const_iterator and iterator
    list<int>::iterator it8 = lst41.begin();
    list<int>::const_iterator it9 = lst41.begin();
    std::cout << (it8 == it9) << std::endl;
    std::cout << (it9 == it8) << std::endl;
    std::cout << (it8 != it9) << std::endl;
    std::cout << (it9 != it8) << std::endl;
}
#endif

#ifdef VECTOR
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
    vec13.push_back(3);
    std::cout << "size: " << vec13.size() << std::endl;   
    std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.resize(13); // n > 2 * cap
    std::cout << "size: " << vec13.size() << std::endl;   
    std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.push_back(3);
    std::cout << "size: " << vec13.size() << std::endl;   
    std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.resize(40, 4); // n < 2 * cap && n > cap
    std::cout << "size: " << vec13.size() << std::endl;   
    std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.resize(50, 5); // n < cap && n > size
    std::cout << "size: " << vec13.size() << std::endl;
    std::cout << "cap: " << vec13.capacity() << std::endl;
    vec13.resize(45); // n < size
    std::cout << "size: " << vec13.size() << std::endl;
    std::cout << "cap: " << vec13.capacity() << std::endl;
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
    std::cout << "cap: " << vec14.capacity() << std::endl;
    vec14.insert(vec14.end(), vec15.begin(), vec15.end());
    std::cout << "size: " << vec14.size() << std::endl;
    std::cout << "cap: " << vec14.capacity() << std::endl;
    vec14.insert(vec14.begin(), vec15.begin(), vec15.end());
    std::cout << "size: " << vec14.size() << std::endl;
    std::cout << "cap: " << vec14.capacity() << std::endl;
    vec14.insert(vec14.begin(), vec15.begin(), vec15.begin());
    std::cout << "size: " << vec14.size() << std::endl;
    std::cout << "cap: " << vec14.capacity() << std::endl;
    displayvec(vec14);

    // insert with input iterators
    vec14.insert(vec14.begin(), lst.begin(), lst.end());
    std::cout << "size: " << vec14.size() << std::endl;
    displayvec(vec14);

    vector<int> vec17;
    vec17.insert(vec17.begin(), vec15.begin(), vec15.end());
    std::cout << "size: " << vec14.size() << std::endl;
    std::cout << "cap: " << vec14.capacity() << std::endl;
    displayvec(vec14);

    // insert range
    vec17.insert(vec17.begin(), 4, 70);
    std::cout << "size: " << vec17.size() << std::endl;
    std::cout << "cap: " << vec17.capacity() << std::endl;
    vec17.insert(vec17.begin(), 20, 90);
    std::cout << "size: " << vec17.size() << std::endl;
    std::cout << "cap: " << vec17.capacity() << std::endl;
    displayvec(vec17);

    // insert single
    std::cout << "ret: " << *vec15.insert(vec15.begin(), 99) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    std::cout << "cap: " << vec15.capacity() << std::endl;
    std::cout << "ret: " << *vec15.insert(vec15.begin(), 96) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    std::cout << "cap: " << vec15.capacity() << std::endl;
    std::cout << "ret: " << *vec15.insert(vec15.begin(), 93) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    std::cout << "cap: " << vec15.capacity() << std::endl;
    std::cout << "ret: " << *vec15.insert(vec15.begin(), 90) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    std::cout << "cap: " << vec15.capacity() << std::endl;
    std::cout << "ret: " << *vec15.insert(vec15.end(), 87) << std::endl;
    std::cout << "size: " << vec15.size() << std::endl;
    std::cout << "cap: " << vec15.capacity() << std::endl;
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
    std::cout << "CLEAR" << std::endl;
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
    std::cout << "SWAP" << std::endl;
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
#endif

#ifdef MAP
{
    // insert
    map<int, char> map3;
    std::pair<map<int, char>::iterator, bool> p;
    map<int, char>::iterator it3;
    map3.insert(make_pairs(10, 'a'));
    map3.insert(make_pairs(5, 'a'));
    map3.insert(make_pairs(8, 'x'));
    map3.insert(make_pairs(15, 'a'));
    map3.insert(make_pairs(7, 'a'));
    // insert return value
    p = map3.insert(make_pairs(1, 'a'));
    std::cout << p.second << std::endl;
    p = map3.insert(make_pairs(1, 'a'));
    std::cout << p.second << std::endl;
    std::cout << "---" << std::endl;
    it3 = p.first;
    std::cout << it3->first << std::endl;
    std::cout << (++it3)->first << std::endl;
    std::cout << (++it3)->first << std::endl;
    std::cout << (++it3)->first << std::endl;
    std::cout << (++it3)->first << std::endl;
    std::cout << (++it3)->first << std::endl;

    // erase
    map<int, char> map5(map3);
    print(map5);
    map5.erase(8); // one child
    print(map5);
    map5.erase(5); // two child
    print(map5);
    map5.erase(15); // no child
    print(map5);
    map5.erase(10); // root
    print(map5);
    map5.erase(1); // root
    print(map5);
    map5.erase(7); // root
    print(map5);

    // // iterator ++ & --
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
    map4.insert(make_pairs(100, 'a'));
    map4 = map3;
    print(map4);

    // // reverse iterator
    map<int, char>::reverse_iterator it5 = map4.rbegin();
    while(it5 != map4.rend())
    {
        std::cout << it5->first << std::endl;
        it5++;
    }
    
    // size, empty, clear and iterator constructor
    map<int, char> map6(map3.begin(), map3.end());
    print(map6);
    std::cout << "size: " << map6.size() << std::endl;
    std::cout << map6.empty() << std::endl;
    map6.clear();
    std::cout << "size: " << map6.size() << std::endl;
    std::cout << map6.empty() << std::endl;
    print(map6);

    // max size: not the same as std, as our structure is differents from std's:
    // our node has 3 attributes: value + left + right
    // stl node (rb_tree) has 2 additional attributes: parent and color
    // std::cout << map6.max_size() << std::endl;

    // operator[]

    map<int, char> map7;
    map7[3] = 'a';
    print(map7);
    map7[2];
    print(map7);
    map7[3] = 'b';
    map7[33] = 'k';
    map7[7] = map7[3];
    print(map7);

    // insert with hint
    map7.insert(map7.begin(), make_pairs(22, 'x'));
    print(map7);
    
    // insert with range
    map<int, char> map8;
    map8[10] = 'g';
    map8[3] = 'g';
    map8.insert(map7.begin(), map7.end());
    print(map8);

    // erase return value
    std::cout << map8.erase(30) << std::endl;
    std::cout << map8.erase(3) << std::endl;
    // erase iterator
    print(map8);
    map8.erase(map8.begin());
    print(map8);
    // erase range
    map8.erase(++map8.begin(), map8.end());
    print(map8);

    // swap
    map8.insert(make_pairs(8, 'z'));
    it2 = map7.begin();
    it3 = map8.begin();
    map8.swap(map7);
    while (it2 != map8.end())
    {
        std::cout << it2->first << std::endl;
        it2++;
    }
    std::cout << "---" << std::endl;
    while (it3 != map7.end())
    {
        std::cout << it3->first << std::endl;
        it3++;
    }
    std::cout << "---" << std::endl;
    print(map8);
    print(map7);

    //find
    it2 = map8.find(7);
    std::cout << (it2 == map8.end()) << std::endl;
    std::cout << "---" << std::endl;
    while (it2 != map8.end())
    {
        std::cout << it2->first << std::endl;
        it2++;
    }
    std::cout << "---" << std::endl;
    
    it2 = map8.find(82);
    std::cout << (it2 == map8.end()) << std::endl;
    std::cout << "---" << std::endl;

    // find const
    const map<int, char> map9(map8);
    
    it4 = map9.find(22);
    while (it4 != map9.end())
    {
        std::cout << it4->first << std::endl;
        it4++;
    }
    std::cout << "---" << std::endl;

    // count
    std::cout << map9.count(22) << std::endl;
    std::cout << map9.count(322) << std::endl;

    // upper & lower bounds
    print(map8);
    it2 = map8.lower_bound(16);
    if (it2 != map8.end())
        std::cout << it2->first << std::endl;
    it2 = map8.lower_bound(22);
    if (it2 != map8.end())
        std::cout << it2->first << std::endl;
    it2 = map8.lower_bound(160);
    if (it2 != map8.end())
        std::cout << it2->first << std::endl;
    it2 = map8.upper_bound(16);
    if (it2 != map8.end())
        std::cout << it2->first << std::endl;
    it2 = map8.upper_bound(22);
    if (it2 != map8.end())
        std::cout << it2->first << std::endl;
    it2 = map8.upper_bound(160);
    if (it2 != map8.end())
        std::cout << it2->first << std::endl;
    std::cout << "---" << std::endl;

    // equal range
    typedef map<int, char>::iterator iterator;
    std::pair<iterator, iterator> q;
    q = map8.equal_range(2);
    std::cout << q.first->first << std::endl;
    std::cout << q.second->first << std::endl;
    q = map8.equal_range(-1);
    std::cout << q.first->first << std::endl;
    std::cout << q.second->first << std::endl;
    q = map8.equal_range(230);
    if (q.first != map8.end())
        std::cout << q.first->first << std::endl;
    if (q.second != map8.end())
        std::cout << q.second->first << std::endl;
    std::cout << "---" << std::endl;

    // // key_comp given as a class ("function object")

    // class with no state 
    my_less_class<char> my_less1;
    map<char,int, my_less_class<char> > mymap4;
    map<char,int, my_less_class<char> > mymap(my_less1); 
    // "my_less1" parameter is not relevant: comparison object is the same in my_map (my_less1) vs my_map4 (my_less_class<char>()), as my_less_class has no "state": the () is the same for all instances of the class;
    
    // class with state
    my_less_class_with_state<char> my_state_less(-1);
    map<char, int, my_less_class_with_state<char> > mymap5;
    map<char, int, my_less_class_with_state<char> > mymap6(my_state_less);
    // "my_state_less" param is relevant, as comparison object will not be the same in my_map5 vs my_map6

    // test that operator= does modify this->cmp
    map<char,int, my_less_class_with_state<char> >::key_compare mycomp5 = mymap5.key_comp();
    map<char,int, my_less_class_with_state<char> >::key_compare mycomp6 = mymap6.key_comp();
    std::cout << "5 " << mycomp5('a', 'b') << std::endl;
    std::cout << "6 " << mycomp6('a', 'b') << std::endl;
    mymap5 = mymap6;
    mycomp5 = mymap5.key_comp();
    std::cout << "5 " << mycomp5('a', 'b') << std::endl;

    // test insert/delete/search and iterator when cmp not less
    mymap6.insert(make_pairs('m', 3));
    mymap6.insert(make_pairs('c', 3));
    mymap6.insert(make_pairs('r', 3));
    mymap6.insert(make_pairs('o', 3));
    mymap6.insert(make_pairs('p', 3));

    map<char, int, my_less_class_with_state<char> >::iterator it = mymap6.begin();
    std::cout << it->first << std::endl;
    it++;
    std::cout << it->first << std::endl;
    it++;
    std::cout << it->first << std::endl;
    it++;
    std::cout << it->first << std::endl;
    it++;
    std::cout << it->first << std::endl;
    std::cout << "---" << std::endl;
    it = mymap6.end();
    it--;
    std::cout << it->first << std::endl;
    it--;
    std::cout << it->first << std::endl;
    it--;
    std::cout << it->first << std::endl;
    it--;
    std::cout << it->first << std::endl;
    it--;
    std::cout << it->first << std::endl;
    std::cout << "---" << std::endl;

    std::cout << mymap6.find('m')->first << std::endl;
    std::cout << mymap6.find('o')->first << std::endl;
    std::cout << mymap6.find('p')->first << std::endl;
    std::cout << mymap6.find('r')->first << std::endl;
    std::cout << mymap6.find('c')->first << std::endl;
    std::cout << "---" << std::endl;
    std::cout << mymap6.size() << std::endl;
    mymap6.erase('o');
    mymap6.erase('p');
    mymap6.erase('m');
    std::cout << mymap6.size() << std::endl;
    mymap6.clear();
    std::cout << mymap6.size() << std::endl;

    // key_comp given as a function pointer

    map<char,int, bool(*)(char, char)> mymap3(my_less);
    map<char,int, bool(*)(char, char) >::key_compare mycomp3 = mymap3.key_comp();
    std::cout << "5 " << mycomp3('a', 'b') << std::endl;

    // value comp
    map<char, int, my_less_class<char> >::value_compare val = mymap4.value_comp();
    std::cout << val(make_pairs('a', 3), make_pairs('b', 4)) << std::endl;
    std::cout << val(make_pairs('b', 3), make_pairs('c', 4)) << std::endl;
    mymap4.insert(make_pairs('m', 3));
    mymap4.insert(make_pairs('c', 3));
    std::cout << val(*mymap4.begin(), *++mymap4.begin()) << std::endl;
    std::cout << val(*++mymap4.begin(), *mymap4.begin()) << std::endl;

    // relational op

    std::cout << "---" << std::endl;
    std::cout << (map7 == map8) << std::endl;
    std::cout << (map7 != map8) << std::endl;
    std::cout << (map7 <= map8) << std::endl;
    std::cout << (map7 >= map8) << std::endl;
    std::cout << (map7 < map8) << std::endl;
    std::cout << (map7 > map8) << std::endl;

    // non member swap

    swap(map7, map8);
    print(map7);
    print(map8);

}
#endif

#ifdef STACK
{
    // default stack(no container argument)

    stack<int> st;
    st.push(4);
    st.push(43);
    st.push(443);
    st.push(49);

    std::cout << "size: " <<st.size() << std::endl;

    st.top() = 55;
    while (!st.empty())
    {
        std::cout << st.top() << std::endl;
        st.pop();
    }
    
    stack<int> st_bis;
    st.push(4);

    std::cout << (st == st_bis) << std::endl;
    std::cout << (st != st_bis) << std::endl;
    std::cout << (st > st_bis) << std::endl;
    std::cout << (st >= st_bis) << std::endl;
    std::cout << (st <= st_bis) << std::endl;
    std::cout << (st < st_bis) << std::endl;
    
    // stack containing a list

    stack<int, ft::list<int> > st1;
    st1.push(4);
    st1.push(43);
    st1.push(443);
    st1.push(49);

    std::cout << "size: " <<st1.size() << std::endl;
    st1.top() = 55;

    while (!st1.empty())
    {
        std::cout << st1.top() << std::endl;
        st1.pop();
    }
    
    stack<int, ft::list<int> > st1_bis;
    st1_bis.push(4);

    std::cout << (st1 == st1_bis) << std::endl;
    std::cout << (st1 != st1_bis) << std::endl;
    std::cout << (st1 > st1_bis) << std::endl;
    std::cout << (st1 >= st1_bis) << std::endl;
    std::cout << (st1 <= st1_bis) << std::endl;
    std::cout << (st1 < st1_bis) << std::endl;

}
#endif

#ifdef QUEUE
{
    // default queue (no container argument)

    queue<int> st;
    st.push(4);
    st.push(43);
    st.push(443);
    st.push(49);

    std::cout << "size: " <<st.size() << std::endl;

    st.front() = 55;
    st.back() = 12;
    while (!st.empty())
    {
        std::cout << st.front() << std::endl;
        st.pop();
    }
    
    queue<int> st_bis;
    st.push(4);

    std::cout << (st == st_bis) << std::endl;
    std::cout << (st != st_bis) << std::endl;
    std::cout << (st > st_bis) << std::endl;
    std::cout << (st >= st_bis) << std::endl;
    std::cout << (st <= st_bis) << std::endl;
    std::cout << (st < st_bis) << std::endl;
    
    // queue containing a list

    queue<int, ft::list<int> > st1;
    st1.push(4);
    st1.push(43);
    st1.push(443);
    st1.push(49);

    std::cout << "size: " <<st1.size() << std::endl;
    st1.front() = 55;
    st1.back() = 12;

    while (!st1.empty())
    {
        std::cout << st1.front() << std::endl;
        st1.pop();
    }
    
    queue<int, ft::list<int> > st1_bis;
    st1_bis.push(4);

    std::cout << (st1 == st1_bis) << std::endl;
    std::cout << (st1 != st1_bis) << std::endl;
    std::cout << (st1 > st1_bis) << std::endl;
    std::cout << (st1 >= st1_bis) << std::endl;
    std::cout << (st1 <= st1_bis) << std::endl;
    std::cout << (st1 < st1_bis) << std::endl;

}
#endif

}
