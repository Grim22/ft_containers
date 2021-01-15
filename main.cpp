#include "list.hpp"
#include <iostream>
#include <list>
#include <cmath> // fabs

using namespace ft;
// using namespace std;

void displaylist(list lst)
{
    list::iterator it = lst.begin();
    while (it != lst.end())
    {
        std::cout << *it << std::endl;
        it++;
    }
    std::cout << "---" << std::endl;
}
void displaylist_reverse(list lst)
{
    list::reverse_iterator it = lst.rbegin();
    while (it != lst.rend())
    {
        std::cout << *it << std::endl;
        it++;
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

int main()
{
    list lst;
    lst.push_back(9);
    lst.push_back(19);
    lst.push_back(49);
    displaylist_reverse(lst);
    list lst2(5, 7);
    std::cout << lst2.size() << std::endl;
    list lst3(lst2);
    std::cout << lst3.size() << std::endl;
    lst3 = lst;
    std::cout << lst3.size() << std::endl;

    // pop_back, pop front, assign
    list lst4(4, 8);
    lst4.push_front(5);
    std::cout << "back:" << lst4.back() << std::endl;
    displaylist(lst4);
    lst4.pop_back();
    lst4.pop_back();
    lst4.pop_back();
    lst4.pop_back();
    // lst4.pop_back();
    // lst4.pop_back();
    displaylist(lst4);
    list lst5;
    lst5.push_front(22);
    lst5.push_back(50);
    lst5.pop_front();
    lst5.pop_front();
    lst5.pop_front();
    displaylist(lst5);
    lst5.assign(4, 9);
    displaylist(lst5);
    lst5 = lst4;
    displaylist(lst5);

    // swap
    list lst6(4, 8);
    list lst7(3, 7);
    lst6.swap(lst7);
    displaylist(lst6);
    displaylist(lst7);

    // resize
    list lst8;
    lst8.push_front(2);
    lst8.push_front(22);
    lst8.push_front(222);
    lst8.push_front(2222);
    lst8.resize(8, 3);
    displaylist(lst8);
    lst8.resize(1);
    displaylist(lst8);

    // remove
    list lst9(4, 2);
    lst9.push_back(3);
    lst9.push_front(4);
    lst9.remove(4);
    lst9.remove(2);
    // lst9.remove(3);
    displaylist(lst9);

    // remove if
    list lst10;
    lst10.push_back(3);
    lst10.push_back(5);
    lst10.push_back(6);
    lst10.push_back(60);
    lst10.push_back(61);
    lst10.remove_if(single_digit);
    lst10.remove_if(is_odd());
    displaylist(lst10);

    // unique
    list lst11;
    lst11.push_back(5);
    lst11.push_back(4);
    lst11.push_back(5);
    lst11.push_back(6);
    lst11.push_back(6);
    lst11.push_back(5);
    lst11.push_back(5);
    lst11.unique();
    displaylist(lst11);

    // unique with binarypred
    list lst12;
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
    displaylist(lst12);

    // sort
    list lst13;
    lst13.push_back(5);
    lst13.push_back(8);
    lst13.push_back(3);
    lst13.push_back(8);
    lst13.push_back(1);
    displaylist(lst13);
    lst13.sort();
    displaylist(lst13);

    // sort with binary compare
    list lst14;
    lst14.push_back(18);
    lst14.push_back(48);
    lst14.push_back(42);
    lst14.push_back(1000);
    lst14.push_back(188);
    displaylist(lst14);
    lst14.sort(compare_custom);
    displaylist(lst14);

    //reverse
    list lst15;
    lst15.push_back(4);
    lst15.push_back(22);
    lst15.push_back(23);
    lst15.push_back(12);
    lst15.reverse();
    displaylist(lst15);

    // iterator
    list lst16;
    lst16.push_back(2);
    lst16.push_back(4);
    lst16.push_back(9);
    for (list::iterator it = lst16.begin(); it != lst16.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    // const iterator
    list lst17(4, 8);
    const list lst18(lst17);
    for (list::const_iterator it = lst18.begin(); it != lst18.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    // reverse iterator
    list lst19;
    lst19.push_back(4);
    lst19.push_back(3);
    lst19.push_back(1);
    lst19.push_back(9);
    for (list::reverse_iterator it = lst19.rbegin(); it != lst19.rend(); it++)
    {
        std::cout << *it << std::endl;
    }

    // iterator constructor
    list lst20;
    lst20.push_back(12);
    lst20.push_back(14);
    lst20.push_back(134);
    lst20.push_back(1354);
    list lst21a(lst20.begin(), lst20.end());
    displaylist(lst21a);
    ft::list::iterator it = lst20.begin();
    ++it;
    list lst21b(it, ++it); // 1st arg is also incremented: both args are ++it
    displaylist(lst21b);
    
    // // // iterator assign
    list lst22(2, 4);
    std::cout << "it is: " << *it << std::endl;
    lst22.assign(it, lst20.end());
    displaylist(lst22);

    // insert
    ft::list lst23;
    lst23.push_back(12);
    lst23.push_back(122);
    lst23.push_back(212);
    lst23.push_back(12222);
    ft::list::iterator it3 = lst23.begin();
    ft::list::iterator it4 = lst23.insert(++it3, 88);
    displaylist(lst23);
    std::cout << "inserted element is: " << *it4 << std::endl;
    std::cout << "---" << std::endl;

    // // insert multiple
    ft::list lst25;
    lst25.push_back(3);
    lst25.push_back(6);
    lst25.push_back(0);
    lst25.insert(lst25.begin(), 3, 8);
    displaylist(lst25);
    

    // // // // insert multiple with iterator
    ft::list lst26;
    lst26.push_back(9);
    lst26.push_back(1);
    lst26.push_back(12);
    lst26.insert(++lst26.begin(), ++lst25.begin(), lst25.end());
    displaylist(lst26);

    // erase
    ft::list lst27;
    lst27.push_back(4);
    lst27.push_back(42);
    lst27.push_back(422);
    lst27.push_back(8422);
    ft::list::iterator it6 = lst27.begin();
    it6 = lst27.erase(it6++);
    displaylist(lst27);
    std::cout << "element that followed: " <<  *it6 << std::endl;
    std::cout << "---" << std::endl;
    lst27.erase(++it6);
    displaylist(lst27);

    // erase with iterator
    ft::list lst28;
    lst28.push_back(4);
    lst28.push_back(49);
    lst28.push_back(44);
    lst28.push_back(45);
    lst28.erase(lst28.begin(), ++lst28.begin());
    displaylist(lst28);

    // // splice (whole list)
    ft::list lst29;
    lst29.push_back(4);
    lst29.push_back(42);
    lst29.push_back(44);
    ft::list lst30;
    lst30.push_back(8);
    lst30.push_back(12);
    lst29.splice(++lst29.begin(), lst30);
    displaylist(lst29);
    displaylist(lst30);
    
    // // // splice (one elem)
    lst30.push_back(5);
    lst30.push_back(512);
    lst29.splice(lst29.begin(), lst30, lst30.begin());
    displaylist(lst29);
    displaylist(lst30);
    // special case where the two lists are the same
    lst29.splice(lst29.begin(), lst29, ++lst29.begin());
    displaylist(lst29);

    // // // splice (elems between two iterators)
    ft::list lst31;
    lst31.push_back(66);
    lst31.push_back(166);
    lst31.push_back(766);
    lst31.push_back(3166);
    lst29.splice(lst29.begin(), lst31, lst31.begin(), ++lst31.begin());
    displaylist(lst29);

    // // merge
    ft::list lst32;
    lst32.push_back(2);
    lst32.push_back(4);
    lst32.push_back(9);
    ft::list lst33;
    lst33.push_back(2);
    lst33.push_back(5);
    lst33.push_back(7);
    lst33.push_back(19);
    lst33.push_back(29);
    lst32.merge(lst33);
    displaylist(lst32);
    displaylist(lst33);

    // // merge with comp
    ft::list lst34;
    lst34.push_back(33);
    lst34.push_back(27);
    lst34.push_back(2);
    lst34.sort(compare_custom);
    displaylist(lst34);
    ft::list lst35;
    lst35.push_back(4);
    lst35.push_back(110);
    lst35.push_back(11);
    lst35.push_back(222);
    lst35.sort(compare_custom);
    displaylist(lst35);
    lst34.merge(lst35, compare_custom);
    displaylist(lst34);
    displaylist(lst35);

    // relationnal operators

    ft::list lst36;
    lst36.push_back(3);
    lst36.push_back(5);
    lst36.push_back(7);
    ft::list lst37;
    lst37.push_back(3);
    lst37.push_back(5);
    lst37.push_back(7);
    ft::list lst38;
    lst38.push_back(3);
    lst38.push_back(5);
    lst38.push_back(7);
    lst38.push_back(17);
    ft::list lst39;
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

    ft::list lst40;
    std::cout << lst40.max_size() << std::endl;
    
    std::list<int> listoun;
    std::cout << listoun.max_size() << std::endl;


    // // sort REAL
    // std::list<int> lst;
    // lst.push_back(5);
    // lst.push_back(8);
    // lst.push_back(13);

    // // lst.sort(compare_custom);
    // lst.sort();
    // for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    

    // iterator constructor REAL
    // std::list<int> lst;
    // lst.push_back(3);
    // lst.push_back(4);
    // lst.push_back(5);
    // std::list<int>::iterator it3 = lst.begin();
    // it3++;
    // std::list<int> lst2(it3, ++it3);
    // for (std::list<int>::iterator it = lst2.begin(); it != lst2.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    
    // // insert REAL
    // std::list<int> lst;
    // lst.push_back(8);
    // lst.insert(++lst.begin(), 3, 1);
    // std::list<int>::iterator it = lst.begin();
    // // for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
    // // {
    // //     std::cout << *it << std::endl;
    // // }
    //     std::cout << *it++ << std::endl;
    //     std::cout << *it++ << std::endl;
    //     std::cout << *it++ << std::endl;
    //     std::cout << *it++ << std::endl;
    //     std::cout << *it++ << std::endl;
    //     std::cout << *it++ << std::endl;
    //     std::cout << *it++ << std::endl;
    //     std::cout << *it++ << std::endl;
    //     std::cout << *it++ << std::endl;


}