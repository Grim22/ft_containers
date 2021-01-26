#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm> // max
#include <stdexcept> // out of range error


namespace ft
{


namespace vec // for iterator definition, to differentiate them from other container iterator
{

// we define one templated itereator class, that can represent both iterator and const_iterator
// here template argument T is a pointer type
// cf. __normal_iterator of stl_iterator.h
// TO DO: add non member comparison operators, to make possible comparison between const and non const iterators (and more)

template<class T>
class iterator
{
    private:
        T ptr;
    public:
        // T is a pointer (int * for eg). so it is also an iterator, so iterator_traits works on it
        // sometimes we want to return int or int & --> we will use value_type and reference (we can't use *T to design "int") 
        typedef typename std::iterator_traits<T>::value_type value_type; //
        typedef typename std::iterator_traits<T>::reference reference;
        typedef typename std::iterator_traits<T>::pointer pointer;
        typedef typename std::iterator_traits<T>::difference_type difference_type;
        typedef typename std::iterator_traits<T>::iterator_category iterator_category;
        // Rq: if T is of type const int *, value type will be CONST int and reference type will be CONST reference
        // those typedefs are also needed by standard algorithm (for ex. by std::reverse_iterator<iterator> ?). cf std::iterator_traits on cplusplus.com
        
        iterator(): ptr(NULL) {};
        
        // to work with our template constructor below, we replace the 1st form (T ptr) with two alternatives (if we keep only the first form, the compiler gets mixed up)
        // iterator(T ptr): ptr(ptr) {};
        iterator(value_type* ptr): ptr(ptr) {};
        iterator(const value_type* ptr): ptr(ptr) {};

        
        // this contructor is suposed to accept iterators and const_iterators (to allow construction of a const_iterator from an iterator)
        // as it is now, it accepts everything --> enable_if needed to make it compliant
        template <class it>
        iterator(it copy): ptr(copy.base()) {};
        // iterator(const iterator &copy): ptr(copy.ptr) {}; // not needed if templated version below is present
        
        iterator &operator=(const iterator &rhs)
        {
            this->ptr = rhs.ptr;
            return *this;
        };
        ~iterator() {};

        // (1) access        
        reference operator*() const
        {
            return *this->ptr;
        };
        reference operator[](difference_type n) const
        {
            return this->ptr[n];
        };
        pointer operator->() const
        {
            return this->ptr;
        };
        pointer base() const // access to the underlying pointer (read access only) --> done this way in the stl iterator
        {
            return this->ptr;
        }

        // (2) arithmetics

        // (2.1) binary
        // substracting two pointers returns a difference_type
        difference_type operator-(const iterator &rhs) const
        {
            return (this->ptr - rhs.ptr);
        }

        // unlike ++ += -- -=, these operators do not modify this: they return a new iterator
        iterator operator-(difference_type n) const
        {
            return iterator(this->ptr - n);
        }
        iterator operator+(difference_type n) const
        {
            return iterator(this->ptr + n);

        }

        // (2.2) unary
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

