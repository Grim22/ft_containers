
#ifndef QUEUE_HPP
# define QUEUE_HPP

#include <iostream>
#include <deque>

namespace ft
{

template<class T, class Container = std::deque<T> >
class queue
{
public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

private:
    container_type c;

public:
    explicit queue (const container_type& ctnr = container_type()): c(ctnr) {};
    ~queue() {};

    void push (const value_type& val)
    {
        c.push_back(val);
    }
    void pop()
    {
        c.pop_front();
    };
    size_type size() const
    {
        return c.size();
    }    
    bool empty() const
    {
        return c.empty();
    }
    value_type& front()
    {
        return c.front();
    };
    const value_type& front() const
    {
        return c.front();
    }
    value_type& back()
    {
        return c.back();
    };
    const value_type& back() const
    {
        return c.back();
    }

    template <class U, class Cont>
    friend bool operator== (const queue<U, Cont>& lhs, const queue<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator!= (const queue<U, Cont>& lhs, const queue<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator<= (const queue<U, Cont>& lhs, const queue<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator< (const queue<U, Cont>& lhs, const queue<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator>= (const queue<U, Cont>& lhs, const queue<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator> (const queue<U, Cont>& lhs, const queue<U, Cont>& rhs);


};

template <class T, class Container>
  bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
  {
      return (lhs.c == rhs.c);
  };
template <class T, class Container>
  bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
  {
      return (lhs.c != rhs.c);
  }
template <class T, class Container>
  bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
  {
      return (lhs.c < rhs.c);
  }
template <class T, class Container>
  bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
  {
      return (lhs.c <= rhs.c);
  }
template <class T, class Container>
  bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
  {
      return (lhs.c > rhs.c);
  }
template <class T, class Container>
  bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
  {
      return (lhs.c >= rhs.c);
  }
};

#endif