#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <iterator>
#include <memory>

// list of int (1st param of template = int, and second param is set to default)

typedef struct s_list
{
    int content; // stl containers internally store copies
    struct s_list *prev;
    struct s_list *next;
    void reverse();
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
            const int *operator->() const; // difference(3) with iterator
            const_iterator& operator++();
            const_iterator operator++(int);
            const_iterator& operator--();
            const_iterator operator--(int);
            bool operator==(const const_iterator &rhs) const;
            bool operator!=(const const_iterator &rhs) const;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;    
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;    
private:

    void delete_node(t_list *node);
    void unlink_node(t_list *node);
    void insert_before(t_list *node, t_list *new_node);

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
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    //capacity
    bool empty() const;
    size_type size() const;
    size_type max_size() const;

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

};

    // non member functions (relationnal operators)
    // -> if they need to call private members of ft::list, we add them as friend of the ft::list class

    bool operator== (const list& lhs, const list& rhs);
    bool operator!= (const list& lhs, const list& rhs);
    bool operator<= (const list& lhs, const list& rhs);
    bool operator< (const list& lhs, const list& rhs);
    bool operator>= (const list& lhs, const list& rhs);
    bool operator> (const list& lhs, const list& rhs);


}
template <class Predicate>
void ft::list::remove_if (Predicate pred)
{
    iterator it = this->begin();
    iterator ite = this->end();

    while (it != this->end())
    {
        if (pred(*it))
            it = this->erase(it);
        else
            it++;
    }
}

template <class BinaryPredicate>
void ft::list::unique (BinaryPredicate binary_pred)
{
    iterator it = this->begin();
    iterator it_next = it;
    iterator ite = this->end();
    while (++it_next != ite)
    {
        if (binary_pred(*it, *it_next))
            this->erase(it_next);
        else
            it = it_next;
        it_next = it;
    }
}
    
template <class Compare>
void ft::list::sort (Compare comp)
{
    iterator it = this->begin();
    iterator it_next = it;
    iterator ite = this->end();
    while (++it_next != this->end())
    {
        if (comp(*it_next, *it))
        {
            this->splice(it, *this, it_next);
            it = this->begin();
            it_next = it;
        }
        else
            it = it_next;
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
    // for each element in x, go through this to find where to insert it
    while (x_it != x.end())
    {
        tmp++;
        while (this_it != this->end())
        {
            if (comp(*x_it, *this_it)) // if x_it "<" this_it
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

#endif