#include <gtest/gtest.h>
#include <matrix_n/numerical/matrix.hpp>
#include <matrix_n/numerical/matrix_generator.hpp>
#include <matrix_n/numerical/matrix/serial_matrix_implementation.hpp>

using numerical::Matrix;
using numerical::impl::SerialMatrixImplementation;
using numerical::ones;
using numerical::eye;
using numerical::random;

static const size_t N = 256;

typedef Matrix<double,
               SerialMatrixImplementation> MatrixType;

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
  MatrixType a(N);
  MatrixType b(a);

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

TEST(test_matrix_constructors, range_constructor_square)
{
  typename MatrixType::value_type d[9] = {1,2,3,
                                          4,5,6,
                                          7,8,9};
  MatrixType m(d, d+9, 3);
  
  typename MatrixType::value_type i = 1;
  for (const auto x : m)
    EXPECT_EQ(x, i++);
}

TEST(test_matrix_constructors, range_constructor_rectangle)
{
  typename MatrixType::value_type d[9] = {1,2,3,
                                          4,5,6,
                                          7,8,9};

  MatrixType m(d, d+9, 3, 3);
  
  typename MatrixType::value_type i = 1;
  for (const auto x : m)
    EXPECT_EQ(x, i++);
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
  a = a + 1.0;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 2.0d);
}

TEST(test_matrix_binary_ops, matrix_scalar_subtract)
{
  MatrixType a = ones<MatrixType>(N);
  a = a - 1.0;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 0.0d);
}

TEST(test_matrix_binary_ops, matrix_scalar_multiply)
{
  MatrixType a = ones<MatrixType>(N);
  a = a * 3.0;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 3.0);
}
TEST(test_matrix_binary_ops, scalar_matrix_add)
{
  MatrixType a = ones<MatrixType>(N);
  a = 1.0 + a;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 2.0);
}

TEST(test_matrix_binary_ops, scalar_matrix_subtract)
{
  MatrixType a = ones<MatrixType>(N);
  a = 3.0 - a;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 2.0);
}

TEST(test_matrix_binary_ops, scalar_matrix_multiply)
{
  MatrixType a = ones<MatrixType>(N);
  a = 10.0 * a;

  for (size_t i = 0; i < a.rows(); ++i)
    for (size_t j = 0; j < a.cols(); ++j)
      EXPECT_FLOAT_EQ(a(i,j), 10.0);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
