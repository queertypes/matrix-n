/*
  Matrix N - generic matrix library offering compile-time implementation choices
  Copyright (C) 2012 Alejandro Cabrera

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <algorithm>
#include <cassert>

namespace numerical {
  namespace impl {

    template <class T, class _Alloc>
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation()
        : _allocator(),
          _rows(0), _cols(0),
          _data(nullptr)
    {}

    template <class T, class _Alloc>
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(const size_t n)
        : _allocator(),
          _rows(n), _cols(n),
          _data(_allocator.allocate(n*n))
    {
      std::fill(begin(*this), end(*this), T());
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(const size_t rows,
                                          const size_t cols)
        : _allocator(),
          _rows(rows), _cols(cols),
          _data(_allocator.allocate(rows*cols))
    {
      std::fill(begin(*this), end(*this), T());
    }

    template <class T, class _Alloc>
    void swap(SerialMatrixImplementation<T, _Alloc>& lhs,
              SerialMatrixImplementation<T, _Alloc>& rhs)
    {
      using std::swap;

      swap(lhs._rows, rhs._rows);
      swap(lhs._cols, rhs._cols);
      swap(lhs._data, rhs._data);
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(const SerialMatrixImplementation<T,
        _Alloc>& other)
        : _allocator(),
          _rows(other._rows), _cols(other._cols),
          _data(_allocator.allocate(_rows * _cols))
    {
      std::copy(cbegin(other), cend(other), begin(*this));
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T,
      _Alloc>::operator=(SerialMatrixImplementation<T, _Alloc> other)
    {
      swap(*this, other);

      return *this;
    }

    template <class T, class _Alloc>
    template <class InputIterator>
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(const InputIterator _begin,
                                          const InputIterator _end,
                                          const size_t n)
      : _allocator(),
        _rows(n), _cols(n),
        _data(_allocator.allocate(n * n))
    {
      std::copy(_begin, _end, begin(*this));
    }

    template <class T, class _Alloc>
    template <class InputIterator>
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(const InputIterator _begin,
                                          const InputIterator _end,
                                          const size_t rows,
                                          const size_t cols)
      : _allocator(),
        _rows(rows), _cols(cols),
        _data(_allocator.allocate(rows * cols))
    {
      std::copy(_begin, _end, begin(*this));
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(SerialMatrixImplementation<T,
        _Alloc>&& other)
        : _allocator(),
          _rows(0), _cols(0),
          _data(nullptr)
    {
      swap(*this, other);
    }

    template <class T, class _Alloc>
    T&
    SerialMatrixImplementation<T,
      _Alloc>::operator()(const size_t row, const size_t col)
    {
      return (_data.get())[_cols * row + col];
    }

    template <class T, class _Alloc>
    T&
    SerialMatrixImplementation<T,
      _Alloc>::operator()(const size_t row, const size_t col) const
    {
      return (_data.get())[_cols * row + col];
    }

    template <class T, class _Alloc>
    size_t
    SerialMatrixImplementation<T, _Alloc>::rows() const
    {
      return _rows;
    }

    template <class T, class _Alloc>
    size_t
    SerialMatrixImplementation<T, _Alloc>::cols() const
    {
      return _cols;
    }

    template <class T, class _Alloc>
    T*
    SerialMatrixImplementation<T, _Alloc>::data() const
    {
      return _data.get();
    }

    template <class T,
              class _Alloc>
    typename SerialMatrixImplementation<T, _Alloc>::iterator
    begin(const SerialMatrixImplementation<T, _Alloc>& m)
    {
      return m.data();
    }

    template <class T,
              class _Alloc>
    typename SerialMatrixImplementation<T, _Alloc>::const_iterator
    cbegin(const SerialMatrixImplementation<T, _Alloc>& m)
    {
      return m.data();
    }

    template <class T,
              class _Alloc>
    typename SerialMatrixImplementation<T, _Alloc>::iterator
    end(const SerialMatrixImplementation<T, _Alloc>& m)
    {
      return m.data() + m.rows() * m.cols();
    }

    template <class T,
              class _Alloc>
    typename SerialMatrixImplementation<T, _Alloc>::const_iterator
    cend(const SerialMatrixImplementation<T, _Alloc>& m)
    {
      return m.data() + m.rows() * m.cols();
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    SerialMatrixImplementation<T, _Alloc>::operator-()
    {
      SerialMatrixImplementation<T, _Alloc> result{*this};

      std::transform(cbegin(*this), cend(*this), begin(result),
                     [](const T& x) {return -x;});

      return result;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T,
      _Alloc>::operator+=(const SerialMatrixImplementation<T, _Alloc>& rhs)
    {
      assert(rhs.rows() == rows());
      assert(rhs.cols() == cols());

      std::transform(cbegin(*this), cend(*this), cbegin(rhs), begin(*this),
                     [](const T& x, const T& y) {return x + y;});

      return *this;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T,
      _Alloc>::operator-=(const SerialMatrixImplementation<T, _Alloc>& rhs)
    {
      assert(rhs.rows() == rows());
      assert(rhs.cols() == cols());

      std::transform(cbegin(*this), cend(*this), cbegin(rhs), begin(*this),
                     [](const T& x, const T& y) {return x - y;});

      return *this;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T,
      _Alloc>::operator*=(const SerialMatrixImplementation<T, _Alloc>& rhs)
    {
      assert(cols() == rhs.rows());

      SerialMatrixImplementation<T, _Alloc> result(rows(), rhs.cols());

      for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < rhs.cols(); ++j) {
          for (size_t k = 0; k < cols(); ++k) {
            result(i,j) += (*this)(i,k) * rhs(k,j);
          }
        }
      }

      *this = std::move(result);

      return *this;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T, _Alloc>::operator+=(const T& scalar)
    {
      std::transform(cbegin(*this), cend(*this), begin(*this),
                     [&scalar](const int x) {return x + scalar;} );

      return *this;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T, _Alloc>::operator-=(const T& scalar)
    {
      std::transform(cbegin(*this), cend(*this), begin(*this),
                     [&scalar](const int x) {return x - scalar;} );

      return *this;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T, _Alloc>::operator*=(const T& scalar)
    {
      std::transform(cbegin(*this), cend(*this), begin(*this),
                     [&scalar](const int x) {return x * scalar;} );

      return *this;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T, _Alloc>::operator/=(const T& scalar)
    {
      assert(scalar != 0);
      std::transform(cbegin(*this), cend(*this), begin(*this),
                     [&scalar](const int x) {return x / scalar;} );

      return *this;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator+(const SerialMatrixImplementation<T, _Alloc>& lhs,
              const SerialMatrixImplementation<T, _Alloc>& rhs)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return std::move(result += rhs);
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator-(const SerialMatrixImplementation<T, _Alloc>& lhs,
              const SerialMatrixImplementation<T, _Alloc>& rhs)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return result -= rhs;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator*(const SerialMatrixImplementation<T, _Alloc>& lhs,
              const SerialMatrixImplementation<T, _Alloc>& rhs)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return result *= rhs;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator+(const SerialMatrixImplementation<T, _Alloc>& lhs,
              const T& scalar)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return result += scalar;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator-(const SerialMatrixImplementation<T, _Alloc>& lhs,
              const T& scalar)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return result -= scalar;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator*(const SerialMatrixImplementation<T, _Alloc>& lhs,
              const T& scalar)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return result *= scalar;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator/(const SerialMatrixImplementation<T, _Alloc>& lhs,
              const T& scalar)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return result /= scalar;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator+(const T& scalar,
              const SerialMatrixImplementation<T, _Alloc>& lhs)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return result += scalar;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator-(const T& scalar,
              const SerialMatrixImplementation<T, _Alloc>& lhs)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return (-result) += scalar;
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator*(const T& scalar,
              const SerialMatrixImplementation<T, _Alloc>& lhs)
    {
      SerialMatrixImplementation<T, _Alloc> result(lhs);

      return result *= scalar;
    }

    template <class T, class _Alloc>
    bool
    operator==(const SerialMatrixImplementation<T, _Alloc>& lhs,
               const SerialMatrixImplementation<T, _Alloc>& rhs)
    {
      if (lhs.rows() != rhs.rows()) return false;
      if (lhs.cols() != rhs.cols()) return false;

      if (!std::equal(cbegin(lhs), cend(lhs), cbegin(rhs)) ) {
        return false;
      }

      return true;
    }
  }
}
