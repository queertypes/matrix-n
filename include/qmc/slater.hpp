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
#ifndef QMC_SLATER_HPP
#define QMC_SLATER_HPP

namespace qmc {
  template <class Matrix,
            class Determinant,
            class Inverse,
            class SlaterDeterminantImplementation>
  class SlaterDeterminant {
  public:

    typedef Matrix matrix_type;
    typedef Determinant determinant_functor_type;
    typedef Inverse inverse_functor_type;
    typedef SlaterDeterminantImplementation
            slater_determinant_implementation_type;

    SlaterDeterminant() = default;
    ~SlaterDeterminant() = default;
    SlaterDeterminant(const SlaterDeterminant&) = delete;
    SlaterDeterminant(SlaterDeterminant&&) = delete;
    SlaterDeterminant& operator=(SlaterDeterminant) = delete;

    matrix_type
    operator()(const matrix_type& D,
               const matrix_type& V,
               const size_t numSteps,
               const double threshold);
  private:
    slater_determinant_implementation_type _impl;
  };
}

#include <implementation/slater.cpp>

#endif
