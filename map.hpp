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

template <class Key_type, class Value_type>
struct map_node
{
    map_node* left;
    map_node* right;
    Key_type key;
    Value_type value;
    map_node(): left(NULL), right(NULL), key(Key_type()), value(Value_type())
    {};
    map_node(Key_type key, Value_type val):left(NULL), right(NULL), key(key), value(val)
    {};
};

template <class key_type, class value_type>
void insert(map_node<key_type, value_type> *&root, key_type key, value_type val)
{
    if (root == nullptr)
    {
        root = new map_node<key_type, value_type>(key, val);
        return;
    }
    if (root->key == key)
        return ;
    else if (root->key > key)
        insert(root->left, key, val);
    else
        insert(root->right, key, val);
}

template <class key_type, class value_type>
map_node<key_type, value_type> *search(map_node<key_type, value_type> *root, key_type key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

template <class key_type, class value_type>
map_node<key_type, value_type> *search_min(map_node<key_type, value_type> *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

template <class key_type, class value_type>
map_node<key_type, value_type> *search_max(map_node<key_type, value_type> *root)
{
    while (root->right != NULL)
        root = root->right;
    return root;
}

template <class key_type, class value_type>
void delete_map_node(map_node<key_type, value_type> *&root, key_type key)
{
    // std::cout << "key: " << root->key;
    // std::cout << "looking for: " << key << std::endl;
    if (root->key == key)
    {
        // delete root
        // return
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
            // // 1 -relink child to root parent
            // // 1 - a - get parent
            // map_node<key_type, value_type> *parent = get_parent(root->key);
            // // 1 - b - link parent to child (on the left or on the right)
            // if (root == parent->right)
            //     parent->right = root->right
            // else
            //     parent->left = root->right
            // // delete root
            // delete root;
            // return ;
            root->key = root->right->key;
            root->value = root->right->value;
            delete_map_node(root->right, root->key);
            return ;
        }
        if (root->left && root->right == NULL)
        {
            root->key = root->left->key;
            root->value = root->left->value;
            delete_map_node(root->left, root->key);
            return ;
        }
        // case 3: root has 2 childs
        else
        {
            // map_node<key_type, value_type> *tmp = search_min(root->right);
            map_node<key_type, value_type> *tmp = search_max(root->left);
            root->key = tmp->key;
            root->value = tmp->value;
            // delete_map_node(root->right, tmp->key);
            delete_map_node(root->left, tmp->key);
            return ;
        }
    }
    if (root->key > key)
        delete_map_node(root->left, key);
    else
        delete_map_node(root->right, key);
}

template <class key_type, class value_type>
void print_in_order(map_node<key_type, value_type> *&root)
{
    if (root->left)
        print_in_order(root->left);
    std::cout << root->key << std::endl;
    if (root->right)
        print_in_order(root->right);
}

// template <class key_type, class value_type>
// void delete_in_order(map_node<key_type, value_type> *&root)
// {
//     if (root->left)
//         delete_in_order(root->left);
//     delete root;
//     if (root->right)
//         delete_in_order(root->right);
// }


template<class key, class T>
class map
{
public:
    // member types
    typedef key key_type; // 1st param of template
    typedef T mapped_type; // 2st param of template
    typedef std::pair<const key, T> value_type; // 1st param of template
    typedef unsigned long size_type;

private:
    typedef map_node<key, T> node_type;
    node_type *root;

public:
    
    // typedef iterator<T> iterator;
    // typedef const_iterator<T> const_iterator;
    // typedef std::reverse_iterator<iterator> reverse_iterator;    
    // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;    

public:
    // constructors & destructor
    explicit map (): root(NULL) {};
    template <class InputIterator> 
    map(InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            insert(this->root, first->first, first->second);
            first++;
        }
    };
    map (const map& x);
    ~map() 
    {
        // delete_in_order(this->root);
    };
    map& operator= (const map& x);

    void print(void)
    {
        print_in_order(this->root);
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