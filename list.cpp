#include "list.hpp"

t_list *ft_lst_new(const int &val)
{
    t_list *elem = new t_list;
    elem->content = val;
    elem->next = NULL;
    elem->prev = NULL;
    return elem;
}

void ft::list::delete_node(t_list *node)
{
    if (node == NULL)
        return;

    if (node->prev)
        node->prev->next = node->next;
    else // if we are deleting the first element of the list, we need to update this->lst
        this->lst = node->next;

    if (node->next)
        node->next->prev = node->prev;
    
    delete node;
    if (this->num == 1) // if there will be no more element left on the list, set this->lst to NULL
        this->lst = NULL;
    this->num--;
}

// node a and b are contiguousm a is before b
void ft::list::swap_cont_nodes(t_list *a, t_list *b)
{
    t_list *tmp;

    // std::cout << "swap " << a->content << " " << b->content << std::endl << std::endl;
    if (a->prev)
        a->prev->next = b;
    else
        this->lst = b; // if a was the first element, we need to update this->lst 
    
    if (b->next)
        b->next->prev = a;
    
    tmp = a->prev;
    // std::cout << "tmp->prev " << tmp << std::endl;
    a->prev = b;
    a->next = b->next;
    
    b->next = a;
    b->prev = tmp;
    // std::cout << "tmp->prev " << tmp << std::endl;

}

// NOT WORKING: swap for reverse
// version for two nodes that are not contiguous
// void ft::list::swap_nodes(t_list *a, t_list *b)
// {
//     t_list *old_a(a);
//     t_list *old_b(b);

//     // std::cout << "swap " << a->content << " " << b->content << std::endl << std::endl;
//     if (a->prev)
//         a->prev->next = b;
//     else
//         this->lst = b;
//     if (a ->next)
//         a->next->prev = b; 

//     if (b->next)
//         b->next->prev = a;
//     if (b->prev)
//         b->prev->next = a;
//     else
//         this->lst = a;
    
//     // std::cout << "tmp->prev " << tmp << std::endl;
//     a->prev = old_b->prev;
//     a->next = old_b->next;
    
//     b->next = old_a->next;
//     b->prev = old_a->prev;
//     // std::cout << "tmp->prev " << tmp << std::endl;

// }

t_list *ft::list::get_last_node()
{
    t_list *tmp(this->lst);
    if (tmp == NULL)
        return NULL;
    while (tmp->next)
        tmp = tmp->next;
    return tmp;
}

t_list *ft::list::get_last_node() const
{
    t_list *tmp(this->lst);
    if (tmp == NULL)
        return NULL;
    while (tmp->next)
        tmp = tmp->next;
    return tmp;
}

void ft::list::insert_before(t_list *node, t_list *new_node)
{
    if (node->prev)
        node->prev->next = new_node;
    else
        this->lst = new_node;
    new_node->prev = node->prev;
    node->prev = new_node;
    new_node->next = node;
    this->num++;
}

t_list *ft::list::get_node(iterator position)
{
    t_list *tmp(this->lst);
    iterator it(this->begin());
    while (it != position)
    {
        it++;
        tmp = tmp->next;
    }
    return tmp;
}

// class iterator


ft::list::iterator::iterator()
{
}
ft::list::iterator::iterator(const iterator &copy): ptr(copy.ptr)
{
}
ft::list::iterator::iterator(t_list *ptr): ptr(ptr)
{
}
ft::list::iterator::~iterator()
{
}
ft::list::iterator &ft::list::iterator::operator=(const iterator &rhs)
{
    this->ptr = rhs.ptr;
    return *this;
}
int &ft::list::iterator::operator*() const
{
    return this->ptr->content;
}
int *ft::list::iterator::operator->() const
{
    return &this->ptr->content;
}
ft::list::iterator& ft::list::iterator::operator++() // preincrement (++a)
{
    this->ptr = this->ptr->next;
    return *this;
}
ft::list::iterator ft::list::iterator::operator++(int) // postincrement (a++)
{
    iterator tmp(*this);
    this->ptr = this->ptr->next;
    return tmp;
}
ft::list::iterator& ft::list::iterator::operator--()
{
    this->ptr = this->ptr->prev;
    return *this;    
}
ft::list::iterator ft::list::iterator::operator--(int)
{
    iterator tmp(*this);
    this->ptr = this->ptr->prev;
    return tmp;
}
bool ft::list::iterator::operator==(const iterator &rhs) const
{
    return (this->ptr == rhs.ptr);
}
bool ft::list::iterator::operator!=(const iterator &rhs) const
{
    return (this->ptr != rhs.ptr);
}


