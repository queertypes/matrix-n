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
    along with Fast Slater.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef NUMERICAL_MATRIX_SERIAL_MATRIX_IMPLEMENTATION_HPP
#define NUMERICAL_MATRIX_SERIAL_MATRIX_IMPLEMENTATION_HPP

namespace numerical {
  namespace impl {

    template <class T,
              class Allocator = std::allocator<T> >
    class SerialMatrixImplementation {

    public:

      typedef T value_type;
      typedef Allocator allocator_type;

    public:

      explicit SerialMatrixImplementation(const size_t n);
      SerialMatrixImplementation(const size_t rows,
                                 const size_t cols);

      friend void swap(SerialMatrixImplementation& lhs,
                       SerialMatrixImplementation& rhs);

      SerialMatrixImplementation(const SerialMatrixImplementation&);
      SerialMatrixImplementation&
      operator=(const SerialMatrixImplementation&);

      SerialMatrixImplementation(SerialMatrixImplementation&&);
      SerialMatrixImplementation
      operator=(SerialMatrixImplementation&&);

      ~SerialMatrixImplementation();

      T& operator()(const size_t row, const size_t col);
      T& operator()(const size_t row, const size_t col) const;

      SerialMatrixImplementation&
      operator+=(const SerialMatrixImplementation&);
      SerialMatrixImplementation&
      operator-=(const SerialMatrixImplementation&);
      SerialMatrixImplementation&
      operator*=(const SerialMatrixImplementation&);

      SerialMatrixImplementation&
      operator+=(const T&);
      SerialMatrixImplementation&
      operator-=(const T&);
      SerialMatrixImplementation&
      operator*=(const T&);
      SerialMatrixImplementation&
      operator/=(const T&);

      T* data() const;
      size_t rows() const;
      size_t cols() const;
      constexpr allocator_type get_allocator() const;

    private:
      size_t _rows, _cols;
      T* _data;
      static allocator_type _allocator;
    };

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator-(const SerialMatrixImplementation<T, _Alloc>&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator+(const SerialMatrixImplementation<T, _Alloc>&,
              const SerialMatrixImplementation<T, _Alloc>&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator-(const SerialMatrixImplementation<T, _Alloc>&,
              const SerialMatrixImplementation<T, _Alloc>&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator*(const SerialMatrixImplementation<T, _Alloc>&,
              const SerialMatrixImplementation<T, _Alloc>&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator+(const SerialMatrixImplementation<T, _Alloc>&,
              const T&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator-(const SerialMatrixImplementation<T, _Alloc>&,
              const T&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator*(const SerialMatrixImplementation<T, _Alloc>&,
              const T&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator+(const T&,
              const SerialMatrixImplementation<T, _Alloc>&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator-(const T&,
              const SerialMatrixImplementation<T, _Alloc>&);

    template <class T,
              class _Alloc>
    SerialMatrixImplementation<T, _Alloc>
    operator*(const T&,
              const SerialMatrixImplementation<T, _Alloc>&);

    template <class T,
              class _Alloc>
    bool operator==(const SerialMatrixImplementation<T, _Alloc>&,
                    const SerialMatrixImplementation<T, _Alloc>&);

    template <class T,
              class _Alloc>
    bool operator!=(const SerialMatrixImplementation<T, _Alloc>&,
                    const SerialMatrixImplementation<T, _Alloc>&);
  }
}

#include <implementation/matrix/serial_matrix_implementation.cpp>

#endif
