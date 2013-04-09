#include <cmath>

namespace compchem {
  namespace impl {

    template <class _Mat,
              class _Det,
              class _Inv>
    _Mat
    JustUpdate<_Mat, _Det, _Inv>::operator()(const _Mat& D,
                                             const _Mat& V,
                                             const size_t numSteps,
                                             const double threshold)
    {
      _Det det;
      _Inv inv;

      _Mat D_after(D);
      _Mat D_curr(D);
      const size_t numElectrons = D.rows();
      size_t p = 0;
      size_t step = 0;

      while (step < numSteps) {
        p %= numElectrons;

        D_after.row(p) += V.row(step);
        const double R = det(D_after) / det(D_curr);

        if (abs(R) > threshold) {
          D_curr.row(p) = D_after.row(p);
          ++step;
        } else {
          D_after.row(p) = D_curr.row(p);
        }
        
        ++p;
      }

      return D_after;
    }
  }
}
