#include <gtest/gtest.h>

#include <matrix_n/numerical/matrix.hpp>
#include <matrix_n/numerical/matrix_generator.hpp>
#include <matrix_n/numerical/matrix/serial_matrix_implementation.hpp>
#include <matrix_n/numerical/determinant.hpp>
#include <matrix_n/numerical/determinant/gsl_determinant_implementation.hpp>
#include <matrix_n/numerical/inverse.hpp>
#include <matrix_n/numerical/inverse/gsl_inverse_implementation.hpp>

#include <fast_slater/compchem/slater_determinant.hpp>
#include <fast_slater/compchem/slater_determinant/just_update.hpp>
#include <fast_slater/compchem/slater_determinant/sherman_morrison.hpp>

using numerical::Matrix;
using numerical::impl::SerialMatrixImplementation;
using numerical::Determinant;
using numerical::impl::GslDeterminantImplementation;
using numerical::Inverse;
using numerical::impl::GslInverseImplementation;
using compchem::SlaterDeterminant;
using compchem::impl::JustUpdate;
using compchem::impl::ShermanMorrison;

typedef Matrix<double,
               SerialMatrixImplementation> MatrixType;
typedef Determinant<MatrixType,
                    GslDeterminantImplementation<MatrixType>> DeterminantType;
typedef Inverse<MatrixType,
                GslInverseImplementation<MatrixType>> InverseType;
typedef JustUpdate<MatrixType, 
                   DeterminantType, 
                   InverseType> JUSlaterDeterminantImplType;
typedef ShermanMorrison<MatrixType, 
                        DeterminantType, 
                        InverseType> SMSlaterDeterminantImplType;

typedef SlaterDeterminant<MatrixType,
                          DeterminantType,
                          InverseType,
                          JUSlaterDeterminantImplType> JUSlaterDeterminantType;

typedef SlaterDeterminant<MatrixType,
                          DeterminantType,
                          InverseType,
                          SMSlaterDeterminantImplType> SMSlaterDeterminantType;

static const double THRESHOLD = .975d;

TEST(JustUpdate, TwoByTwoForFourSteps)
{
  JUSlaterDeterminantType slater;
  double d[] = {1,2,
                3,4};
  double v[] = {1,2,
                3,4,
                5,6,
                7,8};

  MatrixType md(d, d+4, 2);
  MatrixType mv(v, v+8, 4, 2);

  MatrixType result = slater(md, mv, 4, THRESHOLD);
  DeterminantType det;
  EXPECT_FLOAT_EQ(det(result), -28);
}

TEST(JustUpdate, OneHundredIdentityElectrons)
{
  JUSlaterDeterminantType slater;

  MatrixType md = numerical::eye<MatrixType>(100);
  MatrixType mv = numerical::ones<MatrixType>(1000, 100);

  MatrixType result = slater(md, mv, 1000, THRESHOLD);
  DeterminantType det;
  EXPECT_FLOAT_EQ(det(result), 1001.0d);
}

TEST(ShermanMorrison, TwoByTwoForFourSteps)
{
  SMSlaterDeterminantType slater;
  double d[] = {1,2,
                3,4};
  double v[] = {1,2,
                3,4,
                5,6,
                7,8};

  MatrixType md(d, d+4, 2);
  MatrixType mv(v, v+8, 4, 2);

  MatrixType result = slater(md, mv, 4, THRESHOLD);
  DeterminantType det;
  EXPECT_FLOAT_EQ(det(result), -28);
}

TEST(ShermanMorrison, OneHundredIdentityElectrons)
{
  SMSlaterDeterminantType slater;

  MatrixType md = numerical::eye<MatrixType>(100);
  MatrixType mv = numerical::ones<MatrixType>(1000, 100);

  MatrixType result = slater(md, mv, 1000, THRESHOLD);
  DeterminantType det;
  EXPECT_FLOAT_EQ(det(result), 1001.0d);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
