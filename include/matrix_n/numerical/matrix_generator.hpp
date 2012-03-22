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
#ifndef MATRIX_N_NUMERICAL_MATRIX_GENERATOR_HPP
#define MATRIX_N_NUMERICAL_MATRIX_GENERATOR_HPP

#include <random>

namespace numerical {

  template <class Matrix>
  struct IdentityMatrixGenerator {
    Matrix operator()(const size_t n) const;
    Matrix operator()(const size_t rows, const size_t cols) const;
  };

  template <class Matrix, size_t Value>
  struct ValueMatrixGenerator {
    Matrix operator()(const size_t n) const;
    Matrix operator()(const size_t rows, const size_t cols) const;
  };

  template <class Matrix>
  struct UnitVectorGenerator {
    Matrix operator()(const size_t cols, const size_t index) const;
  };

  template <class Matrix,
            class RandomNumberGenerator = std::minstd_rand>
  class RandomMatrixGenerator {
  public:
    typedef typename Matrix::value_type value_type;
  public:
    Matrix operator()(const size_t n) const;
    Matrix operator()(const size_t rows, const size_t cols) const;

  private:
    value_type generate_random_value() const;
  private:
    mutable RandomNumberGenerator generator;
  };

  template <class Matrix,
            class MatrixGenerator>
  Matrix generate_matrix(const size_t n);

  template <class Matrix,
            class MatrixGenerator>
  Matrix generate_matrix(const size_t rows, const size_t cols);

  template <class Matrix>
  Matrix random(const size_t n);

  template <class Matrix>
  Matrix random(const size_t rows, const size_t cols);

  template <class Matrix>
  Matrix zeros(const size_t n);

  template <class Matrix>
  Matrix zeros(const size_t rows, const size_t cols);

  template <class Matrix>
  Matrix ones(const size_t n);

  template <class Matrix>
  Matrix ones(const size_t rows, const size_t cols);

  template <class Matrix>
  Matrix eye(const size_t n);

  template <class Matrix>
  Matrix eye(const size_t rows, const size_t cols);

  template <class Matrix>
  Matrix unit(const size_t cols, const size_t index);
}

#include <matrix_n/implementation/matrix_generator.cpp>

#endif
