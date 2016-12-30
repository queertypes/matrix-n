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
#include <random>
#include <numeric>
#include <cassert>

namespace numerical {

  template <class Matrix>
  Matrix
  IdentityMatrixGenerator<Matrix>::operator()(const size_t n) const
  {
    Matrix result{n};
    for (size_t i = 0; i < n; ++i)
      result(i,i) = 1;
    return result;
  }

  template <class Matrix>
  Matrix
  IdentityMatrixGenerator<Matrix>::operator()(const size_t rows,
                                              const size_t cols) const
  {
    Matrix result{rows, cols};
    for (size_t i = 0; i < std::min(rows,cols); ++i)
      result(i,i) = 1;
    return result;
  }

  template <class Matrix,
            size_t Value>
  Matrix
  ValueMatrixGenerator<Matrix, Value>::operator()(const size_t n) const
  {
    Matrix result{n};
    for (auto& i : result)
      i = Value;
    return result;
  }

  template <class Matrix,
            size_t Value>
  Matrix
  ValueMatrixGenerator<Matrix, Value>::operator()(const size_t rows,
                                                  const size_t cols) const
  {
    Matrix result(rows,cols);
    for (auto& i : result)
      i = Value;
    return result;
  }

  template <class Matrix>
  Matrix
  UnitVectorGenerator<Matrix>::operator()(const size_t cols,
                                          const size_t index) const
  {
    Matrix result(1, cols);

    assert(index < cols);
    result(0,index) = 1;

    return result;
  }

  template <class Matrix,
            class RNG>
  typename Matrix::value_type
  RandomMatrixGenerator<Matrix, RNG>::generate_random_value() const
  {
    return std::generate_canonical<typename Matrix::value_type,
                                   sizeof(typename Matrix::value_type),
                                   RNG>(generator);
  }

  template <class Matrix,
            class RNG>
  Matrix
  RandomMatrixGenerator<Matrix, RNG>::operator()(const size_t n) const
  {
    Matrix result{n};
    for (auto& i : result)
      i = generate_random_value();
    return result;
  }

  template <class Matrix,
            class RNG>
  Matrix
  RandomMatrixGenerator<Matrix, RNG>::operator()(const size_t rows,
                                                 const size_t cols) const
  {
    Matrix result{rows, cols};
    for (auto& i : result)
      i = generate_random_value();
    return result;
  }

  template <class Matrix,
            class MatrixGenerator>
  Matrix generate_matrix(const size_t n) {
    static MatrixGenerator g;
    return g(n);
  }

  template <class Matrix,
            class MatrixGenerator>
  Matrix generate_matrix(const size_t rows, const size_t cols) {
    static MatrixGenerator g;
    return g(rows, cols);
  }

  template <class Matrix>
  Matrix random(const size_t n) {
    return generate_matrix<Matrix,
                           RandomMatrixGenerator<Matrix>>(n);
  }

  template <class Matrix>
  Matrix random(const size_t rows, const size_t cols) {
    return generate_matrix<Matrix,
                           RandomMatrixGenerator<Matrix>>(rows, cols);
  }

  template <class Matrix>
  Matrix zeros(const size_t n) {
    return generate_matrix<Matrix,
                           ValueMatrixGenerator<Matrix, 0>>(n);
  }

  template <class Matrix>
  Matrix zeros(const size_t rows, const size_t cols) {
    return generate_matrix<Matrix,
                           ValueMatrixGenerator<Matrix, 0>>(rows, cols);
  }

  template <class Matrix>
  Matrix ones(const size_t n) {
    return generate_matrix<Matrix,
                           ValueMatrixGenerator<Matrix, 1>>(n);
  }

  template <class Matrix>
  Matrix ones(const size_t rows, const size_t cols) {
    return generate_matrix<Matrix,
                           ValueMatrixGenerator<Matrix, 1>>(rows, cols);
  }

  template <class Matrix>
  Matrix eye(const size_t n) {
    return generate_matrix<Matrix,
                           IdentityMatrixGenerator<Matrix>>(n);
  }

  template <class Matrix>
  Matrix eye(const size_t rows, const size_t cols) {
    return generate_matrix<Matrix,
                           IdentityMatrixGenerator<Matrix>>(rows, cols);
  }

  template <class Matrix>
  Matrix unit(const size_t cols, const size_t index)
  {
    static UnitVectorGenerator<Matrix> g;
    return g(cols, index);
  }
}
