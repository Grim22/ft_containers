#include "list.hpp"
#include <iostream>

// constructors & destructors
ft::list::list(): lst(NULL), num(0)
{
}

ft::list::list(size_t n, const int val)
{
    this->num = 0;
    for (size_t i = 0; i < n; i++)
    {
        this->push_back(val);
    }
}

ft::list::~list()
{
    t_list *tmp;
    t_list *del;
    tmp = this->lst;
    for (size_t i = 0; i < this->num; i++)
    {
        del = tmp;
        tmp = del->next;
        delete del;
    }
    
}

//capacity


size_t ft::list::size() const
{
    return this->num;
}

bool ft::list::empty() const
{
    if (this->num == 0)
        return true;
    else
        return false;
}


// element access
// Calling these functions (front & back) on an empty container causes undefined behavior (cplusplus.com)

int &ft::list::front()
{
    return this->lst->content;
}

const int &ft::list::front() const
{
    return this->lst->content;
}

int &ft::list::back()
{
    t_list *tmp;
    tmp = this->lst;
    while (tmp->next)
        tmp = tmp->next;
    return tmp->content;
}

const int &ft::list::back() const
{
    t_list *tmp;
    tmp = this->lst;
    while (tmp->next)
        tmp = tmp->next;
    return tmp->content;
}

// modifiers

void ft::list::push_back(const int &val)
{
    if (this->empty())
    {
        this->lst = ft_lst_new(val);
        this->num = 1;
        return ;
    }
    // add elem at the end
    t_list *tmp;
    t_list *new_elem;
    tmp = this->lst;
    new_elem = ft_lst_new(val);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_elem;
    // set last elem->prev
    new_elem->prev = tmp;
    this->num++;
}

t_list *ft_lst_new(const int &val)
{
    t_list *elem = new t_list;
    elem->content = val;
    elem->next = NULL;
    elem->prev = NULL;
    return elem;
}