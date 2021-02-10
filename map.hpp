#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <utility> // pair


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
};

namespace mp
{
    template <class T>
    class iterator: public std::iterator<std::bidirectional_iterator_tag, T> // has typedefs (cf iterator_traits cplusplus)
    {
        public:
        typedef map_node<T> node_type;
        typedef T value_type;

        public:
            node_type *ptr;
            node_type *const *root; // pointer on this->root (so when this->root is updated, it is also updated)
            // rq:: node_type *const *root means that root is a pointer to a const pointer: *root cannot be changed (we dont need to change it)
        public:
            iterator(): ptr(NULL), root(NULL){};
            iterator(node_type *ptr, node_type *const *root): ptr(ptr), root(root) {};
            // void get_root_value()
            // {
            //     std::cout << "it root: " << (*this->root)->value.first << std::endl;
            // };
            iterator(const iterator &copy): ptr(copy.ptr), root(copy.root) {};
            iterator &operator=(const iterator &rhs)
            {
                this->ptr = rhs.ptr;
                this->root = rhs.root;
                return *this;
            };
            ~iterator() {};
            
            // node_type *as_node(); // needed to access node from outisde the class (from list for example): it would be better to declare list as a friend class (thats the way it is done in the STL) but we're not allowed to
            // const node_type *as_node() const;
            value_type &operator*() const
            {
                return this->ptr->value;
            };
            value_type *operator->() const
            {
                return &this->ptr->value;
            };
            iterator& operator++() // preincrement (++a)
            {
                if (this->ptr == NULL)
                    return *this; // if we have arrived at the end (this->ptr == NULL), ++ will have no effect

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
                while (tmp->value.first != key)
                {
                    if (tmp->value.first > key) // key is left -> update ret
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
                if (this->ptr == NULL)
                    return *this; // if we have arrived at the end (this->ptr == NULL), -- will have no effect
                if (this->ptr->left) 
                {
                    // std::cout << "left" << std::endl;
                    this->ptr = this->ptr->left->search_max();
                    return *this;
                }
                node_type *tmp(*this->root);
                typename T::first_type key(this->ptr->value.first);
                node_type *ret(NULL); // will store the successor (or NULL if no successor if found)
                // std::cout << "go down" << std::endl;
                while (tmp->value.first != key)
                {
                    if (tmp->value.first < key) 
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

    template <class T>
    class const_iterator: public std::iterator<std::bidirectional_iterator_tag, T> // has typedefs (cf iterator_traits cplusplus)
    {
        typedef map_node<T> node_type;
        typedef T value_type;

        public:
            const node_type *ptr; // diff (1)
            node_type *const *root; 
        public:
            const_iterator(): ptr(NULL), root(NULL){};
            const_iterator(node_type *ptr, node_type*const *root): ptr(ptr), root(root) {};
            // void get_root_value()
            // {
            //     std::cout << "it root: " << (*this->root)->value.first << std::endl;
            // };
            const_iterator(const const_iterator &copy): ptr(copy.ptr), root(copy.root) {};
            const_iterator(const iterator<T> &copy): ptr(copy.ptr), root(copy.root) {}; // diff (4)
            const_iterator &operator=(const const_iterator &rhs)
            {
                this->ptr = rhs.ptr;
                this->root = rhs.root;
                return *this;
            };
            ~const_iterator() {};
            
            // node_type *as_node(); 
            // const node_type *as_node() const;
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
                    return *this; 

                if (this->ptr->right) 
                {
                    this->ptr = this->ptr->right->search_min();
                    return *this;
                }
                node_type *tmp(*this->root);
                typename T::first_type key(this->ptr->value.first);
                node_type *ret(NULL); 
                // std::cout << "go down" << std::endl;
                while (tmp->value.first != key)
                {
                    if (tmp->value.first > key) 
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
                    return *this; 
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
                while (tmp->value.first != key)
                {
                    if (tmp->value.first < key) 
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

// the functions below cant stay here alone
// -> put them inside map as private functions
// Rq: they can't be called with "this", instead of "root", as they are recursive

template <class T>
std::pair<map_node<T>*, bool> insert(map_node<T> *&root, T elem)
{
    if (root == nullptr)
    {
        root = new map_node<T>(elem);
        return std::pair<map_node<T>*, bool>(root, true);
    }
    if (root->value.first == elem.first)
        return std::pair<map_node<T>*, bool>(root, false);
    else if (root->value.first > elem.first)
        return (insert(root->left, elem));
    else
        return (insert(root->right, elem));
}

template <class T>
map_node<T> *search(map_node<T> *root, T elem)
{
    if (root == NULL || root->value.first == elem.first)
        return root;

    if (root->value.first > elem.first)
        return search(root->left, elem);
    else
        return search(root->right, elem);
}

// template <class key_type, class value_type>
// map_node<key_type, value_type> *search_parent_ptr(map_node<key_type, value_type> *root, key_type key)
// {
//     if (root == NULL || root->key == key)
//         return root;

//     if (root->key > key)
//         return search(root->left, key);
//     else
//         return search(root->right, key);
// }

template <class T>
map_node<T> *search_min(map_node<T> *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

template <class T>
map_node<T> *search_max(map_node<T> *root)
{
    while (root->right != NULL)
        root = root->right;
    return root;
}

template <class T>
map_node<T> *search_max_parent(map_node<T> *root)
{
    if (root->right == NULL)
        return NULL;
    while (root->right->right != NULL)
        root = root->right;
    return root;
}

template <class T>
void delete_map_node(map_node<T> *&root, typename T::first_type key)
{
     if (root == NULL)
         return;
    if (root->value.first == key)
    {
        // case #1: root has no child: delete root and set is to NULL
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return;
        }
        // case #2: root has 1 child: relink child to root parent, then delete root
        if (root->right && root->left == NULL)
        {
            map_node<T> *child = root->right;
            delete root;
            root = child; // (root is a reference to root->left / root->right from the previous call (in root's parent). So when we modify root we modify parent->left or parent->right)
            return ;
        }
        if (root->left && root->right == NULL)
        {
            map_node<T> *child = root->left;
            delete root;
            root = child;
            return ;
        }
        // case 3: root has 2 children
        else
        {
            // relink max of left subtree in place of root:
            // alternative: relink min of right subtree

            // 1 - find max and max_parent
            map_node<T> *max = search_max(root->left);
            map_node<T> *max_parent = search_max_parent(root->left);
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

            return ;
        }
    }
    if (root->value.first > key)
        delete_map_node(root->left, key);
    else
        delete_map_node(root->right, key);
}

// template <class key_type, class value_type>
// void print_in_order(map_node<key_type, value_type> *root)
// {
//     if (root == NULL)
//         return ;
//     if (root->left)
//         print_in_order(root->left);
//     std::cout << root->value.first << std::endl;
//     if (root->right)
//         print_in_order(root->right);
// }

template <class T>
void delete_postfix(map_node<T> *&root)
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


template<class key, class T>
class map
{
public:
    // member types
    typedef key key_type; // 1st param of template
    typedef T mapped_type; // 2st param of template
    typedef std::pair<const key, T> value_type;
    typedef unsigned long size_type;

private:
    typedef map_node<value_type> node_type;
    node_type *root;

public:
    
    typedef ft::mp::iterator<value_type> iterator;
    typedef ft::mp::const_iterator<value_type> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;    
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::pair<iterator, bool> pair_iterator; // return type of insert

public:
    // constructors & destructor
    explicit map (): root(NULL) {};
    template <class InputIterator> 
    map(InputIterator first, InputIterator last): root(NULL)
    {
        while (first != last)
        {
            ft::insert(this->root, *first);
            first++;
        }
    }
    map (const map& x): root(NULL) // will create an unbalanced tree, as elements are inserted sorted
    {
        for (const_iterator it = x.begin(); it != x.end(); it++)
            ft::insert(this->root, *it);
    }
    ~map() 
    {
        this->clear();
    };
    map& operator= (const map& x)
    {
        this->clear();
        for (const_iterator it = x.begin(); it != x.end(); it++)
            ft::insert(this->root, *it);
        return *this;
    };

    size_type erase (const key_type& k)
    {
        delete_map_node(this->root, k);
        return 0;
    };
    // void print(void)
    // {
    //     print_in_order(this->root);
    //     std::cout << "---" << std::endl;
    // }
    void clear(void)
    {
        this->delete_postfix(this->root);
    }

    // iterator
    iterator begin()
    {
        if (this->root == NULL)
            return iterator(NULL, NULL);
        return iterator(this->root->search_min(), &this->root);
    }
    const_iterator begin() const
    {
        if (this->root == NULL)
            return const_iterator(NULL, NULL);
        return const_iterator(this->root->search_min(), &this->root);
    }
    iterator end()
    {
        return iterator(NULL, &this->root);
    }
    const_iterator end() const
    {
        return const_iterator(NULL, &this->root);
    }
    // reverse_iterator rbegin()
    // {
    //     return reverse_iterator(this->end());
    // };
    // const_reverse_iterator rbegin() const
    // {
    //     return reverse_iterator(this->end());
    // };
    // reverse_iterator rend()
    // {
    //     return reverse_iterator(this->begin());
    // };
    // const_reverse_iterator rend() const
    // {
    //     return reverse_iterator(this->begin());
    // };

    pair_iterator insert (const value_type& val)
    {
        std::pair<node_type*, bool> p = ft::insert(this->root, val);
        iterator it(p.first, &this->root);
        return pair_iterator(it, p.second);
    };
    iterator insert (iterator position, const value_type& val);
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last);
    
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
    // // iterator
    // ft::list<T>::iterator begin();
    // ft::list<T>::iterator end();
    // const_iterator begin() const;
    // const_iterator end() const;
    // reverse_iterator rbegin();
    // const_reverse_iterator rbegin() const;
    // reverse_iterator rend();
    // const_reverse_iterator rend() const;

    // //capacity
    // bool empty() const;
    // size_type size() const;
    // size_type max_size() const;

    // // element access
    // T &front();
    // const T &front() const;
    // T &back();
    // const T &back() const;

    // // modifiers
    // void push_back(const T& val);
    // void pop_back();
    // void push_front (const value_type& val);
    // void pop_front();
    // void clear();
    // void swap (list& x);
    // void resize (size_type n, value_type val = value_type());

    // void assign (size_type n, const value_type& val);
    // // void assign (iterator first, iterator last);
    // template<class inputiterator> // not ready either
    // void assign (inputiterator first, typename enable_if<!is_integral<inputiterator>::val, inputiterator>::type last);

    // iterator insert (iterator position, const value_type& val);
    // void insert (iterator position, size_type n, const value_type& val);
    // template<class inputiterator>
    // void insert (iterator position, inputiterator first, typename enable_if<!is_integral<inputiterator>::val, inputiterator>::type last);
    // iterator erase (iterator position);
    // iterator erase (iterator first, iterator last);


    // //operations
    // void remove (const value_type& val);
    // template <class Predicate>
    // void remove_if (Predicate pred);
    // void unique();
    // template <class BinaryPredicate>
    // void unique (BinaryPredicate binary_pred);
    // void sort();
    // template <class Compare>
    // void sort (Compare comp);
    // void splice (iterator position, list& x);
    // void splice (iterator position, list& x, iterator i);
    // void splice (iterator position, list& x, iterator first, iterator last);
    // void reverse();
    // void merge (list& x);
    // template <class Compare>
    // void merge (list& x, Compare comp);
};

} // end of namespace ft scope

#endif