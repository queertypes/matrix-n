#ifndef FAST_SLATER_COMPCHEM_SLATER_DETERMINANT_NUKALA_KENT_HPP
#define FAST_SLATER_COMPCHEM_SLATER_DETERMINANT_NUKALA_KENT_HPP

namespace compchem {
  namespace impl {

    template <class Matrix, class Determinant, class Inverse>
    class NukalaKent {
      typedef Matrix matrix_type;
      typedef Determinant determinant_functor_type;
      typedef Inverse inverse_functor_type;

      matrix_type
      operator()(const matrix_type& D, const matrix_type& V,
                 const size_t numSteps, const double threshold);
    };
  }
}

#include <fast_slater/implementation/slater_determinant/nukala_kent.cpp>

#endif
