#include "list.hpp"

void t_list::reverse()
{
    t_list *tmp;
    tmp = this->next;
    this->next = this->prev;
    this->prev = tmp;
}

t_list *ft_lst_new(const int &val) // by default, points on itself
{
    t_list *elem = new t_list;
    elem->content = val;
    elem->next = elem;
    elem->prev = elem;
    return elem;
}

void ft::list::unlink_node(t_list *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void ft::list::delete_node(t_list *node)
{
    if (node == this->lst) // we dont want to delete the past the end node
        return;
    this->unlink_node(node);
    delete node;
}

void ft::list::insert_before(t_list *node, t_list *inserted_node)
{
    // update node before and node in list where inserted
    // set next and prev of new_node
    node->prev->next = inserted_node;
    inserted_node->prev = node->prev;
    node->prev = inserted_node;
    inserted_node->next = node;
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

ft::list::list(): lst(ft_lst_new(int()))
{
}

ft::list::list(size_type n, const int val): lst(ft_lst_new(int()))
{
    for (size_type i = 0; i < n; i++)
        this->push_back(val);
}

ft::list::list(const list& x): lst(ft_lst_new(int()))
{
    const_iterator it = x.begin();
    const_iterator ite = x.end();
    while (it != ite)
        this->push_back(*it++);
}
    
ft::list::list(ft::list::iterator first, ft::list::iterator last): lst(ft_lst_new(int()))
{
    for (ft::list::iterator it = first; it != last; it++)
        this->push_back(*it);
}

ft::list& ft::list::operator=(const list& x)
{
    this->clear();
    
    const_iterator it = x.begin();
    const_iterator ite = x.end();
    while (it != ite)
    {
        this->push_back(*it);
        it++;
    }
    return *this;
}

ft::list::~list()
{
    this->clear();
    delete this->lst;
}

// iterator functions

ft::list::iterator ft::list::begin()
{
    return iterator(this->lst->next);
}

ft::list::iterator ft::list::end()
{
    return iterator(this->lst);
}

ft::list::const_iterator ft::list::begin() const
{
    return const_iterator(this->lst->next);
}

ft::list::const_iterator ft::list::end() const
{
    return const_iterator(this->lst);
}

ft::list::reverse_iterator ft::list::rbegin()
{
    return reverse_iterator(this->end());
}

ft::list::reverse_iterator ft::list::rend()
{
    return reverse_iterator(this->begin());
}

ft::list::const_reverse_iterator ft::list::rbegin() const
{
    return const_reverse_iterator(this->end());
}

ft::list::const_reverse_iterator ft::list::rend() const
{
    return const_reverse_iterator(this->begin());
}


//capacity

ft::list::size_type ft::list::size() const
{
    size_type ret(0);
    const_iterator it = this->begin();
    const_iterator ite = this->end();
    while (it != ite)
    {
        ret++;
        it++;
    }
    return ret;
}

ft::list::size_type ft::list::max_size() const
{
    std::allocator<t_list> al;
    return al.max_size();
}

bool ft::list::empty() const
{
    if (this->size() == 0)
        return true;
    else
        return false;
}


// element access
// Calling these functions (front & back) on an empty container causes undefined behavior (cplusplus.com)

int &ft::list::front()
{
    return this->lst->next->content;
}

const int &ft::list::front() const
{
    return this->lst->next->content;
}

int &ft::list::back()
{
    return this->lst->prev->content;
}

const int &ft::list::back() const
{
    return this->lst->prev->content;
}


// modifiers

void ft::list::push_back(const int &val)
{
    this->insert(this->end(), val);
}

void ft::list::pop_back()
{
    this->delete_node(this->lst->prev);
}

void ft::list::push_front (const value_type& val)
{
    this->insert(this->begin(), val);
}

void ft::list::pop_front()
{
    this->delete_node(this->lst->next);
}

void ft::list::clear()
{
    iterator it = this->begin();
    iterator ite = this->end();
    iterator tmp;
    while (it != ite)
    {
        tmp = it;
        tmp++;
        delete it.as_node(); // we dont need to use delete_node, as we are deleting the whole list (no need to use unlink)
        it = tmp;
    }
    // reset past-the-end node
    this->lst->next = this->lst;
    this->lst->prev = this->lst;
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
    if (n > this->size())
    {
        while (this->size() != n)
            this->push_back(val);
    }
    else
    {
        while (this->size() != n)
            this->pop_back();
    }
}

ft::list::iterator ft::list::insert(iterator position, const value_type& val)
{
    this->insert_before(position.as_node(), ft_lst_new(val));
    return --position;
}

void ft::list::insert(iterator position, size_type n, const value_type& val)
{
    for (size_type i = 0; i < n; ++i)
        this->insert_before(position.as_node(), ft_lst_new(val));
}

void ft::list::insert(iterator position, iterator first, iterator last)
{
    for (iterator it = first; it != last ; ++it)
        this->insert_before(position.as_node(), ft_lst_new(*it));
}

ft::list::iterator ft::list::erase (ft::list::iterator position)
{
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
    iterator it = this->begin();
    iterator ite = this->end();

    while (it != this->end())
    {
        if (*it == val)
            it = this->erase(it);
        else
            it++;
    }
}

void ft::list::unique()
{
    // smart implementation from stl source
    iterator it = this->begin();
    iterator it_next = it;
    iterator ite = this->end();
    while (++it_next != ite)
    {
        if (*it == *it_next)
            this->erase(it_next);
        else
            it = it_next;
        it_next = it; // if it_next erased, it_next and it are back to it
        // else it_next and it move on
    }
    
}

void ft::list::sort()
{
    iterator it = this->begin();
    iterator it_next = it;
    iterator ite = this->end();
    while (++it_next != this->end())
    {
        if (*it > *it_next)
        {
            this->splice(it, *this, it_next);
            it = this->begin();
            it_next = it;
        }
        else
            it = it_next;
    }
}

void ft::list::splice (iterator position, list& x)
{
    iterator it = x.begin();
    iterator tmp(it);
    while (it != x.end())
    {
        tmp++;
        x.unlink_node(it.as_node());
        this->insert_before(position.as_node(), it.as_node());
        it = tmp;
    }
}

void ft::list::splice (iterator position, list& x, iterator i)
{
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
        tmp++;
        x.unlink_node(it.as_node());
        this->insert_before(position.as_node(), it.as_node());
        it = tmp;
    }
}

void ft::list::reverse()
{
    // start from end of the list, and "reverse" every node
    // then reverse past_the_end node
    t_list *tmp(this->lst->prev);
    while (tmp != this->lst)
    {
        tmp->reverse();
        tmp = tmp->next;
    }
    tmp->reverse();
}

void ft::list::merge (list& x)
{
    if (this == &x)
        return ;
    iterator this_it = this->begin();
    iterator x_it = x.begin();
    iterator tmp(x_it);
    // for each element in x, go through this to find where to insert it
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
        if (this_it == this->end()) // if couldnt insert it before, insert it at the end
            this->splice(this_it, x, x_it);
        x_it = tmp;
    }
}

