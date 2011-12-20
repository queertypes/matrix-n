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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <cassert>

namespace numerical {

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>::Matrix(const size_t n) 
    : _rows(n), _cols(n),
      _data(_allocator.allocate(n*n))
  {
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>::Matrix(const size_t rows, const size_t cols) 
            : _rows(rows), _cols(cols),
            _data(_allocator.allocate(rows*cols))
  {
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>::Matrix(const Matrix& other)
    : _rows(other._rows), _cols(other._cols),
      _data(_allocator.allocate(_rows*_cols))
  {
    memcpy(_data, other._data, _rows * _cols * sizeof(T));
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>&
  Matrix<T, _Alloc>::operator=(const Matrix& other)
  {
    _rows = other._rows;
    _cols = other._cols;
    _data = _allocator.allocate(_rows * _cols);

    for (size_t i = 0; i < _rows; ++i)
      for (size_t j = 0; j < _cols; ++j)
        (*this)(i,j) = other(i,j);

    return *this;
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>::~Matrix()
  {
    _allocator.deallocate(_data, _rows * _cols);
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>::Matrix(Matrix&& other)
  {
    *this = std::move(other);
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>& 
  Matrix<T, _Alloc>::operator=(Matrix&& other)
  {
    this->_rows = other._rows;
    this->_cols = other._cols;
    this->_data = other._data; 
    other._rows = 0;
    other._cols = 0;
    other._data = nullptr;

    return *this;
  }

  template <typename T,
            typename _Alloc>
  T& Matrix<T, 
           _Alloc>::operator()(const size_t row, const size_t col) const
  {
    return _data[row * _cols + col];
  }

  template <typename T,
            typename _Alloc>
  T& Matrix<T, 
           _Alloc>::operator()(const size_t row, const size_t col)
  {
    return _data[row * _cols + col];
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>&
  Matrix<T, _Alloc>::operator+=(const Matrix& other) 
  {
    assert(this->rows() == other.rows());
    assert(this->cols() == other.cols());

    for (size_t i = 0; i < _rows; ++i)
      for (size_t j = 0; j < _cols; ++j)
        (*this)(i,j) += other(i,j);

    return *this;
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>&
  Matrix<T, _Alloc>::operator-=(const Matrix& other) 
  {
    assert(this->rows() == other.rows());
    assert(this->cols() == other.cols());

    for (size_t i = 0; i < _rows; ++i)
      for (size_t j = 0; j < _cols; ++j)
        (*this)(i,j) -= other(i,j);

    return *this;
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>&
  Matrix<T, _Alloc>::operator*=(const Matrix& other) 
  {
    assert(this->cols() == other.rows());
    Matrix result(_rows, other._cols);

    for (size_t i = 0; i < _rows; ++i)
      for (size_t j = 0; j < _cols; ++j)
        for (size_t k = 0; k < _cols; ++k)
          result(i,j) += (*this)(i,k) * other(k,j);

    *this = result;
    
    return *this;
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>&
  Matrix<T, _Alloc>::operator+=(const T& other)
  {
    for (size_t i = 0; i < _rows; ++i)
      for (size_t j = 0; j < _cols; ++j)
        (*this)(i,j) += other;

    return *this;
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>&
  Matrix<T, _Alloc>::operator-=(const T& other) 
  {
    for (size_t i = 0; i < _rows; ++i)
      for (size_t j = 0; j < _cols; ++j)
        (*this)(i,j) -= other;

    return *this;
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>&
  Matrix<T, _Alloc>::operator*=(const T& other) 
  {
    for (size_t i = 0; i < _rows; ++i)
      for (size_t j = 0; j < _cols; ++j)
        (*this)(i,j) *= other;

    return *this;
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc>&
  Matrix<T, _Alloc>::operator/=(const T& other) 
  {
    for (size_t i = 0; i < _rows; ++i)
      for (size_t j = 0; j < _cols; ++j)
        (*this)(i,j) /= other;

    return *this;
  }

  template <typename T,
            typename _Alloc>
  T* Matrix<T, _Alloc>::data() const
  {
    return _data;
  }

  template <typename T,
            typename _Alloc>
  size_t Matrix<T, _Alloc>::rows() const
  {
    return _rows;
  }

  template <typename T,
            typename _Alloc>
  size_t Matrix<T, _Alloc>::cols() const
  {
    return _cols;
  }

  template <typename T,
            typename _Alloc>
  constexpr _Alloc 
  Matrix<T, _Alloc>::get_allocator() const
  {
    return _allocator;
  }

  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator+(const Matrix<T, _Alloc>& lhs,
            const Matrix<T, _Alloc>& rhs)
  {
    Matrix<T, _Alloc> result(lhs);
    return (result += rhs);
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator-(const Matrix<T, _Alloc>& lhs,
            const Matrix<T, _Alloc>& rhs)
  {
    Matrix<T, _Alloc> result(lhs);
    return (result -= rhs);
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator*(const Matrix<T, _Alloc>& lhs,
            const Matrix<T, _Alloc>& rhs)
  {
    Matrix<T, _Alloc> result(lhs);
    return (result *= rhs);
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator+(const Matrix<T, _Alloc>& lhs,
            const T& rhs)
  {
    Matrix<T, _Alloc> result(lhs);
    return (result += rhs);
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator-(const Matrix<T, _Alloc>& lhs,
            const T& rhs)
  {
    Matrix<T, _Alloc> result(lhs);
    return (result -= rhs);
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator*(const Matrix<T, _Alloc>& lhs,
            const T& rhs)
  {
    Matrix<T, _Alloc> result(lhs);
    return (result *= rhs);
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator+(const T& lhs,
            const Matrix<T, _Alloc>& rhs)
  {
    Matrix<T, _Alloc> result(rhs);
    for (size_t i = 0; i < result.rows(); ++i)
      for (size_t j = 0; j < result.cols(); ++j)
        result(i,j) = lhs + result(i,j);

    return result;
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator-(const T& lhs,
            const Matrix<T, _Alloc>& rhs)
  {
    Matrix<T, _Alloc> result(rhs);
    for (size_t i = 0; i < result.rows(); ++i)
      for (size_t j = 0; j < result.cols(); ++j)
        result(i,j) = lhs - result(i,j);

    return result;
  }
  
  template <typename T,
            typename _Alloc>
  Matrix<T, _Alloc> 
  operator*(const T& lhs,
            const Matrix<T, _Alloc>& rhs)
  {
    Matrix<T, _Alloc> result(rhs);
    for (size_t i = 0; i < result.rows(); ++i)
      for (size_t j = 0; j < result.cols(); ++j)
        result(i,j) = lhs * result(i,j);

    return result;
  } 

  template <typename T,
            typename _Alloc>
  bool
  operator==(const Matrix<T, _Alloc>& lhs,
             const Matrix<T, _Alloc>& rhs)
  {
    if (lhs.rows() != rhs.rows()) return false;
    if (lhs.cols() != rhs.cols()) return false;
    
    return memcmp(lhs.data(), rhs.data(), 
                  lhs.rows() * lhs.cols() * sizeof(T)) == 0;
  }

  template <typename T,
            typename _Alloc>
  bool
  operator!=(const Matrix<T, _Alloc>& lhs,
             const Matrix<T, _Alloc>& rhs)
  {
    return !(lhs == rhs);
  } 
}
