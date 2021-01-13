#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
// #include <iterator>

// list of int (1st param of template = int, and second param is set to default)

typedef struct s_list
{
    int content; // stl containers internally store copies
    struct s_list *prev;
    struct s_list *next;

    // void unlink();
} t_list;


t_list *ft_lst_new(const int &val);

namespace ft
{
class list
{
    // member types
    typedef int value_type; // 1st param of template
    typedef unsigned long size_type;
private:
    t_list *lst;
    size_type num;

    /* data */
public:

    class iterator: public std::iterator<std::bidirectional_iterator_tag, int> // has typedefs (cf iterator_traits cplusplus)
    {
        private:
            t_list *ptr;
        public:
            iterator();
            iterator(t_list *ptr);
            iterator(const iterator &copy);
            iterator &operator=(const iterator &rhs);
            ~iterator();
            
            t_list *as_node();
            int &operator*() const;
            int *operator->() const;
            iterator& operator++(); // preincrement (++a)
            iterator operator++(int); // postincrement (a++)
            iterator& operator--();
            iterator operator--(int);
            bool operator==(const iterator &rhs) const;
            bool operator!=(const iterator &rhs) const;
    };
    
    class const_iterator: public std::iterator<std::bidirectional_iterator_tag, int> // has typedefs (cf iterator_traits cplusplus)
    {
        private:
            const t_list *ptr; // difference(1) with iterator
        public:
            const_iterator();
            const_iterator(t_list *ptr);
            const_iterator(const const_iterator &copy);
            const_iterator &operator=(const const_iterator &rhs);
            ~const_iterator();
            
            const t_list *as_node();
            const int &operator*() const; // difference(2) with iterator
            const int *operator->() const;
            const_iterator& operator++();
            const_iterator operator++(int);
            const_iterator& operator--();
            const_iterator operator--(int);
            bool operator==(const const_iterator &rhs) const;
            bool operator!=(const const_iterator &rhs) const;
    };

    // typedef std::reverse_iterator<iterator> reverse_iterator;    
    // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;    
private:

    void delete_node(t_list *node);
    void unlink_node(t_list *node);
    // void swap_cont_nodes(t_list *a, t_list *b);
    t_list *get_last_node();
    t_list *get_last_node() const;
    void insert_before(t_list *node, t_list *new_node);
    void insert_end(t_list *new_node);

public:
    // constructors & destructor
    explicit list ();
    explicit list (size_type n, const int val = int());
    list (iterator first, iterator last); // better not to call by reference, for cases like list(it, it++) (if we call by reference, first and last are the same object. We want them to copies)
    list (const list& x);
    ~list();
    list& operator= (const list& x);

    // iterator
    ft::list::iterator begin();
    ft::list::iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    // reverse_iterator rbegin();
    // const_reverse_iterator rbegin() const;
    // reverse_iterator rend();
    // const_reverse_iterator rend() const;

    //capacity
    bool empty() const;
    size_type size() const;

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
    void clear();
    void swap (list& x);
    void resize (size_type n, value_type val = value_type());

    void assign (size_type n, const value_type& val);
    void assign (iterator first, iterator last);

    iterator insert (iterator position, const value_type& val);
    void insert (iterator position, size_type n, const value_type& val);
    void insert (iterator position, iterator first, iterator last);
    iterator erase (iterator position);
    iterator erase (iterator first, iterator last);


    //operations
    void remove (const value_type& val);
    template <class Predicate>
    void remove_if (Predicate pred);
    void unique();
    template <class BinaryPredicate>
    void unique (BinaryPredicate binary_pred);
    void sort();
    template <class Compare>
    void sort (Compare comp);
    void splice (iterator position, list& x);
    void splice (iterator position, list& x, iterator i);
    void splice (iterator position, list& x, iterator first, iterator last);
    void reverse();
    void merge (list& x);
    template <class Compare>
    void merge (list& x, Compare comp);


    // debug
    void displaylist();
    void displaylist_reverse();

};
}
template <class Predicate>
void ft::list::remove_if (Predicate pred)
{
    t_list *tmp(this->lst);
    t_list *old(NULL);
    while (tmp)
    {
        old = tmp;
        tmp = tmp->next;
        if (pred(old->content))
            this->delete_node(old);
    }
}

template <class BinaryPredicate>
void ft::list::unique (BinaryPredicate binary_pred)
{
    t_list *tmp(this->lst);
    while (tmp->next)
    {
        if (binary_pred(tmp->content, tmp->next->content))
        {
            this->delete_node(tmp->next);
            tmp = this->lst;
        }
        else
            tmp = tmp->next;
    }
}
    
template <class Compare>
void ft::list::sort (Compare comp)
{
    t_list *tmp(this->lst);
    while (tmp->next)
    {
        if (comp(tmp->next->content, tmp->content)) // swap if tmp->next->content "<" tmp->content (Comp returns true if first_arg < second_arg)
        {
            this->swap_cont_nodes(tmp, tmp->next);
            tmp = this->lst;
        }
        else
            tmp = tmp->next;
    }
}

template <class Compare>
void ft::list::merge (list& x, Compare comp)
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
            if (comp(*x_it, *this_it)) // true if x_it "<" this_it
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


#endif