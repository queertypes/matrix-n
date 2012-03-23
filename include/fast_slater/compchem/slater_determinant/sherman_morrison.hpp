 /*
    Fast Slater - algorithms for the computation of Slater determinants.
    Copyright (C) Alejandro Cabrera 2012

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
#ifndef FAST_SLATER_COMPCHEM_SLATER_DETERMINANT_SHERMAN_MORRISON_HPP
#define FAST_SLATER_COMPCHEM_SLATER_DETERMINANT_SHERMAN_MORRISON_HPP

namespace compchem {
  namespace impl {

    template <class Matrix, class Determinant, class Inverse>
    struct ShermanMorrison {
      typedef Matrix matrix_type;
      typedef Determinant determinant_functor_type;
      typedef Inverse inverse_functor_type;

      matrix_type
      operator()(const matrix_type& D, const matrix_type& V,
                 const size_t numSteps, const double threshold);
    };
  }
}

#include <fast_slater/implementation/slater_determinant/sherman_morrison.cpp>

#endif
