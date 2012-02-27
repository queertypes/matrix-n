 /*
    This file is part of Fast Slater.

    Fast Slater is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Fast Slater is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Fast Slater.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <algorithm>
#include <cassert>

namespace numerical {
  namespace impl {

    template <class T, class _Alloc>
    explicit SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(const size_t n)
        : _rows(n), _cols(n),
          _data(_allocator.allocate(n*n))
    {}

    templae <class T, class _Alloc>
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(const size_t rows,
                                          const size_t cols)
        : _rows(rows), _cols(cols),
          _data(_allocator.allocate(rows*cols))
    {}

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
        : _rows(other._rows), _cols(other._cols),
          _data(_allocator.allocate(other._rows * other._cols))
    {
      std::copy(other._data,
                other._data + sizeof(T) * other._rows * other._cols,
                _data);
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
    SerialMatrixImplementation<T,
      _Alloc>::SerialMatrixImplementation(SerialMatrixImplementation<T,
        _Alloc>&& other)
        : _rows(0), _cols(0),
          _data(nullptr)
    {
      swap(*this, other);
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>&
    SerialMatrixImplementation<T,
      _Alloc>::operator=(SerialMatrixImplementation<T, _Alloc>&& other)
    {
      std::move(_rows, other._rows);
      std::move(_cols, other._cols);
      std::move(_data, other._data);
    }

    template <class T, class _Alloc>
    SerialMatrixImplementation<T, _Alloc>::~SerialMatrixImplementation<T,
      _Alloc>()
    {
      _allocator.deallocate(_data, sizeof(T) *  _rows * _cols);
    }

    template <class T, class _Alloc>
    T&
    SerialMatrixImplementation<T,
      _Alloc>::operator()(const size_t row, const size_t col)
    {
      return _data[_cols * row + col];
    }

    template <class T, class _Alloc>
    T&
    SerialMatrixImplementation<T,
      _Alloc>::operator()(const size_t row, const size_t col) const
    {
      return _data[_cols * row + col];
    }
  }
}
