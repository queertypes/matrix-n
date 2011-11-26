#ifndef NUMERICAL_MATRIX_GENERATOR_HPP
#define NUMERICAL_MATRIX_GENERATOR_HPP

#include <random>

namespace numerical {

	template <class Matrix>
	struct IdentityMatrixGenerator {
		Matrix operator()(const size_t n) const;
		Matrix operator()(const size_t rows, const size_t cols) const;
											
	};

	template <class Matrix, size_t Value>
	struct ValueMatrixGenerator {
		Matrix operator()(const size_t n) const;
		Matrix operator()(const size_t rows, const size_t cols) const;
	};

	template <class Matrix,
						class RandomNumberGenerator = std::mt19937>
	class RandomMatrixGenerator {
	public:
		typedef typename Matrix::value_type value_type;
	public:
		Matrix&& operator()(const size_t n) const;
		Matrix operator()(const size_t rows, const size_t cols) const;

	private:
		value_type generate_random_value() const;
	private:
		mutable RandomNumberGenerator generator;
	};

	template <class Matrix,
						class MatrixGenerator>
	Matrix&& generate_matrix(const size_t n);

	template <class Matrix,
						class MatrixGenerator>
	Matrix generate_matrix(const size_t rows, const size_t cols);

	template <class Matrix>
	Matrix&& random(const size_t n);

	template <class Matrix>
	Matrix random(const size_t rows, const size_t cols);

	template <class Matrix>
	Matrix zeros(const size_t n);

	template <class Matrix>
	Matrix zeros(const size_t rows, const size_t cols);

	template <class Matrix>
	Matrix ones(const size_t n);

	template <class Matrix>
	Matrix ones(const size_t rows, const size_t cols);

	template <class Matrix>
	Matrix eye(const size_t n);
	
	template <class Matrix>
	Matrix eye(const size_t rows, const size_t cols);
}

#include <implementation/matrix_generator.cpp>

#endif