        // (3) comparison
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

// we need this non member operator+ to perform symetrical operations:
// 3 + it (and not only it + 3)
template<class T>
iterator<T> operator+(typename iterator<T>::difference_type n, const iterator<T> &it)
{
    return iterator<T>(it.base() + n);
}


// Here we define iterator and const_iterator classes separately, then we use typedefs to make them member types of vector
// (we could also have defined them inside the vect)
// TO DO: add non member comparison operators, to make possible comparison between const and non const iterators (and more)

// template <class T>
// class iterator: public std::iterator<std::random_access_iterator_tag, T> // has typedefs (cf iterator_traits cplusplus)
// {
//     private:
//         T* ptr;
//     public:
//         typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
        
//         iterator(): ptr(NULL) {};
//         iterator(T *ptr): ptr(ptr) {};
//         iterator(const iterator &copy): ptr(copy.ptr) {};
//         iterator &operator=(const iterator &rhs)
//         {
//             this->ptr = rhs.ptr;
//             return *this;
//         };
//         ~iterator() {};

//         // (1) access        
//         T &operator*() const
//         {
//             return *this->ptr;
//         };
//         T &operator[](difference_type n) const
//         {
//             return this->ptr[n];
//         };
//         T *operator->() const
//         {
//             return this->ptr;
//         };
//         T *base() const // access to the underlying pointer (read access only) --> done this way in the stl iterator
//         {
//             return this->ptr;
//         }

//         // (2) arithmetics

//         // (2.1) binary
//         // substracting two pointers returns a difference_type
//         difference_type operator-(const iterator &rhs) const
//         {
//             return (this->ptr - rhs.ptr);
//         }

//         // unlike ++ += -- -=, these operators do not modify this: they return a new iterator
//         iterator operator-(difference_type n) const
//         {
//             return iterator(this->ptr - n);
//         }
//         iterator operator+(difference_type n) const
//         {
//             return iterator(this->ptr + n);

//         }

//         // (2.2) unary
//         iterator& operator++()// preincrement (++a)
//         {
//             this->ptr++;
//             return *this;
//         };
//         iterator operator++(int) // postincrement (a++)
//         {
//             iterator tmp(*this);
//             this->ptr++;
//             return tmp;
//         };
//         iterator& operator--()
//         {
//             this->ptr--;
//             return *this;
//         };
//         iterator& operator-=(difference_type n)
//         {
//             this->ptr -= n;
//             return *this;
//         };
//         iterator& operator+=(difference_type n)
//         {
//             this->ptr += n;
//             return *this;
//         };
//         iterator operator--(int)
//         {
//             iterator tmp(*this);
//             this->ptr--;
//             return tmp;
//         };

//         // (3) comparison
//         bool operator==(const iterator &rhs) const
//         {
//             return (this->ptr == rhs.ptr);
//         }
//         bool operator!=(const iterator &rhs) const
//         {
//             return (this->ptr != rhs.ptr);
//         }
//         bool operator>=(const iterator &rhs) const
//         {
//             return (this->ptr >= rhs.ptr);
//         }
//         bool operator>(const iterator &rhs) const
//         {
//             return (this->ptr > rhs.ptr);
//         }
//         bool operator<=(const iterator &rhs) const
//         {
//             return (this->ptr <= rhs.ptr);
//         }
//         bool operator<(const iterator &rhs) const
//         {
//             return (this->ptr < rhs.ptr);
//         }
// };

// // we need this non member operator+ to perform symetrical operations:
// // 3 + it (and not only it + 3)
// template<class T>
// iterator<T> operator+(typename iterator<T>::difference_type n, const iterator<T> &it)
// {
//     return iterator<T>(it.base() + n);
// }


// template<class T>
// class const_iterator: public std::iterator<std::random_access_iterator_tag, T> // has typedefs (cf iterator_traits cplusplus)
// {
    
//     private:
//         const T* ptr; // diff(0)
//     public:
//         typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
        
//         const_iterator(): ptr(NULL) {};
//         const_iterator(const T *ptr): ptr(ptr) {}; // diff(1)
//         const_iterator(const const_iterator &copy): ptr(copy.ptr) {};
//         const_iterator(const iterator<T> &copy): ptr(copy.base()) {}; // diff(2)  -- needed to be able to build a const_iterator from an iterator
//         const_iterator &operator=(const const_iterator &rhs)
//         {
//             this->ptr = rhs.ptr;
//             return *this;
//         };
//         ~const_iterator() {};
        
//         // (1) access 
//         // diff(3) -- return value is const for all of these functions
//         const T &operator*() const
//         {
//             return *this->ptr;
//         };
//         const T &operator[](difference_type n) const
//         {
//             return this->ptr[n];
//         };
//         const T *operator->() const
//         {
//             return this->ptr;
//         };
//         const T *base() const // access to the underlying pointer (read access only) --> done this way in the stl const_iterator
//         {
//             return this->ptr;
//         }

//         // (2) arithmetics
//         // (2.1) binary
//         // substracting two pointers returns a difference_type
//         difference_type operator-(const const_iterator &rhs) const
//         {
//             return (this->ptr - rhs.ptr);
//         }

//         // unlike ++ += -- -=, these operators do not modify this: they return a new const_iterator
//         const_iterator operator-(difference_type n) const
//         {
//             return const_iterator(this->ptr - n);
//         }
//         const_iterator operator+(difference_type n) const
//         {
//             return const_iterator(this->ptr + n);
//         }

//         // (2.2) unary
//         const_iterator& operator++()// preincrement (++a)
//         {
//             this->ptr++;
//             return *this;
//         };
//         const_iterator operator++(int) // postincrement (a++)
//         {
//             const_iterator tmp(*this);
//             this->ptr++;
//             return tmp;
//         };
//         const_iterator& operator--()
//         {
//             this->ptr--;
//             return *this;
//         };
//         const_iterator& operator-=(difference_type n)
//         {
//             this->ptr -= n;
//             return *this;
//         };
//         const_iterator& operator+=(difference_type n)
//         {
//             this->ptr += n;
//             return *this;
//         };
//         const_iterator operator--(int)
//         {
//             const_iterator tmp(*this);
//             this->ptr--;
//             return tmp;
//         };

//         // (3) comparison
//         bool operator==(const const_iterator &rhs) const
//         {
//             return (this->ptr == rhs.ptr);
//         }
//         bool operator!=(const const_iterator &rhs) const
//         {
//             return (this->ptr != rhs.ptr);
//         }
//         bool operator>=(const const_iterator &rhs) const
//         {
//             return (this->ptr >= rhs.ptr);
//         }
//         bool operator>(const const_iterator &rhs) const
//         {
//             return (this->ptr > rhs.ptr);
//         }
//         bool operator<=(const const_iterator &rhs) const
//         {
//             return (this->ptr <= rhs.ptr);
//         }
//         bool operator<(const const_iterator &rhs) const
//         {
//             return (this->ptr < rhs.ptr);
//         }
// };

// // we need this non member operator+ to perform symetrical operations:
// // 3 + it (and not only it + 3)
// template<class T>
// const_iterator<T> operator+(typename const_iterator<T>::difference_type n, const const_iterator<T> &it)
// {
//     return const_iterator<T>(it.base() + n);
// }

}; // end of vec scope


template<class T>
class vector
{
private:
    // member types
    typedef T value_type; // 1st param of template
    typedef unsigned long size_type;

private:
    T *base;
    size_type size_;
    size_type capacity_;

public:
    
