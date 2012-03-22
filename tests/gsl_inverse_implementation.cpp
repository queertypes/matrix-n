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
#include <gtest/gtest.h>
#include <matrix_n/numerical/matrix.hpp>
#include <matrix_n/numerical/matrix_generator.hpp>
#include <matrix_n/numerical/matrix/serial_matrix_implementation.hpp>
#include <matrix_n/numerical/inverse.hpp>
#include <matrix_n/numerical/inverse/gsl_inverse_implementation.hpp>

using numerical::Matrix;
using numerical::impl::SerialMatrixImplementation;
using numerical::Inverse;
using numerical::impl::GslInverseImplementation;
using numerical::ones;
using numerical::zeros;
using numerical::eye;

typedef Matrix<double,
               SerialMatrixImplementation> MatrixType;

static const size_t N = 256;

MatrixType
inv(const MatrixType& m)
{
  static Inverse<MatrixType,
                 GslInverseImplementation<MatrixType>> _inv;
  return _inv(m);
}

TEST(InverseTest, IdentityIsIdentity)
{
  auto m = eye<MatrixType>(N);
  auto expect = inv(m);

  for (size_t i = 0; i < m.rows(); ++i)
    for (size_t j = 0; j < m.cols(); ++j)
      ASSERT_FLOAT_EQ(m(i,j), expect(i,j));
}

TEST(InverseTest, HandMadeMatrix)
{
  MatrixType m(2,2);
  MatrixType expect(2,2);

  // [1 2; 3 4]
  m(0,0) = 1;
  m(0,1) = 2;
  m(1,0) = 3;
  m(1,1) = 4;

  // [-2 -1; 1.5 -0.5]
  expect(0,0) = -2.0d;
  expect(0,1) = 1.0d;
  expect(1,0) = 1.5d;
  expect(1,1) = -0.5d;

  MatrixType minv = inv(m);

  for (size_t i = 0; i < m.rows(); ++i) {
    for (size_t j = 0; j < m.cols(); ++j) {
      EXPECT_FLOAT_EQ(minv(i,j), expect(i,j));
    }
  }
}

TEST(InverseTest, BadInverse)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  auto m = zeros<MatrixType>(2);

  ASSERT_DEATH(inv(m), ".*GSL error.*");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
