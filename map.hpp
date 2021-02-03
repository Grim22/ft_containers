#ifndef MAP_HPP
# define MAP_HPP

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
class map_base
{
    typedef node<key_type, value_type> node_type;
    public:
    node_type *base;

    public:
    map_base(): base(nullptr) {};
    map_base(key_type key, value_type val): base(new node_type(key, val)) {};
    void insert(key_type key, value_type val)
    {
        if (this->base == NULL)
            this->base = new node_type(key, val);
        else
            insert(this->base, key, val);
    }

    private:
    void insert(node_type *node, key_type key, value_type val)
    {
        if (node == NULL)
        {
            node = new node_type(key, val);
            return;
        }
        if (node->key == key)
            return ;
        else if (node->key > key)
            insert(node->left, key, val);
        else
            insert(node->right, key, val);
    }
};

#endif