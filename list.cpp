#include "list.hpp"

t_list *ft_lst_new(const int &val)
{
    t_list *elem = new t_list;
    elem->content = val;
    elem->next = NULL;
    elem->prev = NULL;
    return elem;
}

void ft::list::clear_list()
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
    this->num = 0;
    this->lst = NULL;
}


// constructors & destructors

ft::list::list(): lst(NULL), num(0)
{
}

ft::list::list(size_t n, const int val): num(0)
{
    for (size_t i = 0; i < n; i++)
    {
        this->push_back(val);
    }
}

ft::list::list(const list& x): num(0)
{
    t_list *tmp;
    tmp = x.lst;
    for (size_t i = 0; i < x.num; i++)
    {
        this->push_back(tmp->content); // num is incremented at each call
        tmp = tmp->next;
    }
}

ft::list& ft::list::operator=(const list& x)
{
    this->clear_list();
    
    t_list *tmp;
    tmp = x.lst;
    for (size_t i = 0; i < x.num; i++)
    {
        this->push_back(tmp->content); // num is incremented at each call
        tmp = tmp->next;
    }
    return *this;
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

void ft::list::pop_back()
{
    t_list *tmp(this->lst);
    t_list *old(NULL);
    while (tmp->next)
    {
        old = tmp;
        tmp = tmp->next;
    }
    delete tmp;
    if (old)
        old->next = NULL;
    this->num--;
    if (this->num == 0)
        this->lst = NULL;
}

void ft::list::push_front (const value_type& val)
{
    if (this->empty())
    {
        this->lst = ft_lst_new(val);
        this->num = 1;
        return ;
    }
    t_list *tmp(this->lst);
    this->lst = ft_lst_new(val);
    this->lst->next = tmp;
    tmp->prev = this->lst;
    this->num++;
}

void ft::list::pop_front()
{
    if (this->num == 1)
    {
        this->num--;
        delete this->lst;
        this->lst = NULL;
        return ;
    }
    t_list *tmp(this->lst->next);
    delete this->lst;
    this->lst = tmp;
    this->lst->prev = NULL;
    this->num--;
}

void ft::list::assign(size_t n, const value_type& val)
{
    // delete old list
    this->clear_list();
    // assign new list
    for (size_t i = 0; i < n; i++)
        this->push_back(val);
}

//debug

void ft::list::displaylist()
{
    t_list *tmp;
    tmp = this->lst;
    while (tmp)
    {
        std::cout << tmp->content << std::endl;
        tmp = tmp->next;
    }
    
}

void ft::list::displaylist_reverse()
{
    t_list *tmp;
    tmp = this->lst;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    while (tmp)
    {
        std::cout << tmp->content << std::endl;
        tmp = tmp->prev;
    }
}