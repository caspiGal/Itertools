#pragma once

namespace itertools
{

    template <typename F, typename C>
    class filterfalse
    {
    protected:
        F filter;
        C container;

    public:
        // Constroctor filterfalse
        filterfalse(F f, C c) : filter(f), container(c) {}

        class iterator
        {
        protected:
            F filter;
            typename C::iterator _begin;
            typename C::iterator _end;

        public:
            iterator(F fil, typename C::iterator first, typename C::iterator last) : filter(fil), _begin(first), _end(last)
            {
                while (_begin != _end && filter(*_begin))
                    ++_begin;
            }

            // Prefix: (++i) -- > Using the Prefix operator (becouse we want to return the &)
            iterator &operator++()
            {
                ++_begin;
                while (_begin != _end && filter(*_begin))
                    ++_begin;
                return *this;
            }
            // Postfix: (i++) 
            iterator operator++(int)
            {
                iterator i = *this;
                ++(*this);
                return i;
            }
            bool operator==(const iterator &other) const
            {
                return _begin == other._begin;
            }
            bool operator!=(const iterator &other) const
            {
                return _begin != other._begin;
            }
            auto operator*()
            {
                return *_begin;
            }

            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->_begin = other._begin;
                    this->_end = other._end;
                    this->filter = other.filter;
                }
                return *this;
            }
        };
        iterator begin()
        {
            return iterator(filter, container.begin(), container.end());
        }

        iterator end()
        {
            return iterator(filter, container.end(), container.end());
        }
    };
} // namespace itertools