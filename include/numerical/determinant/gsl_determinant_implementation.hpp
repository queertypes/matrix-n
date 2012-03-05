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
#ifndef NUMERICAL_DETERMINANT_GSL_DETERMINANT_IMPLEMENTATION_HPP
#define NUMERICAL_DETERMINANT_GSL_DETERMINANT_IMPLEMENTATION_HPP

namespace numerical {
  namespace impl {

    template <class Matrix>
    struct GslDeterminantImplementation {
      typedef Matrix matrix_type;
      typedef typename matrix_type::value_type value_type;

      value_type operator()(const matrix_type&);
    };
  }
}

#include <implementation/determinant/gsl_determinant_implementation.cpp>

#endif