    typedef vec::iterator<T*> iterator;
    typedef vec::iterator<const T*> const_iterator;
    // typedef vec::iterator<T> iterator;
    // typedef vec::const_iterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;    
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;    

private:
    void delete_base()
    {
        // delete [] this->base; cant do that, as our array was not allocated with new []
        for (size_type i = 0; i < this->size_; i++)
            this->base[i].~T(); // call destructor for each element
        delete this->base; // free the whole memory block // not mandatory ?
    }
public:
    // constructors & destructor

    explicit vector (): base(NULL), size_(0), capacity_(0) {};
    // first we allocate memory without calling constructor
    // then we call constructor at chosen location ("placement new", does not allocate memory)
    // Rq: alternative is to call new T[n] and then assign val to every element of the array = for each element, call default constructor then call assignement operator = expensive
    // chosen option allows us to construct only the elements we need (we allocate enough memory for [capacity] elements but only construct [size] element )
    // https://lokiastari.com/blog/2016/02/27/vector/index.html
    explicit vector (size_type n, const value_type& val = value_type()): base(reinterpret_cast<T*> (::operator new(n * sizeof(T)))), size_(n), capacity_(n)
    {
        for (size_type i = 0; i < n; i++)
            // this->base[i] = val;
            new (this->base + i) T(val);
    };
    // template <class InputIterator>
    // vector (InputIterator first, InputIterator last);
    vector(iterator first, iterator last): base(reinterpret_cast<T*>(::operator new ((last - first) * sizeof(T)))), size_(last - first), capacity_(last - first)
    {
        iterator it = first;
        for (size_type i = 0; i < this->size_; i++)
        {
            // this->base[i] = *it;
            new (this->base + i) T(*it);
            it++;
        }
    };
    vector (const vector& x): base(reinterpret_cast<T*>(::operator new (x.capacity_ * sizeof(T)))), size_(x.size_), capacity_(x.size_)
    {
        const_iterator it = x.begin();
        for (size_type i = 0; i < this->size_; i++)
        {
            // this->base[i] = *it;
            new (this->base + i) T(*it);
            it++;
        }
    }
    ~vector()
    {
        // // delete [] this->base; cant do that, as our array was not allocated with new []
        this->clear();
    };
    vector& operator= (const vector& x)
    {
        this->assign(x.begin(), x.end());
        return *this;
    };


