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
#include <gtest/gtest.h>
#include <numerical/matrix.hpp>
#include <numerical/matrix_generator.hpp>
#include <numerical/matrix/serial_matrix_implementation.hpp>
#include <numerical/determinant.hpp>
#include <numerical/determinant/gsl_determinant_implementation.hpp>

using numerical::Matrix;
using numerical::impl::SerialMatrixImplementation;
using numerical::Determinant;
using numerical::impl::GslDeterminantImplementation;
using numerical::ones;
using numerical::zeros;
using numerical::eye;

typedef Matrix<double,
               SerialMatrixImplementation> MatrixType;

static const size_t N = 256;

typename MatrixType::value_type
det(const MatrixType& m)
{
  static Determinant<MatrixType,
                     GslDeterminantImplementation<MatrixType>> _det;
  return _det(m);
}

TEST(DeterminantTest, IdentityIsOne)
{
  auto m = eye<MatrixType>(N);
  ASSERT_FLOAT_EQ(det(m), 1.0d);
}

TEST(DeterminantTest, ZeroMatrixIsZero)
{
  auto m = zeros<MatrixType>(N);
  ASSERT_FLOAT_EQ(det(m), 0.0d);
}

TEST(DeterminantTest, HandMadeMatrix)
{
  MatrixType m(2,2);

  // [1 2; 3 4] = 1 * 4 - 2 * 3 = -2
  m(0,0) = 1;
  m(0,1) = 2;
  m(1,0) = 3;
  m(1,1) = 4;

  ASSERT_FLOAT_EQ(det(m), -2.0d);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
