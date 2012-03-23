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
namespace compchem {
  namespace impl {

    template <class _Mat,
              class _Det,
              class _Inv>
    _Mat
    JustUpdateSlaterDeterminantImplementation<_Mat,
      _Det,
      _Inv>::operator()(const _Mat& D,
                        const _Mat& V,
                        const size_t numSteps,
                        const double threshold)
    {
      _Det det;
      _Inv inv;

      _Mat result{D};
      _Mat D_curr{D};
      const size_t numElectrons = D.rows();
      size_t p = 0;
      size_t step = 1;

      while (step < numSteps) {
        p = (++p % numElectrons);

        //result(p,:) += V(step, :);
        //result.row(p) += V.row(step);
        for (size_t i = 0; i < result.cols(); ++i)
          result(p,i) = V(step, i);

        const double R = det(result) / det(D_curr);

        if (abs(R) > threshold) {
          //D_curr(p,:) = result(p,:);
          //D_curr.row(p) = result.row(p);
          for (size_t i = 0; i < D_curr.cols(); ++i)
            D_curr(p,i) = result(p,i);

          ++step;
        } else {
          //result(p,:) = D_curr(p,:);
          //result.row(p) = D_curr.row(p);
          for (size_t i = 0; i < D_curr.cols(); ++i)
            result(p,i) = D_curr(p,i);
        }
      }

      return result;
    }
  }
}
