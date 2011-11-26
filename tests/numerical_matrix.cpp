#include <gtest/gtest.h>
#include <numerical/matrix.hpp>
#include <numerical/matrix_generator.hpp>
using namespace std;
using namespace numerical;

typedef Matrix<float> MatrixType;

TEST(test_matrix_constructors, default_constructor_square)
{
	MatrixType a(2);
	EXPECT_EQ(a.rows(), 2);
	EXPECT_EQ(a.cols(), 2);
}

TEST(test_matrix_constructors, default_constructor_rectangle)
{
	MatrixType a(2,3);
	EXPECT_EQ(a.rows(), 2);
	EXPECT_EQ(a.cols(), 3);
}

TEST(test_matrix_constructors, copy_constructor)
{
	MatrixType a(2);
	MatrixType b(a);

	EXPECT_EQ(a, b);	
}

TEST(test_matrix_constructors, move_constructor)
{
	MatrixType a(2);
	MatrixType b(std::move(a));

	EXPECT_EQ(a.rows(), 0);
	EXPECT_EQ(a.cols(), 0);
	EXPECT_EQ(b.rows(), 2);
	EXPECT_EQ(b.cols(), 2);
}

TEST(test_matrix_ops, copy_assignment)
{
	MatrixType a(2);
	MatrixType b(3);

	a = b;
	EXPECT_EQ(a,b);
}

TEST(test_matrix_ops, move_assignment)
{
	MatrixType a(2);
	MatrixType b(3);
	a = std::move(b);

	EXPECT_EQ(a.rows(), 3);
	EXPECT_EQ(a.cols(), 3);
	EXPECT_EQ(b.rows(), 0);
	EXPECT_EQ(b.cols(), 0);
}

TEST(test_matrix_ops, matrix_matrix_add_assign)
{
	MatrixType a = ones<MatrixType>(3);
	a += ones<MatrixType>(3);
	
	for (size_t i = 0; i < a.rows(); ++i)
		for (size_t j = 0; j < a.cols(); ++j)
			EXPECT_EQ(a(i,j), 2);
}

TEST(test_matrix_ops, matrix_scalar_add_assign)
{
	MatrixType a = ones<MatrixType>(3);
	a += 1;

	for (size_t i = 0; i < a.rows(); ++i)
		for (size_t j = 0; j < a.cols(); ++j)
			EXPECT_EQ(a(i,j), 2);
}

TEST(test_matrix_ops, matrix_matrix_subtract_assign)
{
	MatrixType a = ones<MatrixType>(3);
	a -= ones<MatrixType>(3);
	
	for (size_t i = 0; i < a.rows(); ++i)
		for (size_t j = 0; j < a.cols(); ++j)
			EXPECT_EQ(a(i,j), 0);
}

TEST(test_matrix_ops, matrix_scalar_subtract_assign)
{
	MatrixType a = ones<MatrixType>(3);
	a -= 1;

	for (size_t i = 0; i < a.rows(); ++i)
		for (size_t j = 0; j < a.cols(); ++j)
			EXPECT_EQ(a(i,j), 0);
}

TEST(test_matrix_ops, matrix_matrix_multiply_assign)
{
	MatrixType a = numerical::random<MatrixType>(3);
	MatrixType b(a);
	b *= eye<MatrixType>(3);
	
	EXPECT_EQ(a,b);
}

TEST(test_matrix_ops, matrix_scalar_multiply_assign)
{
	MatrixType a = ones<MatrixType>(3);
	a *= 2;

	for (size_t i = 0; i < a.rows(); ++i)
		for (size_t j = 0; j < a.cols(); ++j)
			EXPECT_EQ(a(i,j), 2);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

