#ifndef NUMERICAL_MATRIX_GENERATOR_HPP
#define NUMERICAL_MATRIX_GENERATOR_HPP

namespace numerical {

	template <class Matrix>
	class IdentityMatrixGenerator {
		Matrix operator()(const size_t n) const;
	};

	template <class Matrix, size_t Value>
	class ValueMatrixGenerator {
		Matrix operator()(const size_t n) const;
		Matrix operator()(const size_t rows, const size_t cols) const;
	};

	template <class Matrix>
	class RandomMatrixGenerator {
		Matrix operator()(const size_t n) const;
		Matrix operator()(const size_t rows, const size_t cols) const;
	};

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
