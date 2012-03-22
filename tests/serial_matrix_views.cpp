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

using numerical::Matrix;
using numerical::detail::RowView;
using numerical::detail::ColumnView;
using numerical::impl::SerialMatrixImplementation;
using numerical::ones;
using numerical::eye;
using numerical::zeros;
using numerical::random;

static const size_t N = 256;

typedef Matrix<double,
               SerialMatrixImplementation> MatrixType;
typedef RowView<double> RowType;
typedef ColumnView<double> ColumnType;

TEST(test_matrix_view_generation, row_view_generation)
{
  MatrixType m(2);

  m(0,0) = 1.0d;
  m(0,1) = 2.0d;
  m(1,0) = 3.0d;
  m(1,1) = 4.0d;

  RowType r1 = m.row(0);
  RowType r2 = m.row(1);

  EXPECT_EQ(r1(0), m(0,0));
  EXPECT_EQ(r1(1), m(0,1));
  EXPECT_EQ(r2(0), m(1,0));
  EXPECT_EQ(r2(1), m(1,1));
}

TEST(test_matrix_view_assignment, row_assignment)
{
  MatrixType m1 = zeros<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);

  m1.row(0) = m2.row(1);

  // row assignment works
  EXPECT_EQ(m1(0,0), m2(1,0));
  EXPECT_EQ(m1(0,1), m2(1,1));

  // row assignment only affects target row
  EXPECT_FLOAT_EQ(m1(1,0), 0.0d);
  EXPECT_FLOAT_EQ(m1(1,1), 0.0d);

  // row assignment does not affect rhs
  std::for_each(cbegin(m2), cend(m2),
                [](const double x) {EXPECT_FLOAT_EQ(x, 1.0d); });
}

TEST(test_matrix_view_assignment, row_assignment_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1 = zeros<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(3);

  EXPECT_DEATH(m1.row(0) = m2.row(1), "");
}

TEST(test_matrix_view_assignment, row_add_assignment)
{
  MatrixType m1 = ones<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);;

  m1.row(0) += m2.row(1);

  // row add assignment works
  EXPECT_FLOAT_EQ(m1(0,0), 2.0d);
  EXPECT_FLOAT_EQ(m1(0,1), 2.0d);

  // row add assignment only affects target row
  EXPECT_FLOAT_EQ(m1(1,0), 1.0d);
  EXPECT_FLOAT_EQ(m1(1,1), 1.0d);

  // row add assignment does not affect rhs
  std::for_each(cbegin(m2), cend(m2),
                [](const double x) {EXPECT_FLOAT_EQ(x, 1.0d); });
}

TEST(test_matrix_view_assignment, row_subtract_assignment)
{
  MatrixType m1 = zeros<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);;

  m1.row(0) -= m2.row(1);

  // row subtract assignment works
  EXPECT_FLOAT_EQ(m1(0,0), -1.0d);
  EXPECT_FLOAT_EQ(m1(0,1), -1.0d);

  // row subtract assignment only affects target row
  EXPECT_FLOAT_EQ(m1(1,0), 0.0d);
  EXPECT_FLOAT_EQ(m1(1,1), 0.0d);

  // row subtract assignment does not affect rhs
  std::for_each(cbegin(m2), cend(m2),
                [](const double x) {EXPECT_FLOAT_EQ(x, 1.0d); });
}

TEST(test_matrix_view_ops, row_addition)
{
  MatrixType m1 = ones<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);
  MatrixType m3(2);

  m3.row(0) = m1.row(0) + m2.row(0);
  m3.row(1) = m1.row(1) + m2.row(1);

  std::for_each(cbegin(m3), cend(m3),
                [](const double x) {EXPECT_FLOAT_EQ(x, 2.0d); });
}


TEST(test_matrix_view_ops, row_subtraction)
{
  MatrixType m1 = zeros<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);
  MatrixType m3(2);

  m3.row(0) = m1.row(0) - m2.row(0);
  m3.row(1) = m1.row(1) - m2.row(1);

  std::for_each(cbegin(m3), cend(m3),
                [](const double x) {EXPECT_FLOAT_EQ(x, -1.0d); });
}

