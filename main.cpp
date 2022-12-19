#include <iostream>
#include <filesystem>
#include <boost/mpl/int.hpp>
#include <boost/static_assert.hpp>

struct mypoint
{
    double x;
    double y;
};

double distance(const mypoint &a, const mypoint &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

namespace traits
{
    template <typename T, int D>
    struct access
    {
    };

    template <>
    struct access<mypoint, 0>
    {
        static double get(const mypoint &p)
        {
            return p.x;
        }
    };

    template <>
    struct access<mypoint, 1>
    {
        static double get(const mypoint &p)
        {
            return p.y;
        }
    };

    template <int D, typename T>
    double get(const T &p)
    {
        return access<T, D>::get(p);
    }

    // template <typename T>
    // double distance(const T &a, const T &b)
    // {
    //     double dx = get<0>(a) - get<0>(b);
    //     double dy = get<1>(a) - get<1>(b);
    //     return std::sqrt(dx * dx + dy * dy);
    // }

    template <typename T>
    struct dimension {};

    template <>
    struct dimension<mypoint> : boost::mpl::int_<2>
    {
    };

    template <typename P1, typename P2, int D>
    struct pythagoras
    {
        static double apply(const P1 &a, const P2 &b)
        {
            double d = get<D - 1>(a) - get<D - 1>(b);
            return d * d + pythagoras<P1, P2, D - 1>::apply(a, b);
        }
    };

    template <typename P1, typename P2>
    struct pythagoras<P1, P2, 0>
    {
        static double apply(const P1 &a, const P2 &b)
        {
            return 0;
        }
    };

    template <typename P1, typename P2>
    double distance(const P1 &a, const P2 &b)
    {
        BOOST_STATIC_ASSERT((dimension<P1>::value == dimension<P2>::value));
        return sqrt(pythagoras<P1, P2, dimension<P1>::value>::apply(a, b));
    }
}

template <typename T>
struct dimension : traits::dimension<T>
{
};

int main(int, char **)
{
    mypoint p1(100, 99), p2(50, 25);

    // std::cout << distance(p1, p2) << std::endl;
    std::cout << traits::distance(p1, p2) << std::endl;
}
