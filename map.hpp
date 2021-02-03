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

template <class key_type, class value_type>
node<key_type, value_type> *search(node<key_type, value_type> *root, key_type key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

template <class key_type, class value_type>
node<key_type, value_type> *search_min(node<key_type, value_type> *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

template <class key_type, class value_type>
node<key_type, value_type> *search_max(node<key_type, value_type> *root)
{
    while (root->right != NULL)
        root = root->right;
    return root;
}

template <class key_type, class value_type>
void delete_node(node<key_type, value_type> *&root, key_type key)
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
        // case #2: root has 1 child: replace root by its child, then delete child
        if (root->right && root->left == NULL)
        {
            root->key = root->right->key;
            root->value = root->right->value;
            delete_node(root->right, root->key);
            return ;
        }
        if (root->left && root->right == NULL)
        {
            root->key = root->left->key;
            root->value = root->left->value;
            delete_node(root->left, root->key);
            return ;
        }
        // case 3: root has 2 childs
        else
        {
            // node<key_type, value_type> *tmp = search_min(root->right);
            node<key_type, value_type> *tmp = search_max(root->left);
            root->key = tmp->key;
            root->value = tmp->value;
            // delete_node(root->right, tmp->key);
            delete_node(root->left, tmp->key);
            return ;
        }
    }
    if (root->key > key)
        delete_node(root->left, key);
    else
        delete_node(root->right, key);
}

template <class key_type, class value_type>
void print_in_order(node<key_type, value_type> *&root)
{
    if (root->left)
        print_in_order(root->left);
    std::cout << root->key << std::endl;
    if (root->right)
        print_in_order(root->right);
}


#endif