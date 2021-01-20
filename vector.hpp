#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm> // max


namespace ft
{

template<class T>
class iterator: public std::iterator<std::random_access_iterator_tag, T> // has typedefs (cf iterator_traits cplusplus)
{
    private:
        typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
        T* ptr;
    public:
        iterator(): ptr(NULL) {};
        iterator(T *ptr): ptr(ptr) {};
        iterator(const iterator &copy): ptr(copy.ptr) {};
        iterator &operator=(const iterator &rhs)
        {
            this->ptr = rhs.ptr;
            return *this;
        };
        ~iterator() {};
        
        T &operator*() const
        {
            return *this->ptr;
        };
        T &operator[](difference_type n) const
        {
            return this->ptr[n];
        };
        T *operator->() const
        {
            return this->ptr;
        };
        T *get_ptr() const
        {
            return this->ptr;
        }
        // substracting two pointers returns a difference_type
        difference_type operator-(const iterator &rhs)
        {
            return (this->ptr - rhs.ptr);
        }

        // unlike ++ += -- -=, these operators do not modify this: they return a new iterator
        iterator operator-(difference_type n)
        {
            return iterator(this->ptr - n);
        }
        iterator operator+(difference_type n)
        {
            return iterator(this->ptr + n);
        }
        // non member overload made friend in order to access ptr
        template <class X>
        friend ft::iterator<X> operator+(typename ft::iterator<X>::difference_type n, const ft::iterator<X> &it);
        
        iterator& operator++()// preincrement (++a)
        {
            this->ptr++;
            return *this;
        };
        iterator operator++(int) // postincrement (a++)
        {
            iterator tmp(*this);
            this->ptr++;
            return tmp;
        };
        iterator& operator--()
        {
            this->ptr--;
            return *this;
        };
        iterator& operator-=(difference_type n)
        {
            this->ptr -= n;
            return *this;
        };
        iterator& operator+=(difference_type n)
        {
            this->ptr += n;
            return *this;
        };
        iterator operator--(int)
        {
            iterator tmp(*this);
            this->ptr--;
            return tmp;
        };

        bool operator==(const iterator &rhs) const
        {
            return (this->ptr == rhs.ptr);
        }
        bool operator!=(const iterator &rhs) const
        {
            return (this->ptr != rhs.ptr);
        }
        bool operator>=(const iterator &rhs) const
        {
            return (this->ptr >= rhs.ptr);
        }
        bool operator>(const iterator &rhs) const
        {
            return (this->ptr > rhs.ptr);
        }
        bool operator<=(const iterator &rhs) const
        {
            return (this->ptr <= rhs.ptr);
        }
        bool operator<(const iterator &rhs) const
        {
            return (this->ptr < rhs.ptr);
        }
};

// we need non member to perform symetrical operations:
// 3 + it (and not only it + 3)
template<class T>
iterator<T> operator+(typename ft::iterator<T>::difference_type n, const ft::iterator<T> &it)
{
    return ft::iterator<T>(it.ptr + n);
}


template<class T>
class const_iterator: public std::iterator<std::random_access_iterator_tag, T> // has typedefs (cf iterator_traits cplusplus)
{
    // typedef node<T> node_type;
    
    private:
        // const node_type *ptr; // difference(1) with iterator
        const T* ptr;
    public:
        const_iterator();
        const_iterator(T *ptr);
        const_iterator(const const_iterator &copy);
        const_iterator(ft::iterator<T> copy); // difference(4)
        const_iterator &operator=(const const_iterator &rhs);
        ~const_iterator();
        
        const T &operator*() const; // difference(2) with iterator
        const T *operator->() const; // difference(3) with iterator
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator &rhs) const;
        bool operator!=(const const_iterator &rhs) const;
};



template<class T>
class vector
{
private:
    // member types
    typedef T value_type; // 1st param of template
    typedef unsigned long size_type;

private:
    T *base;
    size_t size_;
    size_t capacity_;

public:
    
