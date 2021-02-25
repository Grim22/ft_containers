#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <utility> // pair
#include <functional> // less, binary_function

#include "reverse_iterator.hpp"


// 00072   // Red-black tree class, designed for use in implementing STL
// 00073   // associative containers (set, multiset, map, and multimap). The
// 00074   // insertion and deletion algorithms are based on those in Cormen,
// 00075   // Leiserson, and Rivest, Introduction to Algorithms (MIT Press,
// 00076   // 1990), except that
// 00077   //
// 00078   // (1) the header cell is maintained with links not only to the root
// 00079   // but also to the leftmost node of the tree, to enable constant
// 00080   // time begin(), and to the rightmost node of the tree, to enable
// 00081   // linear time performance when used with the generic set algorithms
// 00082   // (set_union, etc.)
// 00083   // 
// 00084   // (2) when a node being deleted has two children its successor node
// 00085   // is relinked into its place, rather than copied, so that the only
// 00086   // iterators invalidated are those referring to the deleted node.

namespace ft
{
template <class T>
struct map_node
{
    map_node* left;
    map_node* right;
    T value; 

    map_node(): left(NULL), right(NULL), value(T())
    {};
    map_node(T val):left(NULL), right(NULL), value(val)
    {};
    
    // functions below work only with std::pair as template argument
    map_node* search_max()
    {
        map_node *tmp = this;
        while (tmp->right != NULL)
            tmp = tmp->right;
        return tmp;
    }
    map_node* search_min()
    {
        map_node *tmp = this;
        while (tmp->left != NULL)
            tmp = tmp->left;
        return tmp;
    }
    map_node *search_max_parent()
    {
        map_node *tmp = this;
        if (tmp->right == NULL)
            return NULL;
        while (tmp->right->right != NULL)
            tmp = tmp->right;
        return tmp;
    }
};

// helper functions for BST
// Rq: as they are recursive and/or use a reference to pointer to map_node as argument, there is no need to put them inside the map_node class

template <class T, class compare>
std::pair<map_node<T>*, bool> insert_map_node(map_node<T> *&root, T elem, compare comp)
{
    if (root == NULL)
    {
        root = new map_node<T>(elem);
        return std::make_pair(root, true);
    }
    if (!comp(root->value.first, elem.first) && !comp(elem.first, root->value.first)) // ==
        return std::make_pair(root, false);
    else if (comp(root->value.first, elem.first)) // root->value.first < elem.first
        return (insert_map_node(root->right, elem, comp));
    else
        return (insert_map_node(root->left, elem, comp)); // >
}
template <class T, class compare>
map_node<T> *search_map_node(map_node<T> *root, typename T::first_type key, compare comp)
{
    if (root == NULL || (!comp(root->value.first, key) && !comp(key, root->value.first))) // == or NULL
        return root;
    if (comp(root->value.first, key)) // root->value.first < key
        return search_map_node(root->right, key, comp);
    else
        return search_map_node(root->left, key, comp); // >
}
template <class T, class compare>
size_t delete_map_node(map_node<T> *&root, typename T::first_type key, compare comp)
{
     if (root == NULL)
         return 0;
    if (!comp(root->value.first, key) && !comp(key, root->value.first)) // ==
    {
        // case #1: root has no child: delete root and set is to NULL
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return 1;
        }
        // case #2: root has 1 child: relink child to root parent, then delete root
        if (root->right && root->left == NULL)
        {
            map_node<T> *child = root->right;
            delete root;
            root = child; // (root is a reference to root->left / root->right from the previous call (in root's parent). So when we modify root we modify parent->left or parent->right)
            return 1;
        }
        if (root->left && root->right == NULL)
        {
            map_node<T> *child = root->left;
            delete root;
            root = child;
            return 1;
        }
        // case 3: root has 2 children
        else
        {
            // relink max of left subtree in place of root:
            // alternative: relink min of right subtree

            // 1 - find max and max_parent
            map_node<T> *max = root->left->search_max();
            map_node<T> *max_parent = root->left->search_max_parent();
            if (max_parent == NULL)
                max_parent = root;

            // 2 - link max parent to max's child (max can have only one child: left)
            if (max == max_parent->left)
                max_parent->left = max->left;
            else
                max_parent->right = max->left;
            
            // 3 - update max left and right
            max->left = root->left;
            max->right = root->right;
            
            // 4 - delete root
            delete root;
            // 5 - link root parent to max (root is a reference to root->left / root->right from the previous call (in root's parent). So when we modify root we modify parent->left or parent->right
            root = max;

            return 1;
        }
    }
    if (comp(root->value.first, key)) // root->value.first < key
        return (delete_map_node(root->right, key, comp));
    else
        return (delete_map_node(root->left, key, comp));
}

