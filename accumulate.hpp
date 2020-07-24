#pragma once
#include <functional>

using namespace std;

namespace itertools
{
    auto _sum = [](auto x, auto y) { return x + y; }; // lambda expression - will return the sum of x + y
                                                      //evaluated by return type expression at runtime.

    template <typename C, typename F = decltype(_sum)> //  F is a decltype related  types that depend on template parameters
    class accumulate
    {
    protected:
        C container;
        F function;

    public:
        // Constructor accumulate
        accumulate(C c, F f = _sum) : container(c), function(f) {}

        class iterator
        {
        protected:
            F function;
            typename C::iterator _begin;
            typename C::iterator _end;
            typename decay<decltype(*(container.begin()))>::type aggr; //aggregated value - smaller sums, added together and treated as an individual sum.

        public:
            iterator(typename C::iterator first, typename C::iterator last, F fun) : _begin(first), _end(last), function(fun)
            {
                if (_begin != _end)
                    aggr = *_begin;
            }

            // Prefix: (++i)  -  --> Using the Prefix operator (becouse we want to return the &)
            iterator &operator++()
            {
                ++_begin;
                if (_begin != _end)
                    aggr = function(aggr, *_begin);
                return *this;
            }
            // Postfix: (i++)
            iterator operator++(int)
            {
                iterator i = *this;
                ++(*i);
                return i;
            }
            bool operator==(const iterator &other) const
            {
                return (_begin == other._begin);
            }
            bool operator!=(const iterator &other) const
            {
                return (_begin != other._begin);
            }
            auto operator*() const
            {
                return aggr;
            }

            iterator &operator=(const iterator &other) // to compre
            {
                if (*this != other)
                {
                    this->_begin = other._begin;
                    this->_end = other._end;
                    this->aggr = other.aggr;
                    this->function = other.function;
                }
                return *this;
            }
        };
        iterator begin()
        {
            return iterator(container.begin(), container.end(), function);
        }

        iterator end()
        {
            return iterator(container.end(), container.end(), function);
        }
    };
} // namespace itertools