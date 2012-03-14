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
#include <cassert>
#include <algorithm>

namespace numerical {
  namespace detail {

    template <class T>
    RowView<T>::RowView(typename RowView<T>::iterator begin,
                        const size_t cols)
      : _cols(cols), _data(begin)
    {}

    template <class T>
    void swap(RowView<T>& lhs, RowView<T>& rhs)
    {
      std::copy(cbegin(rhs), cend(rhs), begin(lhs));
    }

    template <class T>
    RowView<T>&
    RowView<T>::operator=(RowView other)
    {
      assert(_cols == other._cols);
      swap(*this, other);
      return *this;
    }

    template <class T>
    RowView<T>&
    RowView<T>::operator+=(const RowView<T>& rhs)
    {
      assert(_cols == rhs._cols);

      std::transform(cbegin(*this), cend(*this), cbegin(rhs), begin(*this),
                     [](const T& x, const T& y){return x + y;});

      return *this;
    }

    template <class T>
    RowView<T>&
    RowView<T>::operator-=(const RowView<T>& rhs)
    {
      assert(_cols == rhs._cols);

      std::transform(cbegin(*this), cend(*this), cbegin(rhs), begin(*this),
                     [](const T& x, const T& y){return x - y;});

      return *this;
    }

    template <class T>
    typename RowView<T>::value_type
    RowView<T>::operator()(const size_t index)
    {
      assert(index < _cols);
      return *(_data + index);
    }

    template <class T>
    const typename RowView<T>::value_type
    RowView<T>::operator()(const size_t index) const
    {
      return (*this)(index);
    }

    template <class T>
    size_t
    RowView<T>::cols() const
    {
      return _cols;
    }

    template <class T>
    T*
    RowView<T>::data() const
    {
      return _data;
    }

    template <class T>
    typename RowView<T>::iterator
    begin(const RowView<T>& x)
    {
      return x.data();
    }

    template <class T>
    typename RowView<T>::const_iterator
    cbegin(const RowView<T>& x)
    {
      return begin(x);
    }

    template <class T>
    typename RowView<T>::iterator
    end(const RowView<T>& x)
    {
      return x.data() + x.cols();
    }

    template <class T>
    typename RowView<T>::const_iterator
    cend(const RowView<T>& x)
    {
      return end(x);
    }

    template <class T>
    RowView<T>
    operator+(const RowView<T>& lhs, const RowView<T>& rhs)
    {
      RowView<T> result{lhs};

      return result += rhs;
    }

    template <class T>
    RowView<T>
    operator-(const RowView<T>& lhs, const RowView<T>& rhs)
    {
      RowView<T> result{lhs};

      return result -= rhs;
    }

    template <class T>
    ColumnView<T>::ColumnView(const T *const begin,
                              const size_t rows, const size_t cols)
      : _data(begin, rows, cols)
    {}

    template <class T>
    ColumnView<T>&
    ColumnView<T>::operator+=(const ColumnView& rhs)
    {
      std::transform(cbegin(*this), cend(*this), cbegin(rhs), begin(*this),
                     [](const T& x, const T& y) {return x + y;});
      return *this;
    }

    template <class T>
    ColumnView<T>&
    ColumnView<T>::operator-=(const ColumnView& rhs)
    {
      std::transform(cbegin(*this), cend(*this), cbegin(rhs), begin(*this),
                     [](const T& x, const T& y) {return x - y;});
      return *this;
    }

    template <class T>
    typename ColumnView<T>::value_type
    ColumnView<T>::operator()(const size_t index)
    {
      //assert(index < _rows);
      return *(_data + index);
    }

    template <class T>
    const typename ColumnView<T>::value_type
    ColumnView<T>::operator()(const size_t index) const
    {
      return (*this)(index);
    }

    template <class T>
    ColumnView<T>::ColumnIterator::ColumnIterator(const T * begin,
                                                  const size_t rows,
                                                  const size_t cols)
      : _cols(cols), _rows(rows), _data(begin)
    {}

    template <class T>
    typename ColumnView<T>::ColumnIterator&
    ColumnView<T>::ColumnIterator::operator++()
    {
      return _data += _cols;
    }

    template <class T>
    typename ColumnView<T>::ColumnIterator
    ColumnView<T>::ColumnIterator::operator++(int)
    {
      ColumnView<T>::ColumnIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    template <class T>
    typename ColumnView<T>::ColumnIterator&
    ColumnView<T>::ColumnIterator::operator--()
    {
      return _data -= _cols;
    }

    template <class T>
    typename ColumnView<T>::ColumnIterator
    ColumnView<T>::ColumnIterator::operator--(int)
    {
      ColumnView<T>::ColumnIterator tmp(*this);
      --(*this);
      return tmp;
    }

    template <class T>
    typename ColumnView<T>::ColumnIterator::reference
    ColumnView<T>::ColumnIterator::operator*() const
    {
      return *_data;
    }

    template <class T>
    typename ColumnView<T>::ColumnIterator::pointer
    ColumnView<T>::ColumnIterator::operator->() const
    {
      return _data;
    }

    template <class T>
    ColumnView<T>
    operator+(const ColumnView<T>& lhs, const ColumnView<T>& rhs)
    {
      ColumnView<T> result{lhs};

      return result += rhs;
    }

    template <class T>
    ColumnView<T>
    operator-(const ColumnView<T>& lhs, const ColumnView<T>& rhs)
    {
      ColumnView<T> result{lhs};

      return result -= rhs;
    }
  }
}