namespace mp
{
    // iterators defined below:
    // - store the root of the BST + a pointer to the node 
    // - are "circular", in the sense that iterating (++ / --) on iterator with NULL ptr (corresponding to the element past the end / before the start) will go to the first/last element of the BST
    template <class T, class compare>
    class iterator: public std::iterator<std::bidirectional_iterator_tag, T> // has typedefs (cf iterator_traits cplusplus)
    {
        public:
        typedef map_node<T> node_type;
        typedef T value_type;

        public:
            node_type *ptr;
            node_type *const *root; // pointer on this->root (so when this->root is updated, it is also updated)
            // rq:: node_type *const *root means that root is a pointer to a const pointer: *root cannot be changed (we dont need to change it)
            compare cmp;
        public:
            iterator(): ptr(NULL), root(NULL){};
            iterator(node_type *ptr, node_type *const *root, compare cmp): ptr(ptr), root(root), cmp(cmp) {};
            iterator(const iterator &copy): ptr(copy.ptr), root(copy.root), cmp(copy.cmp) {};
            iterator &operator=(const iterator &rhs)
            {
                this->ptr = rhs.ptr;
                this->root = rhs.root;
                this->cmp = rhs.cmp;
                return *this;
            };
            ~iterator() {};
            
            value_type &operator*() const
            {
                return this->ptr->value;
            };
            value_type *operator->() const
            {
                return &this->ptr->value;
            };
            iterator& operator++() 
            {
                if (this->ptr == NULL) // past_the_end or before_the_begining -> go to first elem
                {
                    this->ptr = (*this->root)->search_min();
                    return *this; 
                }
                if (this->ptr->right) // if righ subtree, return leftmost of right subtree
                {
                    // std::cout << "right" << std::endl;
                    this->ptr = this->ptr->right->search_min();
                    return *this;
                }
                // else go down the tree from root
                // visit each parent node
                // return the "deepest" parent node for which key is in left
                node_type *tmp(*this->root);
                typename T::first_type key(this->ptr->value.first);
                node_type *ret(NULL); // will store the successor (or NULL if no successor if found)
                // std::cout << "go down" << std::endl;
                while (this->cmp(key, tmp->value.first) || this->cmp(tmp->value.first, key))
                {
                    if (this->cmp(key, tmp->value.first)) // key is left (key < tmp->value.first) -> update ret
                    {
                        ret = tmp;
                        tmp = tmp->left;
                    }   
                    else // key is right -> do not update right
                        tmp = tmp->right;
                }
                this->ptr = ret;
                return *this;
            };
            iterator operator++(int) // postincrement (a++)
            {
                iterator tmp(*this);
                ++*this;
                return tmp;
            }
            iterator& operator--()
            {
                if (this->ptr == NULL) // go to last elem
                {
                    this->ptr = (*this->root)->search_max();
                    return *this;
                }
                if (this->ptr->left) 
                {
                    // std::cout << "left" << std::endl;
                    this->ptr = this->ptr->left->search_max();
                    return *this;
                }
                node_type *tmp(*this->root);
                typename T::first_type key(this->ptr->value.first);
                node_type *ret(NULL);
                // std::cout << "go down" << std::endl;
                while (this->cmp(key, tmp->value.first) ||this->cmp(tmp->value.first, key))
                {
                    if (!this->cmp(key, tmp->value.first)) 
                    {
                        ret = tmp;
                        tmp = tmp->right;
                    }
                    else
                        tmp = tmp->left;
                }
                this->ptr = ret;
                return *this;
            };
            iterator operator--(int)
            {
                iterator tmp(*this);
                --*this;
                return tmp;
            }
            bool operator==(const iterator &rhs) const
            {
                return (this->ptr == rhs.ptr);
            }
            bool operator!=(const iterator &rhs) const
            {
                return (this->ptr != rhs.ptr);
            }
    };

