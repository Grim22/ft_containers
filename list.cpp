#include "list.hpp"

// constructors
list::list(): lst(new t_list[0]), size(0)
{
}

list::list(size_t n, const int val)
{
    for (size_t i = 0; i < n; i++)
        this->push_back(val);
    this->size = n;
}

// element access
// Calling these functions (front & back) on an empty container causes undefined behavior (cplusplus.com)

int &list::front()
{
    return this->lst->content;
}

const int &list::front() const
{
    return this->lst->content;
}

int &list::back()
{
    t_list *tmp;
    tmp = this->lst;
    while (tmp->next)
        tmp = tmp->next;
    return tmp->content;
}

const int &list::back() const
{
    t_list *tmp;
    tmp = this->lst;
    while (tmp->next)
        tmp = tmp->next;
    return tmp->content;
}

// modifiers

void list::push_back(const int &val)
{
    if (this->empty())
    {
        this->lst = ft_lst_new(val);
        this->size = 1;
        return ;
    }
    // add elem at the end
    t_list *tmp;
    t_list *prev;
    tmp = this->lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = ft_lst_new(val);
    // set last elem->prev
    prev = tmp;
    tmp = tmp->next;
    tmp->prev = prev;
}

bool list::empty() const
{
    if (size == 0)
        return true;
    else
        return false;
}

t_list *ft_lst_new(const int &val)
{
    t_list *elem = new t_list;
    elem->content = val;
    elem->next = NULL;
    elem->prev = NULL;
    return elem;
}