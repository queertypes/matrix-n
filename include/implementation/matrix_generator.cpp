#include <random>
#include <numeric>

namespace numerical {

	template <class Matrix>
	Matrix
	IdentityMatrixGenerator<Matrix>::operator()(const size_t n) const
	{
		Matrix result(n);
		for (size_t i = 0; i < n; ++i)
			result(i,i) = 1;
		return result;
	}

	template <class Matrix>
	Matrix
	IdentityMatrixGenerator<Matrix>::operator()(const size_t rows,
																							const size_t cols) const
	{
		Matrix result(rows, cols);
		for (size_t i = 0; i < std::min(rows,cols); ++i)
			result(i,i) = 1;
		return result;
	}

	template <class Matrix,
						size_t Value>
	Matrix
	ValueMatrixGenerator<Matrix, Value>::operator()(const size_t n) const
	{
		Matrix result(n);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j)
				result(i,j) = Value;
		return result;
	}
	template <class Matrix,
						size_t Value>
	Matrix
	ValueMatrixGenerator<Matrix, Value>::operator()(const size_t rows,
																									const size_t cols) const
	{
		Matrix result(rows,cols);
		for (size_t i = 0; i < rows; ++i)
			for (size_t j = 0; j < cols; ++j)
				result(i,j) = Value;
		return result;
	}
	
	template <class Matrix,
						class RNG>
	typename Matrix::value_type
	RandomMatrixGenerator<Matrix, RNG>::generate_random_value() const
	{
		const typename Matrix::value_type val = 
			static_cast<typename Matrix::value_type>(generator());
		return val / std::numeric_limits<typename Matrix::value_type>::max();
	}

	template <class Matrix,
						class RNG>
	Matrix&&
	RandomMatrixGenerator<Matrix, RNG>::operator()(const size_t n) const
	{
		Matrix result(n);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j)
				result(i,j) = generate_random_value();
		return std::move(result);
	}

	template <class Matrix,
						class RNG>
	Matrix
	RandomMatrixGenerator<Matrix, RNG>::operator()(const size_t rows,
																								 const size_t cols) const
	{
		Matrix result(rows, cols);
		for (size_t i = 0; i < rows; ++i)
			for (size_t j = 0; j < cols; ++j)
				result(i,j) = generate_random_value();
		return result;
	}

	template <class Matrix,
						class MatrixGenerator>
	Matrix&& generate_matrix(const size_t n) {
		static MatrixGenerator g;
		return std::move(g(n));
	}

	template <class Matrix,
						class MatrixGenerator>
	Matrix generate_matrix(const size_t rows, const size_t cols) {
		static MatrixGenerator g;
		return g(rows, cols);
	}

	template <class Matrix>
	Matrix&& random(const size_t n) {
		return std::move(generate_matrix<Matrix,
																		 RandomMatrixGenerator<Matrix> >(n));
	}

	template <class Matrix>
	Matrix random(const size_t rows, const size_t cols) {
		return generate_matrix<Matrix,
													 RandomMatrixGenerator<Matrix> >(rows, cols);
	}

	template <class Matrix>
	Matrix zeros(const size_t n) {
		return generate_matrix<Matrix,
													 ValueMatrixGenerator<Matrix, 0> >(n);
	}

	template <class Matrix>
	Matrix zeros(const size_t rows, const size_t cols) {
		return generate_matrix<Matrix,
													 ValueMatrixGenerator<Matrix, 0> >(rows, cols);
	}

	template <class Matrix>
	Matrix ones(const size_t n) {
		return generate_matrix<Matrix,
													 ValueMatrixGenerator<Matrix, 1> >(n);
	}

	template <class Matrix>
	Matrix ones(const size_t rows, const size_t cols) {
		return generate_matrix<Matrix,
													 ValueMatrixGenerator<Matrix, 1> >(rows, cols);
	}

	template <class Matrix>
	Matrix eye(const size_t n) {
		return generate_matrix<Matrix,
													 IdentityMatrixGenerator<Matrix> >(n);
	}

	template <class Matrix>
	Matrix eye(const size_t rows, const size_t cols) {
		return generate_matrix<Matrix,
													 IdentityMatrixGenerator<Matrix> >(rows, cols);
	}
}