    typedef iterator<T> iterator;
    typedef const_iterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;    
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;    

private:

public:
    // constructors & destructor
    explicit vector (): base(NULL), size_(0), capacity_(0) {};
    explicit vector (size_type n, const value_type& val = value_type()): base(new T[n]), size_(n), capacity_(n)
    {
        for (size_type i = 0; i < n; i++)
            this->base[i] = val;
    };
    // template <class InputIterator>
    // vector (InputIterator first, InputIterator last);
    vector(iterator first, iterator last): base(new T[last - first]), size_(last - first), capacity_(last - first)
    {
        iterator it = first;
        for (size_type i = 0; i < this->size_; i++)
        {
            this->base[i] = *it;
            it++;
        }
    };
    // vector (const vector& x): base(new T[x.capacity_]), size_(x.size_), capacity_(x.size_)
    // {
    //     const_iterator it = x.begin();
    //     for (size_type i = 0; i < this->size_; i++)
    //     {
    //         this->base[i] = *it;
    //         it++;
    //     }
    // }
    ~vector()
    {
        delete [] this->base;
    };
    vector& operator= (const vector& x);

    // iterator
    iterator begin()
    {
        return iterator(this->base);
    };
    iterator end()
    {
        return iterator(this->base + this->size_);
    };
    const_iterator begin() const;
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    // capacity
    bool empty() const;
    size_type size() const 
    { 
        return this->size_; 
    };
    size_type capacity() const 
    { 
        return this->capacity_; 
    };
    size_type max_size() const;
    void resize (size_type n, value_type val = value_type());

    // // element access
    // T &front();
    // const T &front() const;
    // T &back();
    // const T &back() const;

    // modifiers
    void assign (size_type n, const value_type& val);
    void assign (iterator first, iterator last);
    // template<class inputiterator> // not ready either
    // void assign (inputiterator first, inputiterator last)
    void push_back(const value_type& val)
    {
        if (this->capacity_ > this->size_)
        {
            this->base[this->size_] = val;
            this->size_++;
            return ;
        }
        if (this->capacity_)
            this->capacity_ = this->capacity_ * 2;
        else
            this->capacity_ = 1;
        T *new_base = new T[this->capacity_]; 
        for (size_type i = 0; i < this->size_; i++)
            new_base[i] = this->base[i];
        new_base[this->size_] = val;
        this->size_++;
        delete [] this->base;
        this->base = new_base;

    };
    void pop_back();
    iterator insert (iterator position, const value_type& val);
    void insert (iterator position, size_type n, const value_type& val);
    void insert (iterator position, iterator first, iterator last);
    iterator erase (iterator position);
    iterator erase (iterator first, iterator last);
    void swap (vector& x);
    void clear();

};

    // non member functions (relationnal operators)
    // -> if they need to call private members of ft::list, we add them as friend of the ft::list class
    template <class T>
    bool operator== (const vector<T>& lhs, const vector<T>& rhs);
    template <class T>
    bool operator!= (const vector<T>& lhs, const vector<T>& rhs);
    template <class T>
    bool operator<= (const vector<T>& lhs, const vector<T>& rhs);
    template <class T>
    bool operator< (const vector<T>& lhs, const vector<T>& rhs);
    template <class T>
    bool operator>= (const vector<T>& lhs, const vector<T>& rhs);
    template <class T>
    bool operator> (const vector<T>& lhs, const vector<T>& rhs);
    template <class T>
    void swap (vector<T>& x, vector<T>& y);


}

    
// class iterator


// template<class T>
// ft::iterator<T>::iterator()
// {
// }
// template<class T>
// ft::iterator<T>::iterator(const iterator &copy): ptr(copy.ptr)
// {
// }
// template<class T>
// ft::iterator<T>::iterator(T *ptr): ptr(ptr)
// {
// }
// template<class T>
// ft::iterator<T>::~iterator()
// {
// }
// template<class T>
// ft::iterator<T> &ft::iterator<T>::operator=(const iterator &rhs)
// {
//     this->ptr = rhs.ptr;
//     return *this;
// }
// template<class T>
// T &ft::iterator<T>::operator*() const
// {
//     return this->ptr->content;
// }
// template<class T>
// T *ft::iterator<T>::operator->() const
// {
//     return &this->ptr->content;
// }
// template<class T>
// ft::iterator<T>& ft::iterator<T>::operator++() // preincrement (++a)
// {
//     this->ptr = this->ptr->next;
//     return *this;
// }
// template<class T>
// ft::iterator<T> ft::iterator<T>::operator++(int) // postincrement (a++)
// {
//     iterator tmp(*this);
//     this->ptr = this->ptr->next;
//     return tmp;
// }
// template<class T>
// ft::iterator<T>& ft::iterator<T>::operator--()
// {
//     this->ptr = this->ptr->prev;
//     return *this;    
// }
// template<class T>
// ft::iterator<T> ft::iterator<T>::operator--(int)
// {
//     iterator tmp(*this);
//     this->ptr = this->ptr->prev;
//     return tmp;
// }
// template<class T>
// bool ft::iterator<T>::operator==(const iterator &rhs) const
// {
//     return (this->ptr == rhs.ptr);
// }
// template<class T>
// bool ft::iterator<T>::operator!=(const iterator &rhs) const
// {
//     return (this->ptr != rhs.ptr);
// }