// class const iterator

ft::list::const_iterator::const_iterator()
{
}
ft::list::const_iterator::const_iterator(const const_iterator &copy): ptr(copy.ptr)
{
}
ft::list::const_iterator::const_iterator(t_list *ptr): ptr(ptr)
{
}
ft::list::const_iterator::~const_iterator()
{
}
ft::list::const_iterator &ft::list::const_iterator::operator=(const const_iterator &rhs)
{
    this->ptr = rhs.ptr;
    return *this;
}
const int &ft::list::const_iterator::operator*() const
{
    return this->ptr->content;
}
const int *ft::list::const_iterator::operator->() const
{
    return &this->ptr->content;
}
ft::list::const_iterator& ft::list::const_iterator::operator++() // preincrement (++a)
{
    this->ptr = this->ptr->next;
    return *this;
}
ft::list::const_iterator ft::list::const_iterator::operator++(int) // postincrement (a++)
{
    const_iterator tmp(*this);
    this->ptr = this->ptr->next;
    return tmp;
}
ft::list::const_iterator& ft::list::const_iterator::operator--()
{
    this->ptr = this->ptr->prev;
    return *this;    
}
ft::list::const_iterator ft::list::const_iterator::operator--(int)
{
    const_iterator tmp(*this);
    this->ptr = this->ptr->prev;
    return tmp;
}
bool ft::list::const_iterator::operator==(const const_iterator &rhs) const
{
    return (this->ptr == rhs.ptr);
}
bool ft::list::const_iterator::operator!=(const const_iterator &rhs) const
{
    return (this->ptr != rhs.ptr);
}




// constructors & destructors

ft::list::list(): lst(NULL), num(0)
{
}

ft::list::list(size_type n, const int val): num(0)
{
    for (size_type i = 0; i < n; i++)
    {
        this->push_back(val);
    }
}

ft::list::list(const list& x): num(0)
{
    t_list *tmp;
    tmp = x.lst;
    for (size_type i = 0; i < x.num; i++)
    {
        this->push_back(tmp->content); // num is incremented at each call
        tmp = tmp->next;
    }
}
    
ft::list::list(ft::list::iterator first, ft::list::iterator last): lst(NULL), num(0)
{
    // std::cout << "first " << *first << std::endl;
    // std::cout << "last " << *last << std::endl;
    for (ft::list::iterator it = first; it != last; it++)
        this->push_back(*it);
}

ft::list& ft::list::operator=(const list& x)
{
    this->clear();
    
    t_list *tmp;
    tmp = x.lst;
    for (size_type i = 0; i < x.num; i++)
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
    for (size_type i = 0; i < this->num; i++)
    {
        del = tmp;
        tmp = del->next;
        delete del;
    }
}

// iterator functions

ft::list::iterator ft::list::begin()
{
    return iterator(this->lst);
}

ft::list::iterator ft::list::end()
{
    return iterator(NULL);
}

ft::list::const_iterator ft::list::begin() const
{
    return const_iterator(this->lst);
}

ft::list::const_iterator ft::list::end() const
{
    return const_iterator(NULL);
}

// ft::list::reverse_iterator ft::list::rbegin()
// {
//     return reverse_iterator(this->get_last_node());
// }

// ft::list::reverse_iterator ft::list::rend()
// {
//     return reverse_iterator(NULL);
// }

// ft::list::const_reverse_iterator ft::list::rbegin() const
// {
//     return const_reverse_iterator(this->get_last_node());
// }

// ft::list::const_reverse_iterator ft::list::rend() const
// {
//     return const_reverse_iterator(NULL);
// }


//capacity

ft::list::size_type ft::list::size() const
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
    return this->get_last_node()->content;
}

const int &ft::list::back() const
{
    return this->get_last_node()->content;
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
    t_list *last(this->get_last_node());
    t_list *new_elem(ft_lst_new(val));
    last->next = new_elem;
    // set last elem->prev
    new_elem->prev = last;
    this->num++;
}