TEST(test_matrix_view_generation, column_view_generation)
{
  MatrixType m(2);

  m(0,0) = 1.0d;
  m(0,1) = 2.0d;
  m(1,0) = 3.0d;
  m(1,1) = 4.0d;

  ColumnType c1 = m.col(0);
  ColumnType c2 = m.col(1);

  EXPECT_EQ(c1(0), m(0,0));
  EXPECT_EQ(c1(1), m(1,0));
  EXPECT_EQ(c2(0), m(0,1));
  EXPECT_EQ(c2(1), m(1,1));
}

TEST(test_matrix_view_assignment, column_assignment)
{
  MatrixType m1 = zeros<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);

  //#include <iostream>
  m1.col(0) = m2.col(1);

  // column assignment works
  EXPECT_FLOAT_EQ(m1(0,0), m2(0,1));
  EXPECT_FLOAT_EQ(m1(1,0), m2(1,1));

  // column assignment only affects target column
  EXPECT_FLOAT_EQ(m1(0,1), 0.0d);
  EXPECT_FLOAT_EQ(m1(1,1), 0.0d);

  // column assignment does not affect rhs
  EXPECT_FLOAT_EQ(m2(0,0), 1.0d);
  EXPECT_FLOAT_EQ(m2(0,1), 1.0d);
  EXPECT_FLOAT_EQ(m2(1,0), 1.0d);
  EXPECT_FLOAT_EQ(m2(1,1), 1.0d);
}
/*
TEST(test_matrix_view_assignment, column_add_assignment)
{
  MatrixType m1 = ones<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);;

  m1.col(0) += m2.col(1);

  // column add assignment works
  EXPECT_FLOAT_EQ(m1(0,0), 2.0d);
  EXPECT_FLOAT_EQ(m1(1,0), 2.0d);

  // column add assignment only affects target column
  EXPECT_FLOAT_EQ(m1(0,1), 1.0d);
  EXPECT_FLOAT_EQ(m1(1,1), 1.0d);

  // column add assignment does not affect rhs
  EXPECT_FLOAT_EQ(m2(0,0), 1.0d);
  EXPECT_FLOAT_EQ(m2(0,1), 1.0d);
  EXPECT_FLOAT_EQ(m2(1,0), 1.0d);
  EXPECT_FLOAT_EQ(m2(1,1), 1.0d);
}

TEST(test_matrix_view_assignment, column_subtract_assignment)
{
  MatrixType m1 = zeros<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);;

  m1.col(0) += m2.col(1);

  // column subtract assignment works
  EXPECT_FLOAT_EQ(m1(0,0), -1.0d);
  EXPECT_FLOAT_EQ(m1(1,0), -1.0d);

  // column subtract assignment only affects target column
  EXPECT_FLOAT_EQ(m1(0,1), 0.0d);
  EXPECT_FLOAT_EQ(m1(1,1), 0.0d);

  // column subtract assignment does not affect rhs
  EXPECT_FLOAT_EQ(m2(0,0), 1.0d);
  EXPECT_FLOAT_EQ(m2(0,1), 1.0d);
  EXPECT_FLOAT_EQ(m2(1,0), 1.0d);
  EXPECT_FLOAT_EQ(m2(1,1), 1.0d);
}

TEST(test_matrix_view_ops, column_addition)
{
  MatrixType m1 = ones<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);
  MatrixType m3(2);

  m3.col(0) = m1.col(0) + m2.col(0);
  m3.col(1) = m1.col(1) + m2.col(1);

  for (auto iter = cbegin(m3), iend = cend(m3); iter != iend; ++iter)
    EXPECT_FLOAT_EQ(*iter, 2.0d);
}

TEST(test_matrix_view_ops, column_subtraction)
{
  MatrixType m1 = zeros<MatrixType>(2);
  MatrixType m2 = ones<MatrixType>(2);
  MatrixType m3(2);

  m3.col(0) = m1.col(0) - m2.col(0);
  m3.col(1) = m1.col(1) - m2.col(1);

  for (auto iter = cbegin(m3), iend = cend(m3); iter != iend; ++iter)
    EXPECT_FLOAT_EQ(*iter, -1.0d);
}
*/
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
