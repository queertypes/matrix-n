#include <gtest/gtest.h>
#include <matrix_n/numerical/matrix.hpp>
#include <matrix_n/numerical/matrix_generator.hpp>
#include <matrix_n/numerical/matrix/serial_matrix_implementation.hpp>

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

  m1.col(0) -= m2.col(1);

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

TEST(matrix_matrix_view_ops, column_row_multiply)
{
  MatrixType m = ones<MatrixType>(3);
  RowType r = m.row(0);
  ColumnType c = m.col(0);
  MatrixType result = c * r;

  for (const auto x : result)
    EXPECT_FLOAT_EQ(x, 1.0d);
}

TEST(matrix_matrix_view_ops, row_column_multiply)
{
  MatrixType m = ones<MatrixType>(3);
  RowType r = m.row(0);
  ColumnType c = m.col(0);
  MatrixType::value_type result = (r * c)(0,0);

  EXPECT_FLOAT_EQ(result, 3.0d);
}

TEST(matrix_matrix_view_ops, row_matrix_multiply)
{
  MatrixType m = ones<MatrixType>(3);
  MatrixType result = m.row(0) * m;

  for (const auto x : result)
    EXPECT_FLOAT_EQ(x, 3.0d);
}

TEST(matrix_matrix_view_ops, column_matrix_multiply)
{
  MatrixType m1 = ones<MatrixType>(1,3);
  MatrixType m2 = ones<MatrixType>(3);
  MatrixType result = m2.col(0) * m1;

  for (const auto x : result)
    EXPECT_FLOAT_EQ(x, 1.0d);
}

TEST(matrix_matrix_view_ops, matrix_row_multiply)
{
  MatrixType m1 = ones<MatrixType>(3,1);
  MatrixType m2 = ones<MatrixType>(3);
  MatrixType result = m1 * m2.row(0);

  EXPECT_FLOAT_EQ(result(0,0), 3.0d);  
}

TEST(matrix_matrix_view_ops, matrix_column_multiply)
{
  MatrixType m = ones<MatrixType>(3);
  MatrixType result = m * m.col(0);

  for (const auto x : result)
    EXPECT_FLOAT_EQ(x, 3.0d);
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

TEST(test_matrix_view_assertions, row_assign_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(2);
  MatrixType m2(3);

  EXPECT_DEATH(m1.row(0) = m2.row(0), "");
}

TEST(test_matrix_view_assertions, row_add_assign_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(2);
  MatrixType m2(3);

  EXPECT_DEATH(m1.row(0) += m2.row(0), "");
}

TEST(test_matrix_view_assertions, col_assign_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(2);
  MatrixType m2(3);

  EXPECT_DEATH(m1.col(0) = m2.col(0), "");
}

TEST(test_matrix_view_assertions, col_add_assign_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(2);
  MatrixType m2(3);

  EXPECT_DEATH(m1.col(0) += m2.col(0), "");
}

TEST(test_matrix_view_assertions, col_subtract_assign_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(2);
  MatrixType m2(3);

  EXPECT_DEATH(m1.col(0) -= m2.col(0), "");
}

TEST(test_matrix_view_assertions, row_col_multiply_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(2,3);
  EXPECT_DEATH(m1.row(0) * m1.col(0), "");
}

TEST(test_matrix_view_assertions, col_row_multiply_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(2,3);
  EXPECT_DEATH(m1.col(0) * m1.row(0), "");
}

TEST(test_matrix_view_assertions, row_mat_multiply_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(1,1);
  MatrixType m2(2,2);
  EXPECT_DEATH(m2.row(0) * m1, "");
}

TEST(test_matrix_view_assertions, col_mat_multiply_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m1(3,1);
  MatrixType m2(2,2);
  EXPECT_DEATH(m2.col(0) * m1, "");
}

TEST(test_matrix_view_assertions, mat_row_multiply_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m(2,3);
  EXPECT_DEATH(m * m.row(0), "");
}

TEST(test_matrix_view_assertions, mat_col_multiply_dim_mismatch)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  MatrixType m(1,3);
  EXPECT_DEATH(m * m.col(0), "");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
