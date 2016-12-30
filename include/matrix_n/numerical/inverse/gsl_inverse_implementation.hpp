/*
  Matrix N - generic matrix library offering compile-time implementation choices
  Copyright (C) 2016 Allele Dev

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
#ifndef MATRIX_N_NUMERICAL_INVERSE_GSL_INVERSE_IMPLEMENTATION_HPP
#define MATRIX_N_NUMERICAL_INVERSE_GSL_INVERSE_IMPLEMENTATION_HPP

namespace numerical {
  namespace impl {

    template <class Matrix>
    struct GslInverseImplementation {
      typedef Matrix matrix_type;

      matrix_type operator()(const matrix_type&);
    };
  }
}

#include <matrix_n/implementation/inverse/gsl_inverse_implementation.cpp>

#endif