    // iterator
    iterator begin()
    {
        return iterator(this->base);
    };
    iterator end()
    {
        return iterator(this->base + this->size_);
    };
    const_iterator begin() const
    {
        return const_iterator(this->base);
    };
    const_iterator end() const
    {
        return const_iterator(this->base + this->size_);
    };
    reverse_iterator rbegin()
    {
        return reverse_iterator(this->end());
    };
    const_reverse_iterator rbegin() const
    {
        return reverse_iterator(this->end());
    };
    reverse_iterator rend()
    {
        return reverse_iterator(this->begin());
    };
    const_reverse_iterator rend() const
    {
        return reverse_iterator(this->begin());
    };

    // capacity
    bool empty() const
    {
        return (this->size_ == 0);
    };
    size_type size() const 
    { 
        return this->size_; 
    };
    size_type capacity() const 
    { 
        return this->capacity_; 
    };
    size_type max_size() const
    {
        std::allocator< T > al;
        return al.max_size();
    };
    void resize (size_type n, value_type val = value_type())
    {
        if (this->size_ > n)
        {
            while (this->size_ > n)
            {
                this->size_--;
                this->base[this->size_].~T();
            }
            return ;
        }

        // ajust capacity
        size_type new_cap(n);
        if (n > this->capacity_ && n < this->capacity_ * 2)
            new_cap = this->capacity_ * 2;
        this->reserve(new_cap);
        // if n <= capacity, capacity will not grow
        // else if capacity < n < 2 * capacity, capacity will grow to 2*capacity
        // else (n >= 2 * cap), it will grow to n

        // add elems
        for (size_type i = this->size_; i < n; i++)
            new (this->base + i) T(val);
        this->size_ = n;
    }

    void reserve (size_type n)
    {
        if (this->capacity_ >= n) // not enough room -> reallocate
            return ;

        // create a new base, allocate it and then copy old_base into it
        T* old_base = this->base;
        this->base = reinterpret_cast<T*>(::operator new(n * sizeof(T)));
        for (size_type i = 0; i < this->size_; i++)
            new(this->base + i) T(old_base[i]);
        this->capacity_ = n;

        // free old_base
        for (size_type i = 0; i < this->size_; i++)
            old_base[i].~T();
        delete old_base;
    };

    // // element access
    T &front()
    {
        return this->base[0];
    };
    const T &front() const
    {
        return this->base[0];
    };
    T &back()
    {
        return this->base[this->size_ - 1];
    };
    const T &back() const
    {
        return this->base[this->size_ - 1];
    };
    T& operator[] (size_type n)
    {
        return this->base[n];
    };
    const T& operator[] (size_type n) const
    {
        return this->base[n];
    };
    T& at (size_type n)
    {
        if (n >= this->size_)
            throw std::out_of_range("vector");
        return this->base[n];
    };
    const T& at (size_type n) const
    {
        if (n >= this->size_)
            throw std::out_of_range("vector");
        return this->base[n];
    };


