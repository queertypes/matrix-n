/*
  Matrix N - generic matrix library offering compile-time implementation choices
  Copyright (C) 2016 Allele Dev

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
#ifndef MATRIX_N_NUMERICAL_DETAIL_MATRIX_VIEW_HPP
#define MATRIX_N_NUMERICAL_DETAIL_MATRIX_VIEW_HPP
#include <iterator>
#include <cstddef>

namespace numerical {
  namespace detail {
    template <class T>
    class RowView {
    public:
      typedef T value_type;
      typedef T* pointer;

      typedef T* iterator;
      typedef const T * const_iterator;
      typedef std::random_access_iterator_tag iterator_category;

      RowView() = default;
      ~RowView() = default;
      RowView(const RowView&) = default;
      RowView(RowView&&) =  default;

      RowView(pointer begin, const size_t cols);

      RowView& operator=(RowView);
      RowView& operator+=(const RowView&);
      RowView& operator-=(const RowView&);

      value_type operator()(const size_t index);
      const value_type operator()(const size_t index) const;

      pointer data() const;
      size_t cols() const;

    private:
      size_t _cols;
      pointer _data;
    };

    template <class T>
    typename RowView<T>::iterator
    begin(const RowView<T>&);

    template <class T>
    typename RowView<T>::const_iterator
    cbegin(const RowView<T>&);

    template <class T>
    typename RowView<T>::iterator
    end(const RowView<T>&);

    template <class T>
    typename RowView<T>::const_iterator
    cend(const RowView<T>&);

    template <class T>
    RowView<T> operator+(const RowView<T>&, const RowView<T>&);

    template <class T>
    RowView<T> operator-(const RowView<T>&, const RowView<T>&);

    template <class T>
    struct ColumnIterator {
      typedef T value_type;
      typedef T* pointer;
      typedef T& reference;
      typedef const T& const_reference;

      typedef std::random_access_iterator_tag iterator_category;
      typedef ptrdiff_t difference_type;
      typedef size_t size_type;

      ColumnIterator() = default;
      ~ColumnIterator() = default;

      ColumnIterator(const ColumnIterator&) = default;
      ColumnIterator(ColumnIterator&&) = default;
      ColumnIterator& operator=(const ColumnIterator&) = default;

      ColumnIterator(T *begin,
                     const size_t rows, const size_t cols);

      ColumnIterator& operator++();
      ColumnIterator operator++(int);
      ColumnIterator& operator--();
      ColumnIterator operator--(int);

      ColumnIterator& operator+=(const difference_type offset);
      ColumnIterator& operator-=(const difference_type offset);

      reference operator[](const difference_type offset);
      const_reference operator[](const difference_type offset) const;

      reference operator*() const;
      pointer operator->() const;

      size_t _cols, _rows;
      pointer _data;
    };

    template <class T>
    ColumnIterator<T> operator+(const ColumnIterator<T>& lhs,
                                const ptrdiff_t offset);

    template <class T>
    ColumnIterator<T> operator-(const ColumnIterator<T>& lhs,
                                const ptrdiff_t offset);

    template <class T>
    ColumnIterator<T> operator+(const ptrdiff_t offset,
                                const ColumnIterator<T>& lhs);

    template <class T>
    ColumnIterator<T> operator-(const ptrdiff_t offset,
                                const ColumnIterator<T>& lhs);

    template <class T>
    ptrdiff_t operator-(const ColumnIterator<T>& lhs,
                        const ColumnIterator<T>& rhs);

    template <class T>
    bool operator==(const ColumnIterator<T>& lhs,
                    const ColumnIterator<T>& rhs);

    template <class T>
    bool operator!=(const ColumnIterator<T>& lhs,
                    const ColumnIterator<T>& rhs);

    template <class T>
    bool operator<(const ColumnIterator<T>& lhs,
                   const ColumnIterator<T>& rhs);

    template <class T>
    bool operator>(const ColumnIterator<T>& lhs,
                   const ColumnIterator<T>& rhs);

    template <class T>
    bool operator<=(const ColumnIterator<T>& lhs,
                    const ColumnIterator<T>& rhs);

    template <class T>
    bool operator>=(const ColumnIterator<T>& lhs,
                    const ColumnIterator<T>& rhs);

    template <class T>
    class ColumnView {
    public:
      typedef T value_type;

      typedef ColumnIterator<T> iterator;
      typedef const ColumnIterator<T> const_iterator;

      ColumnView() = default;
      ColumnView(const ColumnView&) = default;
      ColumnView(ColumnView&&) = default;
      ~ColumnView() = default;

      ColumnView(T* begin,
                 const size_t rows, const size_t cols);
      ColumnView& operator=(const ColumnView&);

      ColumnView& operator+=(const ColumnView&);
      ColumnView& operator-=(const ColumnView&);

      T operator()(const size_t index);
      const T operator()(const size_t index) const;

      iterator data() const;
      size_t cols() const;
      size_t rows() const;

    private:
      iterator _data;
    };

    template <class T>
    typename ColumnView<T>::iterator
    begin(const ColumnView<T>&);

    template <class T>
    typename ColumnView<T>::const_iterator
    cbegin(const ColumnView<T>&);

    template <class T>
    typename ColumnView<T>::iterator
    end(const ColumnView<T>&);

    template <class T>
    typename ColumnView<T>::const_iterator
    cend(const ColumnView<T>&);

    template <class T>
    ColumnView<T> operator+(const ColumnView<T>&, const ColumnView<T>&);

    template <class T>
    ColumnView<T> operator-(const ColumnView<T>&, const ColumnView<T>&);
  }
}

#include <matrix_n/implementation/detail/matrix_view.cpp>

#endif