    template <class T, class compare>
    class const_iterator: public std::iterator<std::bidirectional_iterator_tag, const T> // has typedefs (cf iterator_traits cplusplus)
    {
        public:
        typedef map_node<T> node_type;
        typedef T value_type;

        public:
            const node_type *ptr; // diff (1)
            node_type *const *root; 
            compare cmp;
        public:
            const_iterator(): ptr(NULL), root(NULL){};
            const_iterator(node_type *ptr, node_type*const *root, compare cmp): ptr(ptr), root(root), cmp(cmp) {};
            const_iterator(const const_iterator &copy): ptr(copy.ptr), root(copy.root), cmp(copy.cmp) {};
            const_iterator(const iterator<T, compare> &copy): ptr(copy.ptr), root(copy.root), cmp(copy.cmp) {}; // diff (4)
            const_iterator &operator=(const const_iterator &rhs)
            {
                this->ptr = rhs.ptr;
                this->root = rhs.root;
                this->cmp = rhs.cmp;
                return *this;
            };
            ~const_iterator() {};
            
            const value_type &operator*() const // diff (2)
            {
                return this->ptr->value;
            };
            const value_type *operator->() const // diff (3)
            {
                return &this->ptr->value;
            };
            const_iterator& operator++()
            {
                if (this->ptr == NULL)
                {
                    this->ptr = (*this->root)->search_min();
                    return *this; 
                }

                if (this->ptr->right) 
                {
                    this->ptr = this->ptr->right->search_min();
                    return *this;
                }
                node_type *tmp(*this->root);
                typename T::first_type key(this->ptr->value.first);
                node_type *ret(NULL); 
                // std::cout << "go down" << std::endl;
                while (this->cmp(key, tmp->value.first) || this->cmp(tmp->value.first, key))
                {
                    if (this->cmp(key, tmp->value.first)) // key is left (key < tmp->value.first) -> update ret
                    {
                        ret = tmp;
                        tmp = tmp->left;
                    }
                    else 
                        tmp = tmp->right;
                }
                this->ptr = ret;
                return *this;
            };
            const_iterator operator++(int) 
            {
                const_iterator tmp(*this);
                ++*this;
                return tmp;
            }
            const_iterator& operator--()
            {
                if (this->ptr == NULL)
                {
                    this->ptr = (*this->root)->search_max();
                    return *this; 
                }
                if (this->ptr->left) 
                {
                    // std::cout << "left" << std::endl;
                    this->ptr = this->ptr->left->search_max();
                    return *this;
                }
                node_type *tmp(*this->root);
                typename T::first_type key(this->ptr->value.first);
                node_type *ret(NULL); 
                // std::cout << "go down" << std::endl;
                while (this->cmp(key, tmp->value.first) || this->cmp(tmp->value.first, key))
                {
                    if (!this->cmp(key, tmp->value.first)) 
                    {
                        ret = tmp;
                        tmp = tmp->right;
                    }
                    else
                        tmp = tmp->left;
                }
                this->ptr = ret;
                return *this;
            };
            const_iterator operator--(int)
            {
                const_iterator tmp(*this);
                --*this;
                return tmp;
            }
            bool operator==(const const_iterator &rhs) const
            {
                return (this->ptr == rhs.ptr);
            }
            bool operator!=(const const_iterator &rhs) const
            {
                return (this->ptr != rhs.ptr);
            }
    };
}


template<class key, class T, class compare = std::less<key> >
class map
{
public:
    typedef key key_type; // 1st param of template
    typedef T mapped_type; // 2st param of template
    typedef std::pair<const key, T> value_type;
    typedef compare key_compare;
    typedef unsigned long size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