// class const iterator

// template<class T>
// ft::const_iterator<T>::const_iterator()
// {
// }
// template<class T>
// ft::const_iterator<T>::const_iterator(const const_iterator &copy): ptr(copy.ptr)
// {
// }
// // template<class T>
// // ft::const_iterator<T>::const_iterator(ft::iterator<T> copy): ptr(copy.as_node())
// // {
// // }
// template<class T>
// ft::const_iterator<T>::const_iterator(T *ptr): ptr(ptr)
// {
// }
// template<class T>
// ft::const_iterator<T>::~const_iterator()
// {
// }
// template<class T>
// ft::const_iterator<T> &ft::const_iterator<T>::operator=(const const_iterator &rhs)
// {
//     this->ptr = rhs.ptr;
//     return *this;
// }
// template<class T>
// const T &ft::const_iterator<T>::operator*() const
// {
//     return this->ptr->content;
// }
// template<class T>
// const T *ft::const_iterator<T>::operator->() const
// {
//     return &this->ptr->content;
// }
// template<class T>
// ft::const_iterator<T>& ft::const_iterator<T>::operator++() // preincrement (++a)
// {
//     this->ptr = this->ptr->next;
//     return *this;
// }
// template<class T>
// ft::const_iterator<T> ft::const_iterator<T>::operator++(int) // postincrement (a++)
// {
//     const_iterator tmp(*this);
//     this->ptr = this->ptr->next;
//     return tmp;
// }
// template<class T>
// ft::const_iterator<T>& ft::const_iterator<T>::operator--()
// {
//     this->ptr = this->ptr->prev;
//     return *this;    
// }
// template<class T>
// ft::const_iterator<T> ft::const_iterator<T>::operator--(int)
// {
//     const_iterator tmp(*this);
//     this->ptr = this->ptr->prev;
//     return tmp;
// }
// template<class T>
// bool ft::const_iterator<T>::operator==(const const_iterator &rhs) const
// {
//     return (this->ptr == rhs.ptr);
// }
// template<class T>
// bool ft::const_iterator<T>::operator!=(const const_iterator &rhs) const
// {
//     return (this->ptr != rhs.ptr);
// }


// // list class

// // private functions

// template<class T>
// void ft::list<T>::delete_node(node_type *node)
// {
//     if (node == this->lst) // we dont want to delete the past the end node
//         return;
//     node->unlink();
//     delete node;
// }

// template<class T>
// void ft::list<T>::insert_before(node_type *node, node_type *inserted_node)
// {
//     // update node before and node in list where inserted
//     // set next and prev of new_node
//     node->prev->next = inserted_node;
//     inserted_node->prev = node->prev;
//     node->prev = inserted_node;
//     inserted_node->next = node;
// }



// // constructors & destructors

// template<class T>
// ft::list<T>::list(): lst(new node_type)
// {
// }

// template<class T>
// ft::list<T>::list(size_type n, const T val): lst(new node_type)
// {
//     for (size_type i = 0; i < n; i++)
//         this->push_back(val);
// }

// template<class T>
// ft::list<T>::list(const list<T>& x): lst(new node_type)
// {
//     const_iterator it = x.begin();
//     const_iterator ite = x.end();
//     while (it != ite)
//         this->push_back(*it++);
// }
    
// template<class T>
// ft::list<T>::list(ft::list<T>::iterator first, ft::list<T>::iterator last): lst(new node_type)
// {
//     for (ft::list<T>::iterator it = first; it != last; it++)
//         this->push_back(*it);
// }

// template<class T>
// ft::list<T>::list(T* first, T* last): lst(new node_type)
// {
//     for (T* it = first; it != last; it++)
//         this->push_back(*it);
// }

// template<class T>
// ft::list<T>& ft::list<T>::operator=(const list<T>& x)
// {
//     this->clear();
    
//     const_iterator it = x.begin();
//     const_iterator ite = x.end();
//     while (it != ite)
//     {
//         this->push_back(*it);
//         it++;
//     }
//     return *this;
// }

