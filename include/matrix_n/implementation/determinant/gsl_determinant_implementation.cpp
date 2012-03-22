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
#include <gsl/gsl_linalg.h>

namespace numerical {
  namespace impl {

    template <class _Mat>
    typename _Mat::value_type
    det(const gsl_matrix& m)
    {
      int signum;
      double determinant = 0;

      gsl_matrix *tmp = gsl_matrix_alloc(m.size1, m.size2);
      gsl_permutation *p = gsl_permutation_alloc(m.size1);

      gsl_matrix_memcpy(tmp, &m);

      gsl_linalg_LU_decomp(tmp, p, &signum);
      determinant = gsl_linalg_LU_det(tmp, signum);

      gsl_permutation_free(p);
      gsl_matrix_free(tmp);

      return determinant;
    }

    template <class _Mat>
    typename _Mat::value_type
    GslDeterminantImplementation<_Mat>::operator()(const _Mat& m)
    {
      const gsl_matrix_view view = gsl_matrix_view_array(m.data(), m.rows(), m.cols());

      return det<_Mat>(view.matrix);
    }
  }
}
