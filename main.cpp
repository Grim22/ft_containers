#include "list.hpp"
#include <iostream>
#include <list>

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

    list lst9(4, 2);
    lst9.push_back(3);
    lst9.push_front(4);
    lst9.remove(4);
    lst9.remove(2);
    lst9.remove(3);
    lst9.displaylist();

    list lst10;
    lst10.push_back(3);
    lst10.push_back(5);
    lst10.push_back(6);
    lst10.push_back(60);
    lst10.push_back(61);
    lst10.remove_if(single_digit);
    lst10.remove_if(is_odd());
    lst10.displaylist();

}