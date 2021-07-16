
#ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
#include <deque>

namespace ft
{

template<class T, class Container = std::deque<T> >
class stack
{
public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

private:
    container_type c;

public:
    explicit stack (const container_type& ctnr = container_type()): c(ctnr) {};
    ~stack() {};

    void push (const value_type& val)
    {
        c.push_back(val);
    }
    void pop()
    {
        c.pop_back();
    };
    size_type size() const
    {
        return c.size();
    }    
    bool empty() const
    {
        return c.empty();
    }
    value_type& top()
    {
        return c.back();
    };
    const value_type& top() const
    {
        return c.back();
    }

    template <class U, class Cont>
    friend bool operator== (const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator!= (const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator<= (const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator< (const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator>= (const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
    template <class U, class Cont>
    friend bool operator> (const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);


};

template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
      return (lhs.c == rhs.c);
  };
template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
      return (lhs.c != rhs.c);
  }
template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
      return (lhs.c < rhs.c);
  }
template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
      return (lhs.c <= rhs.c);
  }
template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
      return (lhs.c > rhs.c);
  }
template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
      return (lhs.c >= rhs.c);
  }
};

#endif