// template<class T>
// ft::list<T>::~list()
// {
//     this->clear();
//     delete this->lst;
// }

// // iterator functions

// template<class T>
// typename ft::list<T>::iterator ft::list<T>::begin()
// {
//     return iterator(this->lst->next);
// }

// template<class T>
// typename ft::list<T>::iterator ft::list<T>::end()
// {
//     return iterator(this->lst);
// }

// template<class T>
// typename ft::list<T>::const_iterator ft::list<T>::begin() const
// {
//     return const_iterator(this->lst->next);
// }

// template<class T>
// typename ft::list<T>::const_iterator ft::list<T>::end() const
// {
//     return const_iterator(this->lst);
// }

// template<class T>
// typename ft::list<T>::reverse_iterator ft::list<T>::rbegin()
// {
//     return reverse_iterator(this->end());
// }

// template<class T>
// typename ft::list<T>::reverse_iterator ft::list<T>::rend()
// {
//     return reverse_iterator(this->begin());
// }

// template<class T>
// typename ft::list<T>::const_reverse_iterator ft::list<T>::rbegin() const
// {
//     return const_reverse_iterator(this->end());
// }

// template<class T>
// typename ft::list<T>::const_reverse_iterator ft::list<T>::rend() const
// {
//     return const_reverse_iterator(this->begin());
// }


// //capacity

// template<class T>
// typename ft::list<T>::size_type ft::list<T>::size() const
// {
//     size_type ret(0);
//     const_iterator it = this->begin();
//     const_iterator ite = this->end();
//     while (it != ite)
//     {
//         ret++;
//         it++;
//     }
//     return ret;
// }

// template<class T>
// typename ft::list<T>::size_type ft::list<T>::max_size() const
// {
//     std::allocator< node_type > al;
//     return al.max_size();
// }

// template<class T>
// bool ft::list<T>::empty() const
// {
//     if (this->size() == 0)
//         return true;
//     else
//         return false;
// }


// // element access
// // Calling these functions (front & back) on an empty container causes undefined behavior (cplusplus.com)

// template<class T>
// T &ft::list<T>::front()
// {
//     return this->lst->next->content;
// }

// template<class T>
// const T &ft::list<T>::front() const
// {
//     return this->lst->next->content;
// }

// template<class T>
// T &ft::list<T>::back()
// {
//     return this->lst->prev->content;
// }

// template<class T>
// const T &ft::list<T>::back() const
// {
//     return this->lst->prev->content;
// }


// // modifiers

// template<class T>
// void ft::list<T>::push_back(const T &val)
// {
//     this->insert(this->end(), val);
// }

// template<class T>
// void ft::list<T>::pop_back()
// {
//     this->delete_node(this->lst->prev);
// }

// template<class T>
// void ft::list<T>::push_front (const value_type& val)
// {
//     this->insert(this->begin(), val);
// }

// template<class T>
// void ft::list<T>::pop_front()
// {
//     this->delete_node(this->lst->next);
// }

// template<class T>
// void ft::list<T>::clear()
// {
//     iterator it = this->begin();
//     iterator ite = this->end();
//     iterator tmp;
//     while (it != ite)
//     {
//         tmp = it;
//         tmp++;
//         delete it.as_node(); // we dont need to use delete_node, as we are deleting the whole list (no need to use unlink)
//         it = tmp;
//     }
//     // reset past-the-end node
//     this->lst->next = this->lst;
//     this->lst->prev = this->lst;
// }


// template<class T>
// void ft::list<T>::assign(size_type n, const value_type& val)
// {
//     // delete old list
//     this->clear();
//     // assign new list
//     for (size_type i = 0; i < n; i++)
//         this->push_back(val);
// }

// template<class T>
// void ft::list<T>::assign (iterator first, iterator last)
// {
//     // delete old list
//     this->clear();
//     // assign new list
//     for (iterator it = first; it != last; it++)
//         this->push_back(*it);
// }

// template<class T>
// void ft::list<T>::swap (list& x)
// {
//     node_type *tmp(this->lst);
//     this->lst = x.lst;
//     x.lst = tmp;
// }
    
// template<class T>
// void ft::list<T>::resize (size_type n, value_type val)
// {
//     if (n > this->size())
//     {
//         while (this->size() != n)
//             this->push_back(val);
//     }
//     else
//     {
//         while (this->size() != n)
//             this->pop_back();
//     }
// }

