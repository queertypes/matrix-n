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

using namespace std;
using numerical::Matrix;
using numerical::impl::SerialMatrixImplementation;
using numerical::ones;
using numerical::eye;
using numerical::random;
using std::allocator;

static const size_t N = 256;

typedef Matrix<float,
               allocator<float>,
               SerialMatrixImplementation<float,
                                          allocator<float>>> MatrixType;

TEST(test_matrix_constructors, default_constructor_square)
{
  MatrixType a{N};
  EXPECT_EQ(a.rows(), N);
  EXPECT_EQ(a.cols(), N);
}

TEST(test_matrix_constructors, default_constructor_rectangle)
{
  MatrixType a{N, N + 1};
  EXPECT_EQ(a.rows(), N);
  EXPECT_EQ(a.cols(), N + 1);
}

TEST(test_matrix_constructors, copy_constructor)
{
  MatrixType a{N};
  MatrixType b{a};

  EXPECT_EQ(a.rows(), b.rows());
  EXPECT_EQ(a.cols(), b.cols());

  for (auto iter = cbegin(a), iend = cend(a), iter2 = cbegin(b);
       iter != iend; ++iter, ++iter2) {
    EXPECT_EQ(*iter, *iter2);
  }
}

TEST(test_matrix_constructors, move_constructor)
{
  MatrixType a{N};
  MatrixType b = std::move(a);

  EXPECT_EQ(a.rows(), 0ul);
  EXPECT_EQ(a.cols(), 0ul);
  EXPECT_EQ(b.rows(), N);
  EXPECT_EQ(b.cols(), N);
}

TEST(test_matrix_aux, global_begin)
{
  MatrixType a{1};

  EXPECT_EQ(begin(a), a.data());
  EXPECT_EQ(cbegin(a), a.data());
}

TEST(test_matrix_aux, global_end)
{
  MatrixType a{1};

  EXPECT_EQ(end(a), a.data() + a.rows() * a.cols());
  EXPECT_EQ(cend(a), a.data() + a.rows() * a.cols());
}

TEST(test_matrix_assign, copy_assignment)
{
  MatrixType a{N};
  MatrixType b{N + 1};

  a = b;
  for (auto iter = cbegin(a), iend = cend(a), iter2 = cbegin(b);
       iter != iend; ++iter, ++iter2)
    EXPECT_EQ(*iter, *iter2);
}

TEST(test_matrix_assign, move_assignment)
{
  MatrixType a{N};
  MatrixType b{N + 1};
  a = std::move(b);

  EXPECT_EQ(a.rows(), N+1);
  EXPECT_EQ(a.cols(), N+1);
  EXPECT_EQ(b.rows(), 0ul);
  EXPECT_EQ(b.cols(), 0ul);
}

TEST(test_matrix_unary_ops, matrix_negate)
{
  MatrixType a = ones<MatrixType>(N);
  MatrixType b = -a;

  for (size_t i = 0; i < a.rows(); ++i) {
    for (size_t j = 0; j < a.cols(); ++j) {
      EXPECT_FLOAT_EQ(a(i,j), 1.0f);
      EXPECT_FLOAT_EQ(b(i,j), -1.0f);
    }
  }
}

TEST(test_matrix_assign, matrix_matrix_add_assign)
{
  MatrixType a = ones<MatrixType>(N);
  a += ones<MatrixType>(N);

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_EQ(a(i,j), 2ul);
}

TEST(test_matrix_assign, matrix_scalar_add_assign)
{
  MatrixType a = ones<MatrixType>(N);
  a += 1.0f;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_EQ(a(i,j), 2ul);
}

TEST(test_matrix_assign, matrix_matrix_subtract_assign)
{
  MatrixType a = ones<MatrixType>(N);
  a -= ones<MatrixType>(N);

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_EQ(a(i,j), 0ul);
}

TEST(test_matrix_assign, matrix_scalar_subtract_assign)
{
  MatrixType a = ones<MatrixType>(N);
  a -= 1.0f;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_EQ(a(i,j), 0ul);
}

TEST(test_matrix_assign, matrix_matrix_multiply_assign)
{
  MatrixType a = random<MatrixType>(N);
  MatrixType b{a};
  a *= eye<MatrixType>(N);

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), b(i,j));
}

TEST(test_matrix_assign, matrix_scalar_multiply_assign)
{
  MatrixType a = ones<MatrixType>(N);
  a *= 2.0f;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 2.0f);
}

TEST(test_matrix_assign, matrix_scalar_divide_assign)
{
  MatrixType a = ones<MatrixType>(N);
  a /= 2.0f;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 0.5f);
}

TEST(test_matrix_binary_ops, matrix_matrix_add)
{
  MatrixType a = ones<MatrixType>(N);
  a = a + ones<MatrixType>(N);

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 2.0f);
}

TEST(test_matrix_binary_ops, matrix_matrix_subtract)
{
  MatrixType a = ones<MatrixType>(N);
  a = a - ones<MatrixType>(N);

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 0.0f);
}

TEST(test_matrix_binary_ops, matrix_matrix_multiply)
{
  MatrixType a = ones<MatrixType>(N);
  MatrixType b = a * eye<MatrixType>(N);

  for (size_t i = 0; i < b.rows(); ++i) {
    for (size_t j = 0; j < b.cols(); ++j) {
      EXPECT_EQ(a(i,j), b(i,j));
    }
  }
}

TEST(test_matrix_binary_ops, matrix_scalar_add)
{
  MatrixType a = ones<MatrixType>(N);
  a = a + 1.0f;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 2.0f);
}

TEST(test_matrix_binary_ops, matrix_scalar_subtract)
{
  MatrixType a = ones<MatrixType>(N);
  a = a - 1.0f;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 0ul);
}

TEST(test_matrix_binary_ops, matrix_scalar_multiply)
{
  MatrixType a = ones<MatrixType>(N);
  a = a * 3.0f;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 3.0f);
}
TEST(test_matrix_binary_ops, scalar_matrix_add)
{
  MatrixType a = ones<MatrixType>(N);
  a = 1.0f + a;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 2.0f);
}

TEST(test_matrix_binary_ops, scalar_matrix_subtract)
{
  MatrixType a = ones<MatrixType>(N);
  a = 3.0f - a;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 2.0f);
}

TEST(test_matrix_binary_ops, scalar_matrix_multiply)
{
  MatrixType a = ones<MatrixType>(N);
  a = 10.0f * a;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 10.0f);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
