#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>

template <class Key_type, class Value_type>
struct node
{
    node* left;
    node* right;
    Key_type key;
    Value_type value;
    node(): left(NULL), right(NULL), key(Key_type()), value(Value_type())
    {};
    node(Key_type key, Value_type val):left(NULL), right(NULL), key(key), value(val)
    {};
};

template <class key_type, class value_type>
void insert(node<key_type, value_type> *&root, key_type key, value_type val)
{
    if (root == nullptr)
    {
        root = new node<key_type, value_type>(key, val);
        return;
    }
    if (root->key == key)
        return ;
    else if (root->key > key)
        insert(root->left, key, val);
    else
        insert(root->right, key, val);
}

// template <class key_type, class value_type>
// node<key_type, value_type> search(node<key_type, value_type> root, key_type key, value_type val)
// {


#endif