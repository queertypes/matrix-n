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
namespace numerical {

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>::Matrix()
    : _impl()
  {
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>::Matrix(const size_t n)
    : _impl(n)
  {
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>::Matrix(const size_t rows,
                                   const size_t cols)
    : _impl(rows, cols)
  {
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>::Matrix(const Matrix<T, _Alloc, _Impl>& other)
    : _impl(other._impl)
  {
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>::Matrix(Matrix<T, _Alloc, _Impl>&& other)
    : _impl(std::move(other._impl))
  {
  }

  template <class T,
            class _Alloc,
            class _Impl>
  void swap(Matrix<T, _Alloc, _Impl>& lhs,
            Matrix<T, _Alloc, _Impl>& rhs)
  {
    std::swap(lhs._impl, rhs._impl);
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>&
  Matrix<T, _Alloc, _Impl>::operator=(Matrix<T, _Alloc, _Impl> other)
  {
    swap(*this, other);
    return *this;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>::~Matrix()
  {
  }

  template <class T,
            class _Alloc,
            class _Impl>
  T&
  Matrix<T, _Alloc, _Impl>::operator()(const size_t row,
                                       const size_t col) const
  {
    return _impl(row, col);
  }

  template <class T,
            class _Alloc,
            class _Impl>
  T&
  Matrix<T, _Alloc, _Impl>::operator()(const size_t row,
                                       const size_t col)
  {
    return _impl(row, col);
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>&
  Matrix<T, _Alloc, _Impl>::operator+=(const Matrix<T, _Alloc, _Impl>& other)
  {
    _impl += other._impl;
    return *this;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>&
  Matrix<T, _Alloc, _Impl>::operator-=(const Matrix<T, _Alloc, _Impl>& other)
  {
    _impl -= other._impl;
    return *this;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>&
  Matrix<T, _Alloc, _Impl>::operator*=(const Matrix<T, _Alloc, _Impl>& other)
  {
    _impl *= other._impl;
    return *this;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>&
  Matrix<T, _Alloc, _Impl>::operator+=(const T& scalar)
  {
    _impl += scalar;
    return *this;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>&
  Matrix<T, _Alloc, _Impl>::operator-=(const T& scalar)
  {
    _impl -= scalar;
    return *this;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>&
  Matrix<T, _Alloc, _Impl>::operator*=(const T& scalar)
  {
    _impl *= scalar;
    return *this;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>&
  Matrix<T, _Alloc, _Impl>::operator/=(const T& scalar)
  {
    _impl /= scalar;
    return *this;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  T* Matrix<T, _Alloc, _Impl>::data() const
  {
    return _impl.data();
  }

  template <class T,
            class _Alloc,
            class _Impl>
  size_t Matrix<T, _Alloc, _Impl>::rows() const
  {
    return _impl.rows();
  }

  template <class T,
            class _Alloc,
            class _Impl>
  size_t Matrix<T, _Alloc, _Impl>::cols() const
  {
    return _impl.cols();
  }

  template <class T,
            class _Alloc,
            class _Impl>
  constexpr _Alloc
  Matrix<T, _Alloc, _Impl>::get_allocator() const
  {
    return _impl.get_allocator();
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  Matrix<T, _Alloc, _Impl>::operator-()
  {
    Matrix<T, _Alloc, _Impl> result;
    result._impl = -_impl;
    return result;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  typename Matrix<T, _Alloc, _Impl>::iterator
  begin(const Matrix<T, _Alloc, _Impl>& m)
  {
    return m.data();
  }

  template <class T,
            class _Alloc,
            class _Impl>
  typename Matrix<T, _Alloc, _Impl>::const_iterator
  cbegin(const Matrix<T, _Alloc, _Impl>& m)
  {
    return m.data();
  }

  template <class T,
            class _Alloc,
            class _Impl>
  typename Matrix<T, _Alloc, _Impl>::iterator
  end(const Matrix<T, _Alloc, _Impl>& m)
  {
    return m.data() + m.rows() * m.cols();
  }

  template <class T,
            class _Alloc,
            class _Impl>
  typename Matrix<T, _Alloc, _Impl>::const_iterator
  cend(const Matrix<T, _Alloc, _Impl>& m)
  {
    return m.data() + m.rows() * m.cols();
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const Matrix<T, _Alloc, _Impl>& lhs,
            const Matrix<T, _Alloc, _Impl>& rhs)
  {
    Matrix<T, _Alloc, _Impl> result(lhs);
    return result += rhs;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const Matrix<T, _Alloc, _Impl>& lhs,
            const Matrix<T, _Alloc, _Impl>& rhs)
  {
    Matrix<T, _Alloc, _Impl> result(lhs);
    return result -= rhs;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const Matrix<T, _Alloc, _Impl>& lhs,
            const Matrix<T, _Alloc, _Impl>& rhs)
  {
    Matrix<T, _Alloc, _Impl> result(lhs);
    return result *= rhs;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const Matrix<T, _Alloc, _Impl>& lhs,
            const T& scalar)
  {
    Matrix<T, _Alloc, _Impl> result(lhs);
    return result += scalar;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const Matrix<T, _Alloc, _Impl>& lhs,
            const T& scalar)
  {
    Matrix<T, _Alloc, _Impl> result(lhs);
    return result -= scalar;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const Matrix<T, _Alloc, _Impl>& lhs,
            const T& scalar)
  {
    Matrix<T, _Alloc, _Impl> result(lhs);
    return result *= scalar;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator/(const Matrix<T, _Alloc, _Impl>& lhs,
            const T& scalar)
  {
    Matrix<T, _Alloc, _Impl> result(lhs);
    return result /= scalar;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const T& scalar,
            const Matrix<T, _Alloc, _Impl>& rhs)
  {
    Matrix<T, _Alloc, _Impl> result(rhs);
    return result += scalar;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const T& scalar,
            const Matrix<T, _Alloc, _Impl>& rhs)
  {
    Matrix<T, _Alloc, _Impl> result(rhs);
    return (-result) += scalar;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const T& scalar,
            const Matrix<T, _Alloc, _Impl>& rhs)
  {
    Matrix<T, _Alloc, _Impl> result(rhs);
    return result *= scalar;
  }

  template <class T,
            class _Alloc,
            class _Impl>
  bool
  operator==(const Matrix<T, _Alloc, _Impl>& lhs,
             const Matrix<T, _Alloc, _Impl>& rhs)
  {
    return lhs._impl == rhs._impl;
  }
}
