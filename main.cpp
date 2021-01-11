#include "list.hpp"
#include <iostream>
#include <list>
#include <cmath> // fabs

using namespace ft;
// using namespace std;


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
    return (first % 10 > second % 10);
}

int main()
{
    // list lst;
    // lst.push_back(9);
    // lst.push_back(19);
    // lst.push_back(49);
    // lst.displaylist_reverse();

    // list lst2(5, 7);
    // std::cout << lst2.size() << std::endl;

    // list lst3(lst2);
    // std::cout << lst3.size() << std::endl;
    // lst3 = lst;
    // std::cout << lst3.size() << std::endl;

    // list lst4(4, 8);
    // lst4.push_front(5);
    // std::cout << "back:" << lst4.back() << std::endl;
    // lst4.displaylist();
    // lst4.pop_back();
    // lst4.pop_back();
    // lst4.pop_back();
    // lst4.pop_back();
    // lst4.pop_back();
    // lst4.displaylist();

    // list lst5;
    // lst5.push_front(22);
    // lst5.push_back(50);
    // lst5.pop_front();
    // lst5.pop_front();
    // lst5.displaylist();
    // lst5.assign(4, 9);
    // lst5.displaylist();

    // lst5 = lst4;
    // lst5.displaylist();

    // list lst6(4, 8);
    // list lst7(3, 7);
    // lst6.swap(lst7);
    // lst6.displaylist();
    // lst7.displaylist();

    // list lst8;
    // lst8.push_front(2);
    // lst8.push_front(22);
    // lst8.push_front(222);
    // lst8.push_front(2222);
    // lst8.resize(8, 3);
    // lst8.displaylist();
    // lst8.resize(1);
    // lst8.displaylist();

    // remove
    // list lst9(4, 2);
    // lst9.push_back(3);
    // lst9.push_front(4);
    // lst9.remove(4);
    // lst9.remove(2);
    // lst9.remove(3);
    // lst9.displaylist();

    // remove if
    // list lst10;
    // lst10.push_back(3);
    // lst10.push_back(5);
    // lst10.push_back(6);
    // lst10.push_back(60);
    // lst10.push_back(61);
    // lst10.remove_if(single_digit);
    // lst10.remove_if(is_odd());
    // lst10.displaylist();

    // unique
    // list lst11;
    // lst11.push_back(5);
    // lst11.push_back(4);
    // lst11.push_back(5);
    // lst11.push_back(6);
    // lst11.push_back(6);
    // lst11.push_back(5);
    // lst11.push_back(5);
    // lst11.unique();
    // lst11.displaylist();

    // // unique with binarypred
    // list lst12;
    // lst12.push_back(5);
    // lst12.push_back(8);
    // lst12.push_back(10);
    // lst12.push_back(12);
    // lst12.push_back(5);
    // lst12.push_back(5);
    // lst12.push_back(50);
    // lst12.push_back(7);
    // lst12.push_back(9);
    // lst12.unique(same_parity);
    // lst12.displaylist();

    // sort
    // list lst13;
    // lst13.push_back(5);
    // lst13.push_back(8);
    // lst13.push_back(3);
    // lst13.push_back(1);
    // lst13.displaylist();
    // lst13.sort();
    // lst13.displaylist();
    // // std::cout << lst13.size() << std::endl;

    // // sort with binary compare
    // list lst14;
    // lst14.push_back(18);
    // lst14.push_back(48);
    // lst14.push_back(42);
    // lst14.push_back(1000);
    // lst14.push_back(188);
    // lst14.displaylist();
    // lst14.sort(compare_custom);
    // lst14.displaylist();

    //reverse
    // list lst15;
    // lst15.push_back(4);
    // // lst15.push_back(22);
    // // lst15.push_back(23);
    // lst15.push_back(12);
    // lst15.reverse();
    // lst15.displaylist();

    // iterator
    // list lst16;
    // lst16.push_back(2);
    // lst16.push_back(4);
    // lst16.push_back(9);
    // for (list::iterator it = lst16.begin(); it != lst16.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }

    // // const iterator
    // list lst17(4, 8);
    // const list lst18(lst17);
    // for (list::const_iterator it = lst18.begin(); it != lst18.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }

    // reverse iterator NOT READY
    // list lst19;
    // lst19.push_back(4);
    // lst19.push_back(3);
    // lst19.push_back(1);
    // lst19.push_back(9);
    // for (list::reverse_iterator it = lst19.rbegin(); it != lst19.rend(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }

    // // iterator constructor
    // list lst20;
    // lst20.push_back(12);
    // lst20.push_back(14);
    // lst20.push_back(134);
    // lst20.push_back(1354);
    // lst20.displaylist();
    
    // // iterator constructor: lst(it, it++) case
    // // ft::list::iterator it2(it);
    // // it2++;
    // // list lst21(it, it2); // works fine
    // // lst21.displaylist();
    // // ERROR CASES
    // ft::list::iterator it = lst20.begin();
    // ++it;
    // // std::cout << "it: " << *it << std::endl;
    // list lst21b(it, ++it); // 1st arg is also incremented: both args are ++it
    // // list lst21b(it, it++); // 1st arg is incremented but second arg is not
    // lst21b.displaylist();
    
    // // iterator assign
    // list lst22(2, 4);
    // lst22.assign(it, lst20.end());
    // lst22.displaylist();

    // insert
    ft::list lst23;
    lst23.push_back(12);
    lst23.push_back(122);
    lst23.push_back(212);
    lst23.push_back(12222);
    ft::list::iterator it3 = lst23.begin();
    it3++;
    ft::list::iterator it4 = lst23.insert(it3, 88);
    lst23.displaylist();
    std::cout << *it4 << std::endl;
    std::cout << "---" << std::endl;

    // // insert multiple
    ft::list lst25;
    lst25.push_back(3);
    lst25.push_back(6);
    lst25.push_back(0);
    lst25.insert(lst25.begin(), 3, 8);
    lst25.displaylist();
    // does not work to insert at the end of the list, whereas it works with STL list

    // // insert multiple with iterator
    ft::list lst26;
    lst26.push_back(9);
    lst26.push_back(1);
    lst26.push_back(12);
    lst26.insert(++lst26.begin(), ++lst25.begin(), lst25.end());
    lst26.displaylist();

    // sort REAL
//     std::list<int> lst;
//     lst.push_back(5);
//     lst.push_back(8);
//     lst.push_back(3);

//     std::list<int>::iterator it;

//     it = lst.begin();
//     std::cout << *it << std::endl;
//     // std::cout << it << std::endl;
    
//     lst.sort();
    
//     std::cout << *it << std::endl;
    
//     it = lst.begin();
//     std::cout << *it << std::endl;

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