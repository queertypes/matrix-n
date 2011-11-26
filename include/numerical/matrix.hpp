#ifndef NUMERICAL_MATRIX_HPP
#define NUMERICAL_MATRIX_HPP

#include <config.h>

namespace numerical {

  template <typename T,
            typename Allocator = std::allocator<T> >
  class Matrix {
  public:
    typedef T value_type;
    typedef Allocator allocator_type;

  public:
    Matrix(const size_t n);
    Matrix(const size_t rows, const size_t cols);
    Matrix(const Matrix& other);
    ~Matrix();

#ifdef HAS_MOVE_CONSTRUCTOR
    Matrix(Matrix&& other);
#endif

#ifdef HAS_MOVE_ASSIGNMENT
    Matrix& operator=(Matrix&& other);
#endif
		
    Matrix& operator=(const Matrix& other);

    T& operator()(const size_t row, const size_t col);
    T& operator()(const size_t row, const size_t col) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    Matrix& operator+=(const T& other);
    Matrix& operator-=(const T& other);
    Matrix& operator*=(const T& other);
    Matrix& operator/=(const T& other);

  public:
    T* data() const;
    size_t rows() const;
    size_t cols() const;
    constexpr allocator_type get_allocator() const;

  private:
    size_t _rows, _cols;
    T* _data;
    static allocator_type _allocator;
  };

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator+(const Matrix<T, _Alloc>&, 
															const Matrix<T, _Alloc>&);

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator-(const Matrix<T, _Alloc>&, 
															const Matrix<T, _Alloc>&);

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator*(const Matrix<T, _Alloc>&, 
															const Matrix<T, _Alloc>&);

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator+(const Matrix<T, _Alloc>&, 
															const T&);

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator-(const Matrix<T, _Alloc>&, 
															const T&);

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator*(const Matrix<T, _Alloc>&, 
															const T&);

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator+(const T&, 
															const Matrix<T, _Alloc>&);

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator-(const T&, 
															const Matrix<T, _Alloc>&);

	template <typename T,
						class _Alloc>
	Matrix<T, _Alloc> operator*(const T&, 
															const Matrix<T, _Alloc>&);

	template <typename T,
						class _Alloc>
	bool operator==(const Matrix<T, _Alloc>&,
									const Matrix<T, _Alloc>&);

	template <typename T,
						class _Alloc>
	bool operator!=(const Matrix<T, _Alloc>&,
									const Matrix<T, _Alloc>&);	
}

#include <implementation/matrix.cpp>

#endif
