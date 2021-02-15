#ifndef REV_IT_HPP
# define REV_IT_HPP

#include <iterator>

namespace ft
{

template<class iterator>
class reverse_iterator
{
    public:
    typedef iterator iterator_type;
    typedef typename std::iterator_traits<iterator>::reference reference;
    typedef typename std::iterator_traits<iterator>::pointer pointer;
    typedef typename std::iterator_traits<iterator>::difference_type difference_type;
    // typedef iterator_category ;

    private:
    iterator_type base_it;

    public:
    reverse_iterator(): base_it(iterator_type())
    {};
    explicit reverse_iterator (iterator_type it): base_it(it) 
    {};
    template <class Iter>
    reverse_iterator (const reverse_iterator<Iter>& rev_it): base_it(rev_it.base()) 
    {};
    iterator_type base() const
    {
        return this->base_it;
    };
    reference operator*() const
    {
        iterator_type ret(this->base_it);
        ret--;
        return *ret;
    };
    // reverse_iterator operator+ (difference_type n) const
    reverse_iterator& operator++()
    {
        this->base_it--;
        return *this;
    }
    reverse_iterator  operator++(int)
    {
        reverse_iterator tmp(*this);
        ++(*this);
        return tmp;
    }
    reverse_iterator& operator--()
    {
        this->base_it++;
        return *this;
    }
    reverse_iterator  operator--(int)
    {
        reverse_iterator tmp(*this);
        --(*this);
        return tmp;
    }
    pointer operator->() const
    {
        return &(this->operator*());
    }

};

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() == rhs.base());
}
template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() != rhs.base());
}
template <class Iterator>
bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() < rhs.base());
}
template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() <= rhs.base());
}
template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() >= rhs.base());
}
template <class Iterator>
bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() > rhs.base());
}

};
#endif