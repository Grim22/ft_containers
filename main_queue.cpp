
#include "queue.hpp"
#include <queue>
#include <list>
#include <vector>
#include "list.hpp"
#include <iostream>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

int main()
{
    // default stack(no container argument)

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
