#ifndef NUMERICAL_MATRIX_GENERATOR_HPP
#define NUMERICAL_MATRIX_GENERATOR_HPP

namespace numerical {

	template <class Matrix>
	Matrix eye(const size_t n);

	template <class Matrix>
	Matrix ones(const size_t n);

	template <class Matrix>
	Matrix ones(const size_t rows, const size_t cols);

	template <class Matrix>
	Matrix zeros(const size_t n);

	template <class Matrix>
	Matrix zeros(const size_t rows, const size_t cols);

	template <class Matrix>
	Matrix random(const size_t n);

	template <class Matrix>
	Matrix random(const size_t rows, const size_t cols);

	template <typename T,
						typename Matrix,
						typename Generator>
	class MatrixGenerator {
		void generate(Matrix &);
	};
}

#endif