// template<class T>
// typename ft::list<T>::iterator ft::list<T>::insert(iterator position, const value_type& val)
// {
//     this->insert_before(position.as_node(), new node_type(val));
//     return --position;
// }

// template<class T>
// void ft::list<T>::insert(iterator position, size_type n, const value_type& val)
// {
//     for (size_type i = 0; i < n; ++i)
//         this->insert_before(position.as_node(), new node_type(val));
// }

// template<class T>
// void ft::list<T>::insert(iterator position, iterator first, iterator last)
// {
//     // prevent infinite loop (this is a case of "undefined behaviour")
//     iterator it(first);
//     if (position == ++it)
//         return ;

//     for (iterator it = first; it != last ; ++it)
//         this->insert_before(position.as_node(), new node_type(*it));
// }

// template<class T>
// typename ft::list<T>::iterator ft::list<T>::erase (ft::list<T>::iterator position)
// {
//     ft::list<T>::iterator next(position);
//     next++;
//     this->delete_node(position.as_node());
//     return next;
// }

// template<class T>
// typename ft::list<T>::iterator ft::list<T>::erase (iterator first, iterator last)
// {
//     while (first != last)
//     {
//         first = this->erase(first);
//     }
//     return last;
// }


// // operations

// template<class T>
// void ft::list<T>::remove(const value_type& val)
// {
//     iterator it = this->begin();
//     iterator ite = this->end();

//     while (it != this->end())
//     {
//         if (*it == val)
//             it = this->erase(it);
//         else
//             it++;
//     }
// }

// template <class T>
// template <class Predicate>
// void ft::list<T>::remove_if (Predicate pred)
// {
//     iterator it = this->begin();
//     iterator ite = this->end();

//     while (it != this->end())
//     {
//         if (pred(*it))
//             it = this->erase(it);
//         else
//             it++;
//     }
// }

// template<class T>
// void ft::list<T>::unique()
// {
//     // smart implementation from stl source
//     iterator it = this->begin();
//     iterator it_next = it;
//     iterator ite = this->end();
//     while (++it_next != ite)
//     {
//         if (*it == *it_next)
//             this->erase(it_next);
//         else
//             it = it_next;
//         it_next = it; // if it_next erased, it_next and it are back to it
//         // else it_next and it move on
//     }
    
// }

// template <class T>
// template <class BinaryPredicate>
// void ft::list<T>::unique (BinaryPredicate binary_pred)
// {
//     iterator it = this->begin();
//     iterator it_next = it;
//     iterator ite = this->end();
//     while (++it_next != ite)
//     {
//         if (binary_pred(*it, *it_next))
//             this->erase(it_next);
//         else
//             it = it_next;
//         it_next = it;
//     }
// }

// template<class T>
// void ft::list<T>::sort()
// {
//     iterator it = this->begin();
//     iterator it_next = it;
//     iterator ite = this->end();
//     while (++it_next != this->end())
//     {
//         if (*it > *it_next)
//         {
//             this->splice(it, *this, it_next);
//             it = this->begin();
//             it_next = it;
//         }
//         else
//             it = it_next;
//     }
// }

// template <class T>
// template <class Compare>
// void ft::list<T>::sort (Compare comp)
// {
//     iterator it = this->begin();
//     iterator it_next = it;
//     iterator ite = this->end();
//     while (++it_next != this->end())
//     {
//         if (comp(*it_next, *it))
//         {
//             this->splice(it, *this, it_next);
//             it = this->begin();
//             it_next = it;
//         }
//         else
//             it = it_next;
//     }
// }


// template<class T>
// void ft::list<T>::splice (iterator position, list& x)
// {
//     if (*this == x) // behaviour is "undefined" in that case
//         return ;
//     iterator it = x.begin();
//     iterator tmp(it);
//     while (it != x.end())
//     {
//         tmp++;
//         it.as_node()->unlink();
//         this->insert_before(position.as_node(), it.as_node());
//         it = tmp;
//     }
// }

// template<class T>
// void ft::list<T>::splice (iterator position, list& x, iterator i)
// {
//     // x may be *this if position points to an element not actually being spliced (i != position)
//     // if position == i++ (position == j): no splice to be done
//     iterator j = i;
//     j++;
//     if (position == i || position == j)
//         return ;

//     (void)x; // x is not needed... needed in the source for a "check_equal_allocator" function, whose behaviour I dont know... maybe ras as it concerns allocators ?
//     i.as_node()->unlink();
//     this->insert_before(position.as_node(), i.as_node());
// }

