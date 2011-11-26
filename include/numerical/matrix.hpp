#ifndef NUMERICAL_MATRIX_HPP
#define NUMERICAL_MATRIX_HPP

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

    Matrix(Matrix&& other);
    Matrix& operator=(Matrix&& other);
		
    Matrix& operator=(const Matrix& other);

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    Matrix& operator+=(const T other);
    Matrix& operator-=(const T other);
    Matrix& operator*=(const T other);

    T& operator()(const size_t row, const size_t col);
    T& operator()(const size_t row, const size_t col) const;

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

}

#include <implementation/matrix.cpp>

#endif