    // modifiers
    void assign (size_type n, const value_type& val)
    {
        for (size_type i = 0; i < this->size_; i++)
            this->base[i].~T();
        if (this->capacity_ < n) // not enough room -> reallocate
        {
            delete this->base;
            this->base = reinterpret_cast<T*>(::operator new(n * sizeof(T)));
            this->capacity_ = n;
        }
        this->size_ = n;

        // we use "placement new": object is constructed at the given memory location
        // we cant use assignation (this->base[i] = val), as this->base[i] is no longer a T object (we have destroyed it)
        for (size_type i = 0; i < n; i++)
            new(this->base + i) T(val);

    };
    // template<class inputiterator> // not ready either
    // void assign (inputiterator first, inputiterator last)
    void assign (const_iterator first, const_iterator last)
    {
        for (size_type i = 0; i < this->size_; i++)
            this->base[i].~T();
        if (this->capacity_ < static_cast<size_type>(last - first)) // not enough room -> reallocate
        {
            delete this->base;
            this->base = reinterpret_cast<T*>(::operator new((last - first) * sizeof(T)));
            this->capacity_ = last - first;
        }
        this->size_ = last - first;

        // we use "placement new": object is constructed at the given memory location
        // we cant use assignation (this->base[i] = val), as this->base[i] is no longer a T object (we have destroyed it)
        for (const_iterator it = first; it != last; it++)
            new(this->base + (it - first)) T(*it);

    };
    void push_back(const value_type& val)
    {
        this->resize(this->size_ + 1, val);
    };
    void pop_back()
    {
        if (this->empty())
            return ;
        this->resize(this->size_ - 1);
    };
    iterator insert (iterator position, const value_type& val)
    {
        size_type pos = position - this->begin();
        this->insert(position, 1, val);
        return this->begin() + pos;
    };
    void insert (iterator position, size_type n, const value_type& val)
    {
        size_type end = this->end() -1 - this->begin();
        size_type pos = position - this->begin();
        
        this->resize(this->size_ + n); 

        position = this->begin() + pos;
        iterator old_end = this->begin() + end;
        size_type offset(n);
        for (iterator it = old_end; it >= position ; it--)
            *(it + offset) = *it;
        for (size_type i = 0; i < n; i++)
        {
            *position = val;
            position++;
        }
    };
    
    // template <class InputIterator>
    // void insert (iterator position, InputIterator first, InputIterator last);
    void insert (iterator position, iterator first, iterator last)
    {
        // schema des etapes
        // inserer 8 et 9 dans 0 1 2 3 4 avec position = 2
        // 0 1 2 3 4 NULL
        // 0 1 2 3 4 X X NULL after resize (X is a default constructed T)
        // 0 1 2 3 2 3 4 NULL after moving elements 2 3 and 4 towards the end
        // 0 1 8 9 2 3 4 NULL after inserting 8 & 9 at position

        // save end and position "offset" (to retrieve it in case resize needs to reallocate)
        size_type end = this->end() -1 - this->begin();
        size_type pos = position - this->begin();
        
        this->resize(this->size_ + last - first); // allocates new storage if new size > capacity (the rule for determining new capacity is the same in insert as in resize)
        
        // we now have new Ts at the end of the array
        // we will do assignations to insert elements and relocate others
        
        // retrieve position and end
        position = this->begin() + pos;
        iterator old_end = this->begin() + end;

        // decaller de [offset] tous les elements de position jusqu'a old_end
        // le faire en partant de la fin, pour eviter "decraser" des elements
        size_type offset(last - first);
        for (iterator it = old_end; it >= position ; it--)
            *(it + offset) = *it;
        // inserer a position les elements de first a last
        for (iterator it = first; it < last ; it++)
        {
            *position = *it;
            position++;
        }
        
    };
    iterator erase (iterator position);
    iterator erase (iterator first, iterator last);
    void swap (vector& x);
    void clear()
    {
        this->delete_base();
        this->size_ = 0;
        this->capacity_ = 0;
    };
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