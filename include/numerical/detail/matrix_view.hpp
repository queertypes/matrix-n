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
#ifndef NUMERICAL_DETAIL_MATRIX_VIEW_HPP
#define NUMERICAL_DETAIL_MATRIX_VIEW_HPP

namespace numerical {
  namespace detail {
    template <class T,
              template <class,class> class ViewImpl,
              class Allocator = std::allocator<T>>
    class RowView {
    public:
      typedef T value_type;
      typedef T* iterator;
      typedef const T *const const_iterator;
      typedef ViewImpl<T, Allocator> view_implementation_type;
      typedef Allocator allocator_type;

      RowView();
      RowView(const RowView&);
      RowView(RowView&&);
      ~RowView();

      template <class _T, template <class,class> class _Impl, class _Alloc>
      void friend swap(RowView<_T, _Impl<_T, _Alloc>, _Alloc>&,
                       RowView<_T, _Impl<_T, _Alloc>, _Alloc>&);

      RowView& operator=(RowView);
      RowView& operator+=(const RowView&);
      RowView& operator-=(const RowView&);

      iterator begin() const;
      iterator end() const;
      const_iterator cbegin() const;
      const_iterator cend() const;

      T operator()(const size_t index);
      const T operator()(const size_t index) const;

      size_t cols() const;

    private:
      view_implementation_type _impl;
    };

    template <class T,
              template <class,class> class ViewImpl,
              class Allocator = std::allocator<T>>
    class ColumnView {
    public:
      typedef T value_type;
      typedef T* iterator;
      typedef const T *const const_iterator;
      typedef ViewImpl<T, Allocator> view_implementation_type;
      typedef Allocator allocator_type;

      ColumnView();
      ColumnView(const ColumnView&);
      ColumnView(ColumnView&&);
      ~ColumnView();

      template <class _T, template <class,class> class _Impl, class _Alloc>
      void friend swap(ColumnView<_T, _Impl<_T, _Alloc>, _Alloc>&,
                       ColumnView<_T, _Impl<_T, _Alloc>, _Alloc>&);

      ColumnView& operator=(ColumnView);
      ColumnView& operator+=(const ColumnView&);
      ColumnView& operator-=(const ColumnView&);

      iterator begin() const;
      iterator end() const;
      const_iterator cbegin() const;
      const_iterator cend() const;

      T operator()(const size_t index);
      const T operator()(const size_t index) const;

      size_t rows() const;

    private:
      //some means of iterating over data to reach all rows in given column

    private:
      view_implementation_type _impl;
    };

    template <class _T, template <class,class> _Impl, class _Alloc>
    RowView operator+(const RowView<_T, _Impl<_T, _Alloc>, _Alloc>& lhs,
                      const RowView<_T, _Impl<_T, _Alloc>, _Alloc>& rhs);

    template <class _T, template <class,class> _Impl, class _Alloc>
    RowView operator-(const RowView<_T, _Impl<_T, _Alloc>, _Alloc>& lhs,
                      const RowView<_T, _Impl<_T, _Alloc>, _Alloc>& rhs);

    template <class _T, template <class,class> _Impl, class _Alloc>
    ColumnView operator+(const ColumnView<_T, _Impl<_T, _Alloc>, _Alloc>& lhs,
                         const ColumnView<_T, _Impl<_T, _Alloc>, _Alloc>& rhs);

    template <class _T, template <class,class> _Impl, class _Alloc>
    ColumnView operator-(const ColumnView<_T, _Impl<_T, _Alloc>, _Alloc>& lhs,
                         const ColumnView<_T, _Impl<_T, _Alloc>, _Alloc>& rhs);

    template <class _T, template <class,class> _Impl, class _Alloc,
              template <class,class,class> _Matrix>
    _Matrix<_T,
            typename detail::MatrixImplementationTraits<_Impl<_T,
              _Alloc>>::matrix_implementation_type,
            _Alloc>
    operator*(const ColumnView<_T, _Impl<_T, _Alloc>, _Alloc>& lhs,
              const RowView<_T, _Impl<_T, _Alloc>, _Alloc>& rhs);

    template <class _T, template <class,class> _Impl, class _Alloc,
              template <class,class,class> _Matrix>
    _Matrix<_T,
            typename detail::MatrixImplementationTraits<_Impl<_T,
              _Alloc>>::matrix_implementation_type,
            _Alloc>
    operator*(const RowView<_T, _Impl<_T, _Alloc>, _Alloc>& lhs,
              const ColumnView<_T, _Impl<_T, _Alloc>, _Alloc>& rhs);
  }
}

#include <implementation/detail/matrix_view.cpp>

#endif
