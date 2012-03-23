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
#ifndef QMC_SLATER_JUST_UPDATE_SLATER_HPP
#define QMC_SLATER_JUST_UPDATE_SLATER_HPP

namespace qmc {
  namespace impl {

    template <class Matrix,
              class Determinant,
              class Inverse>
    struct JustUpdateSlaterDeterminantImplementation {
      typedef Matrix matrix_type;
      typedef Determinant determinant_functor_type;
      typedef Inverse inverse_functor_type;

      matrix_type
      operator()(const matrix_type& D, const matrix_type& V,
                 const size_t numSteps, const double threshold);
    };
  }
}

#include <implementation/slater/just_update_slater.cpp>

#endif
