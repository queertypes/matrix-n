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
namespace numerical {

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>::Matrix()
    : _impl()
  {
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>::Matrix(const size_t n)
    : _impl(n)
  {
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>::Matrix(const size_t rows,
                                   const size_t cols)
    : _impl(rows, cols)
  {
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>::Matrix(const Matrix<T, _Impl, _Alloc>& other)
    : _impl(other._impl)
  {
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>::Matrix(Matrix<T, _Impl, _Alloc>&& other)
    : _impl(std::move(other._impl))
  {
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  void swap(Matrix<T, _Impl, _Alloc>& lhs,
            Matrix<T, _Impl, _Alloc>& rhs)
  {
    std::swap(lhs._impl, rhs._impl);
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>&
  Matrix<T, _Impl, _Alloc>::operator=(Matrix<T, _Impl, _Alloc> other)
  {
    swap(*this, other);
    return *this;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>::~Matrix()
  {
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  T&
  Matrix<T, _Impl, _Alloc>::operator()(const size_t row,
                                       const size_t col) const
  {
    return _impl(row, col);
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  T&
  Matrix<T, _Impl, _Alloc>::operator()(const size_t row,
                                       const size_t col)
  {
    return _impl(row, col);
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>&
  Matrix<T, _Impl, _Alloc>::operator+=(const Matrix<T, _Impl, _Alloc>& other)
  {
    _impl += other._impl;
    return *this;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>&
  Matrix<T, _Impl, _Alloc>::operator-=(const Matrix<T, _Impl, _Alloc>& other)
  {
    _impl -= other._impl;
    return *this;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>&
  Matrix<T, _Impl, _Alloc>::operator*=(const Matrix<T, _Impl, _Alloc>& other)
  {
    _impl *= other._impl;
    return *this;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>&
  Matrix<T, _Impl, _Alloc>::operator+=(const T& scalar)
  {
    _impl += scalar;
    return *this;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>&
  Matrix<T, _Impl, _Alloc>::operator-=(const T& scalar)
  {
    _impl -= scalar;
    return *this;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>&
  Matrix<T, _Impl, _Alloc>::operator*=(const T& scalar)
  {
    _impl *= scalar;
    return *this;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>&
  Matrix<T, _Impl, _Alloc>::operator/=(const T& scalar)
  {
    _impl /= scalar;
    return *this;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  T* Matrix<T, _Impl, _Alloc>::data() const
  {
    return _impl.data();
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  size_t Matrix<T, _Impl, _Alloc>::rows() const
  {
    return _impl.rows();
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  size_t Matrix<T, _Impl, _Alloc>::cols() const
  {
    return _impl.cols();
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  constexpr _Alloc
  Matrix<T, _Impl, _Alloc>::get_allocator() const
  {
    return _impl.get_allocator();
  }

  template <class T,
            template <class, class> class _Impl,
            class _Alloc>
  detail::RowView<T>
  Matrix<T, _Impl, _Alloc>::row(const size_t index) const
  {
    return detail::RowView<T>(begin(_impl) + (index * _impl.cols()),
                              _impl.cols());
  }

  template <class T,
            template <class, class> class _Impl,
            class _Alloc>
  detail::ColumnView<T>
  Matrix<T, _Impl, _Alloc>::col(const size_t index) const
  {
    return detail::ColumnView<T>(begin(_impl) + index,
                                 _impl.rows(), _impl.cols());
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  Matrix<T, _Impl, _Alloc>::operator-()
  {
    Matrix<T, _Impl, _Alloc> result;
    result._impl = -_impl;
    return result;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  typename Matrix<T, _Impl, _Alloc>::iterator
  begin(const Matrix<T, _Impl, _Alloc>& m)
  {
    return m.data();
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  typename Matrix<T, _Impl, _Alloc>::const_iterator
  cbegin(const Matrix<T, _Impl, _Alloc>& m)
  {
    return m.data();
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  typename Matrix<T, _Impl, _Alloc>::iterator
  end(const Matrix<T, _Impl, _Alloc>& m)
  {
    return m.data() + m.rows() * m.cols();
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  typename Matrix<T, _Impl, _Alloc>::const_iterator
  cend(const Matrix<T, _Impl, _Alloc>& m)
  {
    return m.data() + m.rows() * m.cols();
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator+(const Matrix<T, _Impl, _Alloc>& lhs,
            const Matrix<T, _Impl, _Alloc>& rhs)
  {
    Matrix<T, _Impl, _Alloc> result(lhs);
    return result += rhs;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator-(const Matrix<T, _Impl, _Alloc>& lhs,
            const Matrix<T, _Impl, _Alloc>& rhs)
  {
    Matrix<T, _Impl, _Alloc> result(lhs);
    return result -= rhs;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator*(const Matrix<T, _Impl, _Alloc>& lhs,
            const Matrix<T, _Impl, _Alloc>& rhs)
  {
    Matrix<T, _Impl, _Alloc> result(lhs);
    return result *= rhs;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator+(const Matrix<T, _Impl, _Alloc>& lhs,
            const T& scalar)
  {
    Matrix<T, _Impl, _Alloc> result(lhs);
    return result += scalar;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator-(const Matrix<T, _Impl, _Alloc>& lhs,
            const T& scalar)
  {
    Matrix<T, _Impl, _Alloc> result(lhs);
    return result -= scalar;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator*(const Matrix<T, _Impl, _Alloc>& lhs,
            const T& scalar)
  {
    Matrix<T, _Impl, _Alloc> result(lhs);
    return result *= scalar;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator/(const Matrix<T, _Impl, _Alloc>& lhs,
            const T& scalar)
  {
    Matrix<T, _Impl, _Alloc> result(lhs);
    return result /= scalar;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator+(const T& scalar,
            const Matrix<T, _Impl, _Alloc>& rhs)
  {
    Matrix<T, _Impl, _Alloc> result(rhs);
    return result += scalar;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator-(const T& scalar,
            const Matrix<T, _Impl, _Alloc>& rhs)
  {
    Matrix<T, _Impl, _Alloc> result(rhs);
    return (-result) += scalar;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  Matrix<T, _Impl, _Alloc>
  operator*(const T& scalar,
            const Matrix<T, _Impl, _Alloc>& rhs)
  {
    Matrix<T, _Impl, _Alloc> result(rhs);
    return result *= scalar;
  }

  template <class T,
            template <class,class> class _Impl,
            class _Alloc>
  bool
  operator==(const Matrix<T, _Impl, _Alloc>& lhs,
             const Matrix<T, _Impl, _Alloc>& rhs)
  {
    return lhs._impl == rhs._impl;
  }
}
