#include <gtest/gtest.h>
#include <matrix_n/numerical/matrix.hpp>
#include <matrix_n/numerical/matrix_generator.hpp>
#include <matrix_n/numerical/matrix/serial_matrix_implementation.hpp>
#include <matrix_n/numerical/determinant.hpp>
#include <matrix_n/numerical/determinant/gsl_determinant_implementation.hpp>

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
