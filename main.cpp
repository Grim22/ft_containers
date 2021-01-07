#include "list.hpp"
#include <iostream>
#include <list>

using namespace ft;
// using namespace std;

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

    list lst4(4, 8);
    lst4.push_front(5);
    lst4.displaylist();
    lst4.pop_back();
    lst4.pop_back();
    lst4.pop_back();
    lst4.pop_back();
    lst4.pop_back();
    lst4.displaylist();

    list lst5;
    lst5.push_front(22);
    lst5.push_back(50);
    lst5.pop_front();
    lst5.pop_front();
    lst5.displaylist();
    lst5.assign(4, 9);
    lst5.displaylist();

    lst5 = lst4;
    lst5.displaylist();

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

}