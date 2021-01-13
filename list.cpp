#include "list.hpp"


t_list *ft_lst_new(const int &val)
{
    t_list *elem = new t_list;
    elem->content = val;
    elem->next = NULL;
    elem->prev = NULL;
    return elem;
}

void ft::list::unlink_node(t_list *node)
{
    if (node == NULL)
        return;

    if (node->prev)
        node->prev->next = node->next;
    else // if we are deleting the first element of the list, we need to update this->lst
        this->lst = node->next;

    if (node->next)
        node->next->prev = node->prev;
    
    this->num--;
}

void ft::list::delete_node(t_list *node)
{
    this->unlink_node(node);
    if (node != NULL)
        delete node;
}

// node a and b are contiguousm a is before b
// void ft::list::swap_cont_nodes(t_list *a, t_list *b)
// {
//     t_list *tmp;

//     // std::cout << "swap " << a->content << " " << b->content << std::endl << std::endl;
//     if (a->prev)
//         a->prev->next = b;
//     else
//         this->lst = b; // if a was the first element, we need to update this->lst 
    
//     if (b->next)
//         b->next->prev = a;
    
//     tmp = a->prev;
//     // std::cout << "tmp->prev " << tmp << std::endl;
//     a->prev = b;
//     a->next = b->next;
    
//     b->next = a;
//     b->prev = tmp;
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

void ft::list::insert_before(t_list *node, t_list *inserted_node)
{
    // update node before and node in list where inserted
    // set next and prev of new_node
    if (node->prev)
        node->prev->next = inserted_node;
    else
        this->lst = inserted_node;
    inserted_node->prev = node->prev;
    node->prev = inserted_node;
    inserted_node->next = node;
    this->num++;
}

void ft::list::insert_end(t_list *new_last)
{
    t_list *old_last = this->get_last_node();
    if (old_last == NULL) // empty list
    {
        new_last->next = NULL;
        this->lst = new_last;
        this->num++;
        return ;
    }
    old_last->next = new_last;
    new_last->prev = old_last;
    new_last->next = NULL;
    this->num++;
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

t_list *ft::list::iterator::as_node()
{
    return this->ptr;
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

const t_list *ft::list::const_iterator::as_node()
{
    return this->ptr;
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
    this->insert_before(position.as_node(), ft_lst_new(val));
    return --position;
}

void ft::list::insert(iterator position, size_type n, const value_type& val)
{
    if (position == NULL) // protection
        return ;
    for (size_type i = 0; i < n; ++i)
        this->insert_before(position.as_node(), ft_lst_new(val));
}

void ft::list::insert(iterator position, iterator first, iterator last)
{
    if (position == NULL) // protection
        return ;
    for (iterator it = first; it != last ; ++it)
        this->insert_before(position.as_node(), ft_lst_new(*it));
}

ft::list::iterator ft::list::erase (ft::list::iterator position)
{
    if (position == NULL)
        return NULL;
    ft::list::iterator next(position);
    next++;
    this->delete_node(position.as_node());
    return next;
}

ft::list::iterator ft::list::erase (iterator first, iterator last)
{
    while (first != last)
    {
        first = this->erase(first);
    }
    return last;
}


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
        if (tmp->content > tmp->next->content)
        {
            // this->swap_cont_nodes(tmp, tmp->next);
            this->splice(iterator(tmp), *this, iterator(tmp->next));
            tmp = this->lst;
        }
        else
            tmp = tmp->next;
    }
}

// sort in iterator fashion
// void ft::list::sort()
// {
//     iterator it = this->begin();
//     iterator it_next = ++this->begin();
//     while (it_next != this->end())
//     {
//         if (*it > *it_next)
//         {
//             this->splice(it, *this, it_next);
//             it = this->begin();
//             it_next = ++this->begin();
//         }
//         else
//         {
//             it++;
//             it_next++;
//         }
//     }
// }


void ft::list::splice (iterator position, list& x)
{
    if (position == NULL) // protection
        return ;
    iterator it = x.begin();
    iterator tmp(it);
    while (it != x.end())
    {
        // std::cout << *it << std::endl;
        // std::cout << "---" << std::endl;
        // x.displaylist();
        // this->displaylist();
        tmp++;
        x.unlink_node(it.as_node());
        this->insert_before(position.as_node(), it.as_node());
        it = tmp;
    }
}

void ft::list::splice (iterator position, list& x, iterator i)
{
    if (position == NULL)
        return;
    
    // x may be *this if position points to an element not actually being spliced (i != position)
    // if position == i++ (position == j): no splice to be done
    iterator j = i;
    j++;
    if (position == i || position == j)
        return ;

    x.unlink_node(i.as_node());
    this->insert_before(position.as_node(), i.as_node());
}

void ft::list::splice (iterator position, list& x, iterator first, iterator last)
{
    if (position == NULL) // protection
        return ;

    // undefined if position in [first, last]
    iterator j = first;
    while (j != last)
    {
        if (position == j)
            return ;
        j++;
    }

    iterator it = first;
    iterator tmp(it);
    while (it != last)
    {
        // std::cout << *it << std::endl;
        // std::cout << "---" << std::endl;
        // x.displaylist();
        // this->displaylist();
        tmp++;
        x.unlink_node(it.as_node());
        this->insert_before(position.as_node(), it.as_node());
        it = tmp;
    }

}

void ft::list::reverse()
{
    if (this->lst == NULL)
        return ;
    t_list *tmp(this->get_last_node());
    this->lst = tmp;
    while (tmp)
    {
        // std::cout << tmp->content << std::endl;
        t_list *swap(tmp->next);
        tmp->next = tmp->prev;
        tmp->prev = swap;
        tmp = tmp->next;
    }
}

void ft::list::merge (list& x)
{
    if (this == &x)
        return ;
    iterator this_it = this->begin();
    iterator x_it = x.begin();
    iterator tmp(x_it);
    while (x_it != x.end())
    {
        tmp++;
        while (this_it != this->end())
        {
            if (*x_it < *this_it)
            {
                this->splice(this_it, x, x_it);
                break;
            }
            else
                this_it++;
        }
        if (this_it == this->end()) // if we have to insert at the end (can't use splice in that case -> has to be done manually...)
        {
            x.unlink_node(x_it.as_node()); // unlink node that we are going to transfer
            this->insert_end(x_it.as_node());
        }
        x_it = tmp;
    }
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