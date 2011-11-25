#ifndef NUMERICAL_MATRIX_HPP
#define NUMERICAL_MATRIX_HPP

namespace numerical {

  template <typename T,
            typename OuterAllocator = std::allocator<T*>,
            typename InnerAllocator = std::allocator<T> >
  class Matrix {
  public:
    typedef T value_type;
    typedef OuterAllocator outer_allocator_type;
    typedef InnerAllocator inner_allocator_type;

  public:
    Matrix(const size_t n);
    Matrix(const size_t rows, const size_t cols);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix(const Matrix&& other);
    Matrix& operator=(const Matrix&& other);
    
    Matrix& operator=(const Matrix& other);

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    Matrix& operator+=(const T other);
    Matrix& operator-=(const T other);
    Matrix& operator*=(const T other);

    T operator()(const size_t row, const size_t col);
    T operator()(const size_t row, const size_t col) const;

  public:
    T** data() const;
    size_t rows() const;
    size_t cols() const;
    constexpr outer_allocator_type get_outer_allocator() const;
		constexpr inner_allocator_type get_inner_allocator() const;

  private:
    size_t _rows, _cols;
    T** _data;
    static outer_allocator_type _outer_allocator;
    static inner_allocator_type _inner_allocator;
  };

}

#include <implementation/matrix.cpp>

#endif
