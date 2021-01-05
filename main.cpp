#include "list.hpp"
#include <iostream>
#include <list>
#include "Fixed.hpp"

using namespace ft;
// using namespace std;

int main()
{
    // list lst;
    // lst.push_back(9);
    // lst.push_back(19);
    // lst.push_back(49);
    // lst.displaylist_reverse();

    // list lst2(4, 7);
    // std::cout << lst2.size() << std::endl;

    // list lst3(lst2);
    // std::cout << lst3.size() << std::endl;
    // lst3 = lst;
    // std::cout << lst3.size() << std::endl;

    int tab[3] = {1, 2, 3};
    list lst(tab, tab + 3);
    lst.push_front(5);
    // lst.displaylist();
    lst.pop_back();
    lst.pop_back();
    lst.pop_back();
    lst.pop_back();
    // lst.displaylist();

    int tab2[4] = {1, 2, 3, 8};
    list lst2;
    lst2.push_front(22);
    lst2.push_back(5);
    lst2.pop_front();
    lst2.displaylist();
    lst2.assign(tab2 + 1, tab2 + 4);
    // lst2.displaylist();

    lst2 = lst;
    // lst2.displaylist();

    // Fixed a;
    // Fixed b;
    // list<int> lst3(&a, &b);

    // char c = 'c';
    // char d = 'd';
    // std::cout << lst.size() << std::endl;
}