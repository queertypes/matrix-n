/*
  Matrix N - generic matrix library offering compile-time implementation choices
  Copyright (C) 2012 Alejandro Cabrera

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MATRIX_N_NUMERICAL_DETERMINANT_HPP
#define MATRIX_N_NUMERICAL_DETERMINANT_HPP

namespace numerical {
  template <class Matrix,
            class DeterminantImpl>
  class Determinant {
  public:
    Determinant() = default;
    ~Determinant() = default;
    Determinant(const Determinant&) = delete;
    Determinant(Determinant&&) = delete;
    Determinant& operator=(Determinant) = delete;

    typedef Matrix matrix_type;
    typedef typename matrix_type::value_type value_type;
    typedef DeterminantImpl determinant_implementation_type;

    value_type operator()(const matrix_type&);

  private:
    determinant_implementation_type _impl;
  };
}

#include <matrix_n/implementation/determinant.cpp>

#endif