// non members

bool ft::operator==(const list& lhs, const list& rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    ft::list::const_iterator it_l = lhs.begin();
    ft::list::const_iterator it_r = rhs.begin();
    while (it_l != lhs.end())
    {
        if (*it_l++ != *it_r++)
            return false;
    }
    return true;
}
bool ft::operator<(const list& lhs, const list& rhs)
{
    ft::list::const_iterator it_l = lhs.begin();
    ft::list::const_iterator it_r = rhs.begin();
    while (it_l != lhs.end() && it_r != rhs.end())
    {
        if (*it_l == *it_r)
        {
            it_l++;
            it_r++;
        }
        else
            return (*it_l < *it_r);
    }
    // so far all elements compare equal
    // 3 cases:
    // 1. it_l == end && it_r == end -> equal ==> return FALSE
    // 2. it_l == end only ==> l is shorther ==> return TRUE
    // 3. it_r == end only ==> r is shorter ==> return FALSE
    if (it_r != rhs.end())
        return true;
    return false;
}
bool ft::operator<=(const list& lhs, const list& rhs)
{
    return (lhs == rhs || lhs < rhs );
}
bool ft::operator!=(const list& lhs, const list& rhs)
{
    return (!(lhs == rhs));
}
bool ft::operator>=(const list& lhs, const list& rhs)
{
    if ( lhs < rhs)
        return false;
    return true;
}
bool ft::operator>(const list& lhs, const list& rhs)
{
    if ( lhs <= rhs)
        return false;
    return true;
}

//debug