    // nested class to compare two value_types based on their "key" field
    // Notice that value_compare has no public constructor, therefore no objects can be directly created from this nested class outside map members
    // value compare objects are created upon call to value_comp member function (see below)
    class value_compare: public std::binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        compare comp;
        value_compare(compare c) : comp(c) {}  // constructed with map's comparison object
    public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;
        bool operator() (const value_type& x, const value_type& y) const
        {
            return comp(x.first, y.first);
        }
    };

private:
    typedef map_node<value_type> node_type;
    node_type **root; // we store a node **root instead of a node *root, just for the sake of member function swap: a swap must not change the pointer root of our existing iterators   
    key_compare cmp; // given at construction, as template parameter. if no template param, defaults to std::less<key>

public:
    typedef ft::mp::iterator<value_type, key_compare> iterator;
    typedef ft::mp::const_iterator<value_type, key_compare> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;    
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    // typedef typename std::iterator_traits<iterator>::difference_type difference_type;
    typedef std::pair<iterator, bool> pair_iterator; // return type of insert

public:
    // constructors & destructor
    explicit map (const key_compare& comp = key_compare()): root(new node_type*), cmp(comp) 
    {
        *this->root = NULL;
    };
    template <class InputIterator> 
    map(InputIterator first, InputIterator last, const key_compare& comp = key_compare()): root(new node_type*), cmp(comp)
    {
        *this->root = NULL;
        while (first != last)
        {
            insert_map_node(*this->root, *first, this->cmp);
            first++;
        }
    }
    map (const map& x): root(new node_type*), cmp(x.cmp) // will create an unbalanced tree, as elements are inserted sorted
    {
        *this->root = NULL;
        for (const_iterator it = x.begin(); it != x.end(); it++)
            insert_map_node(*this->root, *it, this->cmp);
    }
    ~map() 
    {
        this->clear();
        delete this->root;
    };
    map& operator= (const map& x)
    {
        this->clear();
        this->cmp = x.cmp;
        for (const_iterator it = x.begin(); it != x.end(); it++)
            insert_map_node(*this->root, *it, this->cmp);
        return *this;
    };

    // iterator
    iterator begin()
    {
        if (*this->root == NULL)
            return iterator(NULL, NULL, this->cmp);
        return iterator((*this->root)->search_min(), this->root, this->cmp);
    }
    const_iterator begin() const
    {
        if (*this->root == NULL)
            return const_iterator(NULL, NULL, this->cmp);
        return const_iterator((*this->root)->search_min(), this->root, this->cmp);
    }
    iterator end()
    {
        return iterator(NULL, this->root, this->cmp);
    }
    const_iterator end() const
    {
        return const_iterator(NULL, this->root, this->cmp);
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(this->end());
    };
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(this->end());
    };
    reverse_iterator rend()
    {
        return reverse_iterator(this->begin());
    };
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(this->begin());
    };

    
    // capacity
    bool empty() const
    {
        return (this->size() == 0);
    }
    size_type size() const
    {
        size_type ret(0);
        const_iterator it(this->begin());
        const_iterator ite(this->end());
        while (it != ite)
        {
            ret++;
            it++;
        }
        return ret;
    }
    size_type max_size() const
    {
        std::allocator< node_type > al;
        return al.max_size();

    }

    // elements access
    mapped_type& operator[] (const key_type& k)
    {
        value_type elem(k, mapped_type());
        iterator it(this->insert(elem).first);
        return it->second;
    }

    // modifiers
    void erase (iterator position)
    {
        delete_map_node(*this->root, position->first, this->cmp);
    };
    void erase (iterator first, iterator last)
    {
        while (first != last)
            erase(first++);
    };
    size_type erase (const key_type& k)
    {
        return (delete_map_node(*this->root, k, this->cmp));
    };
    void clear(void)
    {
        this->delete_postfix(*this->root);
    }

    pair_iterator insert (const value_type& val)
    {
        std::pair<node_type*, bool> p = insert_map_node(*this->root, val, this->cmp);
        iterator it(p.first, this->root, this->cmp);
        return pair_iterator(it, p.second);
    };
    iterator insert (iterator position, const value_type& val)
    {
        (void)position;
        // dont know how to use that hint (if position is not a good hint, ft::insert(position, val) will insert it anyway...)
        return (this->insert(val).first);
    };
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            insert_map_node(*this->root, *first, this->cmp);
            first++;
        }
    }
    void swap (map& x)
    {
        node_type **tmp;
        tmp = this->root;
        this->root = x.root;
        x.root = tmp;
    }

    // operations
    iterator find (const key_type& k)
    {
        node_type *node(search_map_node(*this->root, k, this->cmp));
        return iterator(node, this->root, this->cmp);
    }
    const_iterator find (const key_type& k) const
    {
        node_type *node(ft::search_map_node(*this->root, k, this->cmp));
        return const_iterator(node, this->root, this->cmp);
    }
    size_type count (const key_type& k) const
    {
        if (search_map_node(*this->root, k, cmp) == NULL)
            return 0;
        return 1;
    }
    iterator lower_bound (const key_type& k)
    {
        iterator it = this->begin();
        iterator ite = this->end();
        while (it != ite && it->first < k)
            it++;
        return it;
    }
    const_iterator lower_bound (const key_type& k) const
    {
        const_iterator it = this->begin();
        const_iterator ite = this->end();
        while (it != ite && it->first < k)
            it++;
        return it;
    }
    iterator upper_bound (const key_type& k)
    {
        iterator it = this->begin();
        iterator ite = this->end();
        while (it != ite && it->first <= k)
            it++;
        return it;
    }
    const_iterator upper_bound (const key_type& k) const
    {
        const_iterator it = this->begin();
        const_iterator ite = this->end();
        while (it != ite && it->first <= k)
            it++;
        return it;
    }
    std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
    {
        return std::make_pair(this->lower_bound(k), this->upper_bound(k));
    }
    std::pair<iterator,iterator> equal_range (const key_type& k)
    {
        return std::make_pair(this->lower_bound(k), this->upper_bound(k));
    }

    // observers
    key_compare key_comp() const
    {
        return this->cmp;
    }
    value_compare value_comp() const
    {
        return value_compare(this->cmp);
    }

