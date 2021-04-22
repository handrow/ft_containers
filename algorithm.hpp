#pragma once

namespace ft
{
    template<class T>
    struct less
    {
        bool operator()(const T& x, const T& y) const
        {
            return x < y;
        }
    };

    template<class T>
    const T& max(const T& a, const T& b)
    {
        return (a > b) ? a : b;
    }

}