void ft::list::pop_back()
{
    // t_list *tmp(this->lst);
    // t_list *old(NULL);
    // while (tmp->next)
    // {
    //     old = tmp;
    //     tmp = tmp->next;
    // }
    // delete tmp;
    // if (old)
    //     old->next = NULL;
    // this->num--;
    // if (this->num == 0)
    //     this->lst = NULL;
    // t_list *tmp(this->lst);
    // while (tmp->next)
    //     tmp = tmp->next;
    this->delete_node(this->get_last_node());
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
    // if (this->num == 1)
    // {
    //     this->num--;
    //     delete this->lst;
    //     this->lst = NULL;
    //     return ;
    // }
    // t_list *tmp(this->lst->next);
    // delete this->lst;
    // this->lst = tmp;
    // this->lst->prev = NULL;
    // this->num--;
    this->delete_node(this->lst);
}

void ft::list::clear()
{
    t_list *tmp;
    t_list *del;
    tmp = this->lst;
    for (size_type i = 0; i < this->num; i++)
    {
        del = tmp;
        tmp = del->next;
        delete del;
    }
    this->num = 0;
    this->lst = NULL;
}


void ft::list::assign(size_type n, const value_type& val)
{
    // delete old list
    this->clear();
    // assign new list
    for (size_type i = 0; i < n; i++)
        this->push_back(val);
}

void ft::list::assign (iterator first, iterator last)
{
    // delete old list
    this->clear();
    // assign new list
    for (iterator it = first; it != last; it++)
        this->push_back(*it);
}

void ft::list::swap (list& x)
{
    list tmp;
    tmp = *this;
    *this = x;
    x = tmp;
}
    
void ft::list::resize (size_type n, value_type val)
{
    if (n > this->num)
    {
        while (this->num != n)
            this->push_back(val);
    }
    else
    {
        while (this->num != n)
            this->pop_back();
    }
}

ft::list::iterator ft::list::insert(iterator position, const value_type& val)
{
    if (position == NULL) // protection
        return NULL;
    this->insert_before(this->get_node(position), ft_lst_new(val));
    return --position;
}

void ft::list::insert(iterator position, size_type n, const value_type& val)
{
    if (position == NULL) // protection
        return ;
    for (size_type i = 0; i < n; ++i)
        this->insert_before(this->get_node(position), ft_lst_new(val));
}

void ft::list::insert(iterator position, iterator first, iterator last)
{
    if (position == NULL) // protection
        return ;
    t_list *node_position = this->get_node(position);
    for (iterator it = first; it != last ; ++it)
        this->insert_before(node_position, ft_lst_new(*it));
}

// ft::list::iterator ft::list::erase (iterator position)
// {

// }

// ft::list::iterator ft::list::erase (iterator first, iterator last)
// {

// }


// operations

void ft::list::remove(const value_type& val)
{
    t_list *tmp(this->lst);
    t_list *old(NULL);
    while (tmp)
    {
        old = tmp;
        tmp = tmp->next;
        if (old->content == val)
            this->delete_node(old);
    }
}

void ft::list::unique()
{
    t_list *tmp(this->lst);
    while (tmp->next)
    {
        if (tmp->content == tmp->next->content)
        {
            this->delete_node(tmp->next);
            tmp = this->lst;
        }
        else
            tmp = tmp->next;
    }
}

void ft::list::sort()
{
    t_list *tmp(this->lst);
    while (tmp->next)
    {
        // this->displaylist();
        // std::cout << "1st elem " << this->lst->prev << std::endl;
        if (tmp->content > tmp->next->content)
        {
            this->swap_cont_nodes(tmp, tmp->next);
            tmp = this->lst;
        }
        else
            tmp = tmp->next;
    }
}

// void ft::list::reverse()
// {
//     t_list *first(this->lst);
//     t_list *last(this->get_last_node());
//     for (size_type i = 0; i < this->num / 2; i++)
//     {
//         std::cout << "a" << std::endl;
//         this->swap_nodes(first, last);
//         first = first->next;
//         last = last->prev;
//     }
// }

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
    std::cout << "---" << std::endl;
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
    std::cout << "---" << std::endl;
}