#ifndef LIST_HPP
#define LIST_HPP

#include <memory>

// list of int (1st param of template = int, and second param is set to default)

typedef struct s_list
{
    int content; // plutot mettre une ref / un pointeur -> voir comment faire
    struct s_list *prev;
    struct s_list *next;
} t_list;


t_list *ft_lst_new(const int &val);

class list
{
private:
    t_list *lst;
    size_t size;

    /* data */
public:

    // member types
    typedef int value_type; // 1st param of template

    // constructors
    explicit list ();
    explicit list (size_t n, const int val = int());
    template <class InputIterator>
    list (InputIterator first, InputIterator last);
    list (const list& x);

    // element access
    int &front();
    const int &front() const;
    int &back();
    const int &back() const;

    // modifiers
    void push_back(const int& val);
    bool empty() const;

};


#endif