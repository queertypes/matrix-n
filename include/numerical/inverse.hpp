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
#ifndef NUMERICAL_INVERSE_HPP
#define NUMERICAL_INVERSE_HPP

namespace numerical {
  template <class Matrix,
            class InverseImplementationType = impl::GslInverseImplementation>
  class Inverse {
  public:
    typedef Matrix matrix_type;
    typedef InverseImplementationType inverse_implementation_type;

    matrix_type operator()(const matrix_type&);

  private:
    inverse_implementation_type _impl;
  };
} 

#include <implementation/inverse.cpp>

#endif
