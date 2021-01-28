#ifndef ENABLE_HPP
#define ENABLE_HPP

namespace ft
{

template <bool b, typename T>
struct enable_if
{

};

template <typename T>
struct enable_if<true, T>
{
    typedef T type;
};


// define our is_integral

template <typename T>
struct is_integral
{
    static const bool val = false;
};

template <>
struct is_integral<int>
{
    static const bool val = true;
};

};

#endif