private:
    void delete_postfix(node_type *&root)
    {
        if (root == NULL)
            return ;
        if (root->left)
            delete_postfix(root->left);
        if (root->right)
            delete_postfix(root->right);
        delete root;
        root = NULL;
    }
};

template <class Key, class T, class Compare>
bool operator== ( const map<Key,T,Compare>& lhs, const map<Key,T,Compare>& rhs )
{
    typename ft::map<Key, T, Compare>::const_iterator it_l = lhs.begin();
    typename ft::map<Key, T, Compare>::const_iterator it_r = rhs.begin();
    while (it_l != lhs.end() && it_r != rhs.end())
    {
        if (*it_l++ != *it_r++)
            return false;
    }
    return true;
}
template <class Key, class T, class Compare>
bool operator!= ( const map<Key,T,Compare>& lhs, const map<Key,T,Compare>& rhs )
{
    return (!(lhs == rhs));
}
template <class Key, class T, class Compare>
bool operator< ( const map<Key,T,Compare>& lhs, const map<Key,T,Compare>& rhs )
{
    typename ft::map<Key, T, Compare>::const_iterator it_l = lhs.begin();
    typename ft::map<Key, T, Compare>::const_iterator it_r = rhs.begin();
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
template <class Key, class T, class Compare>
bool operator<= ( const map<Key,T,Compare>& lhs, const map<Key,T,Compare>& rhs )
{
    return (lhs == rhs || lhs < rhs );
}
template <class Key, class T, class Compare>
bool operator> ( const map<Key,T,Compare>& lhs, const map<Key,T,Compare>& rhs )
{
    return (! (lhs <= rhs) );
}
template <class Key, class T, class Compare>
bool operator>= ( const map<Key,T,Compare>& lhs, const map<Key,T,Compare>& rhs )
{
    return (! (lhs < rhs) );
}
template <class Key, class T, class Compare>
void swap (map<Key,T,Compare>& x, map<Key,T,Compare>& y)
{
    x.swap(y);
}
} // end of namespace ft scope

#endif