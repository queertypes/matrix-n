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
#ifndef NUMERICAL_MATRIX_HPP
#define NUMERICAL_MATRIX_HPP

#include <numerical/matrix/serial_matrix_implementation.hpp>

namespace numerical {

  template <class T,
            class Allocator = std::allocator<T>,
            template <class, class> class MatrixImpl = 
              impl::SerialMatrixImplementation> 
  class Matrix {
  public:
    typedef T value_type;
    typedef typename MatrixImpl<T, Allocator>::iterator iterator;
    typedef typename MatrixImpl<T, Allocator>::const_iterator const_iterator;
    typedef Allocator allocator_type;
    typedef MatrixImpl<T, Allocator> matrix_implementation_type;

  public:
    Matrix();
    explicit Matrix(const size_t n);
    Matrix(const size_t rows, const size_t cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    template <class _T, class _Alloc, template <class, class> class _Impl>
    void friend swap(Matrix<_T, _Alloc, _Impl>&,
                     Matrix<_T, _Alloc, _Impl>&);

    Matrix& operator=(Matrix other);

    T& operator()(const size_t row, const size_t col);
    T& operator()(const size_t row, const size_t col) const;

    Matrix operator-();

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    Matrix& operator+=(const T& other);
    Matrix& operator-=(const T& other);
    Matrix& operator*=(const T& other);
    Matrix& operator/=(const T& other);

    template <class _T, class _Alloc, 
              template <class, class> class _Impl>
    friend bool 
    operator==(const Matrix<_T, _Alloc, _Impl>&,
               const Matrix<_T, _Alloc, _Impl>&);

  public:
    T* data() const;
    size_t rows() const;
    size_t cols() const;
    constexpr allocator_type get_allocator() const;

  private:
    matrix_implementation_type _impl;
  };

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  typename Matrix<T, _Alloc, _Impl>::iterator
  begin(const Matrix<T, _Alloc, _Impl>& m);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  typename Matrix<T, _Alloc, _Impl>::const_iterator
  cbegin(const Matrix<T, _Alloc, _Impl>& m);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  typename Matrix<T, _Alloc, _Impl>::iterator
  end(const Matrix<T, _Alloc, _Impl>& m);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  typename Matrix<T, _Alloc, _Impl>::const_iterator
  cend(const Matrix<T, _Alloc, _Impl>& m);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const Matrix<T, _Alloc, _Impl>&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const Matrix<T, _Alloc, _Impl>&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const Matrix<T, _Alloc, _Impl>&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const Matrix<T, _Alloc, _Impl>&,
            const T&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const Matrix<T, _Alloc, _Impl>&,
            const T&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const Matrix<T, _Alloc, _Impl>&,
            const T&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const T&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const T&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            template <class, class> class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const T&,
            const Matrix<T, _Alloc, _Impl>&);
}

#include <implementation/matrix.cpp>

#endif
