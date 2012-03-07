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
#ifndef NUMERICAL_DETAIL_MATRIX_IMPLEMENTATION_TRAITS_HPP
#define NUMERICAL_DETAIL_MATRIX_IMPLEMENTATION_TRAITS_HPP

namespace numerical {
  namespace impl {
    template <class T, class Alloc>
    class SerialMatrixImplementation;

    namespace detail {
      template <class T, class Alloc>
      class SerialRowViewImplementation;

      template <class T, class Alloc>
      class SerialColumnViewImplementation;
    }
  }
}

namespace detail {
  using namespace numerical::impl;

  template <class MatrixImplementation>
  struct MatrixImplementationTraits {
    static_assert(0,
                  "Matrix implementation type not found.\
                   Refer to <numerical/matrix/>.");
  };

  template <>
  struct MatrixImplementationTraits<SerialMatrixImplementation> {
    typedef SerialMatrixImplementation matrix_implementation_type;
    typedef detail::SerialRowViewImplementation row_view_implementation_type;
    typedef detail::SerialColumnViewImplementation column_view_implementation_type;
  };
}

#endif