// template<class T>
// void ft::list<T>::splice (iterator position, list& x, iterator first, iterator last)
// {
//     // "undefined: if position in [first, last]
//     iterator j = first;
//     while (j != last)
//     {
//         if (position == j)
//             return ;
//         j++;
//     }

//     (void)x;
//     iterator it = first;
//     iterator tmp(it);
//     while (it != last)
//     {
//         tmp++;
//         it.as_node()->unlink();
//         this->insert_before(position.as_node(), it.as_node());
//         it = tmp;
//     }
// }

// template<class T>
// void ft::list<T>::reverse()
// {
//     // start from end of the list, and "reverse" every node
//     // then reverse past_the_end node
//     node_type *tmp(this->lst->prev);
//     while (tmp != this->lst)
//     {
//         tmp->reverse();
//         tmp = tmp->next;
//     }
//     tmp->reverse();
// }

// template<class T>
// void ft::list<T>::merge (list& x)
// {
//     if (this == &x)
//         return ;
//     iterator this_it = this->begin();
//     iterator x_it = x.begin();
//     iterator tmp(x_it);
//     // for each element in x, go through this to find where to insert it
//     while (x_it != x.end())
//     {
//         tmp++;
//         while (this_it != this->end())
//         {
//             if (*x_it < *this_it)
//             {
//                 this->splice(this_it, x, x_it);
//                 break;
//             }
//             else
//                 this_it++;
//         }
//         if (this_it == this->end()) // if couldnt insert it before, insert it at the end
//             this->splice(this_it, x, x_it);
//         x_it = tmp;
//     }
// }

// template <class T>
// template <class Compare>
// void ft::list<T>::merge (list& x, Compare comp)
// {
//     if (this == &x)
//         return ;
//     iterator this_it = this->begin();
//     iterator x_it = x.begin();
//     iterator tmp(x_it);
//     // for each element in x, go through this to find where to insert it
//     while (x_it != x.end())
//     {
//         tmp++;
//         while (this_it != this->end())
//         {
//             if (comp(*x_it, *this_it)) // if x_it "<" this_it
//             {
//                 this->splice(this_it, x, x_it);
//                 break;
//             }
//             else
//                 this_it++;
//         }
//         if (this_it == this->end()) // if couldnt insert it before, insert it at the end
//             this->splice(this_it, x, x_it);
//         x_it = tmp;
//     }
// }


// // non members

// template<class T>
// bool ft::operator==(const list<T>& lhs, const list<T>& rhs)
// {
//     if (lhs.size() != rhs.size())
//         return false;
//     typename ft::list<T>::const_iterator it_l = lhs.begin();
//     typename ft::list<T>::const_iterator it_r = rhs.begin();
//     while (it_l != lhs.end())
//     {
//         if (*it_l++ != *it_r++)
//             return false;
//     }
//     return true;
// }
// template<class T>
// bool ft::operator<(const list<T>& lhs, const list<T>& rhs)
// {
//     typename ft::list<T>::const_iterator it_l = lhs.begin();
//     typename ft::list<T>::const_iterator it_r = rhs.begin();
//     while (it_l != lhs.end() && it_r != rhs.end())
//     {
//         if (*it_l == *it_r)
//         {
//             it_l++;
//             it_r++;
//         }
//         else
//             return (*it_l < *it_r);
//     }
//     // so far all elements compare equal
//     // 3 cases:
//     // 1. it_l == end && it_r == end -> equal ==> return FALSE
//     // 2. it_l == end only ==> l is shorther ==> return TRUE
//     // 3. it_r == end only ==> r is shorter ==> return FALSE
//     if (it_r != rhs.end())
//         return true;
//     return false;
// }
// template<class T>
// bool ft::operator<=(const list<T>& lhs, const list<T>& rhs)
// {
//     return (lhs == rhs || lhs < rhs );
// }
// template<class T>
// bool ft::operator!=(const list<T>& lhs, const list<T>& rhs)
// {
//     return (!(lhs == rhs));
// }
// template<class T>
// bool ft::operator>=(const list<T>& lhs, const list<T>& rhs)
// {
//     if ( lhs < rhs)
//         return false;
//     return true;
// }
// template<class T>
// bool ft::operator>(const list<T>& lhs, const list<T>& rhs)
// {
//     if ( lhs <= rhs)
//         return false;
//     return true;
// }

// template<class T>
// void ft::swap (list<T>& x, list<T>& y)
// {
//     x.swap(y);
// }



#endif