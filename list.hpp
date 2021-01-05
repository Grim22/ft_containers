#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <iostream>

// list of int (1st param of template = int, and second param is set to default)

typedef struct s_list
{
    int content; // stl containers internally store copies
    struct s_list *prev;
    struct s_list *next;
} t_list;


t_list *ft_lst_new(const int &val);

namespace ft
{
class list
{
private:
    t_list *lst;
    size_t num;
    void clear_list();

    /* data */
public:

    // member types
    typedef int value_type; // 1st param of template

    // constructors & destructor
    explicit list ();
    explicit list (size_t n, const int val = int());
    template <class InputIterator>
    list (InputIterator first, InputIterator last);
    list (const list& x);
    ~list();
    list& operator= (const list& x);

    //capacity
    bool empty() const;
    size_t size() const;

    // element access
    int &front();
    const int &front() const;
    int &back();
    const int &back() const;

    // modifiers
    void push_back(const int& val);
    void pop_back(); 
    void push_front (const value_type& val);
    void pop_front(); 

    void assign (size_t n, const value_type& val);
    template <class InputIterator>
    void assign (InputIterator first, InputIterator last);

    // debug
    void displaylist();
    void displaylist_reverse();

};
}

template <class InputIterator>
ft::list::list (InputIterator first, InputIterator last)
{
    for (InputIterator tmp = first; tmp != last; tmp++)
    {
        this->push_back(*tmp);
    }
    
}

template <class InputIterator>
void ft::list::assign (InputIterator first, InputIterator last)
{
    this->clear_list();
    for (InputIterator tmp = first; tmp != last; tmp++)
    {
        this->push_back(*tmp);
    }

}

#endif