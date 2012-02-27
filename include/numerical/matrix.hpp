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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef NUMERICAL_MATRIX_HPP
#define NUMERICAL_MATRIX_HPP

#include <config.h>

namespace numerical {

  template <class T,
            class Allocator = std::allocator<T>,
            class MatrixImpl = impl::SerialMatrixImplementation<T, Allocator> >
  class Matrix {
  public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef MatrixImpl matrix_implementation_type;

  public:
    explicit Matrix(const size_t n);
    Matrix(const size_t rows, const size_t cols);
    Matrix(const Matrix& other);
    ~Matrix();

#ifdef HAS_MOVE_CONSTRUCTOR
    Matrix(Matrix&& other);
#endif

#ifdef HAS_MOVE_ASSIGNMENT
    Matrix& operator=(Matrix&& other);
#endif

    Matrix& operator=(const Matrix& other);

    T& operator()(const size_t row, const size_t col);
    T& operator()(const size_t row, const size_t col) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    Matrix& operator+=(const T& other);
    Matrix& operator-=(const T& other);
    Matrix& operator*=(const T& other);
    Matrix& operator/=(const T& other);

  public:
    T* data() const;
    size_t rows() const;
    size_t cols() const;
    constexpr allocator_type get_allocator() const;

  private:
    static matrix_implementation_type _impl;
  };

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const Matrix<T, _Alloc, _Impl>&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const Matrix<T, _Alloc, _Impl>&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const Matrix<T, _Alloc, _Impl>&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const Matrix<T, _Alloc, _Impl>&,
            const T&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const Matrix<T, _Alloc, _Impl>&,
            const T&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const Matrix<T, _Alloc, _Impl>&,
            const T&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator+(const T&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator-(const T&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            class _Impl>
  Matrix<T, _Alloc, _Impl>
  operator*(const T&,
            const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            class _Impl>
  bool operator==(const Matrix<T, _Alloc, _Impl>&,
                  const Matrix<T, _Alloc, _Impl>&);

  template <class T,
            class _Alloc,
            class _Impl>
  bool operator!=(const Matrix<T, _Alloc, _Impl>&,
                  const Matrix<T, _Alloc, _Impl>&);
}

#include <implementation/matrix.cpp>

#endif
