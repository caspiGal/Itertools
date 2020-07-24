#pragma once
#include <iostream>
using namespace std;

namespace itertools
{
    class range
    {
    protected:
        int _begin, _end;

    public:
        //Constructor range:
        range(int first, int last) : _begin(first), _end(last) {} //  first - begin , last - end

        class iterator
        {
            int _cur; // Current

        public:
            //Constructor iterator:
            iterator(int c = 0) : _cur(c) {}

            //  Prefix: (++i)  using this for the range(5,9) - > 5 , 6 , 7 , 8
            iterator &operator++()
            {
                _cur += 1;
                return *this;
            }

            // Postfix: (i++)
            const iterator operator++(int)
            {
                iterator temp = *this;
                _cur += 1;
                return temp;
            }
            //    // comparison operator
            bool operator==(const iterator &other) const
            {
                return _cur == other._cur;
            }

            bool operator!=(const iterator &other) const
            {
                return _cur != other._cur;
            }

            int operator*() // (Asterisk operator) * (Onri - access to the object that the iterator points to)
            {
                return _cur;
            }
            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->_cur = other._cur;
                }
                return *this;
            }
        };

        iterator begin() const
        {
            return iterator(_begin);
        }

        iterator end() const
        {
            return iterator(_end);
        }
    };

} // namespace itertools
