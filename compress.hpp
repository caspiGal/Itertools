#pragma once

namespace itertools
{

    template <typename C, typename B> // typname ~= class
    class compress
    {
    protected:
        C container;
        B b_container; // boolean container

    public:
        compress(C c, B b) : container(c), b_container(b) {}

        class iterator
        {
        protected:
            typename C::iterator _begin;
            typename C::iterator _end;
            typename B::iterator b_iter; //boolean iterator

        public:
            iterator(typename C::iterator first, typename C::iterator last, typename B::iterator b) : _begin(first), _end(last), b_iter(b)
            {
                while (_begin != _end && !(*b_iter))
                {
                    ++_begin;
                    ++b_iter;
                }
            }

            // Prefix: (++i)
            iterator &operator++()
            {
                ++_begin;
                ++b_iter;
                while (_begin != _end && !(*b_iter))
                {
                    ++_begin;
                    ++b_iter;
                }
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
                    this->b_it = other.b_it;
                }
                return *this;
            }
        };
        iterator begin()
        {
            return iterator(container.begin(), container.end(), b_container.begin());
        }

        iterator end()
        {
            return iterator(container.end(), container.end(), b_container.end());
        }
    };
} // namespace itertools