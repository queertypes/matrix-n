#ifndef FAST_SLATER_COMPCHEM_SLATER_DETERMINANT_JUST_UPDATE_HPP
#define FAST_SLATER_COMPCHEM_SLATER_DETERMINANT_JUST_UPDATE_HPP

namespace compchem {
  namespace impl {

    template <class Matrix,
              class Determinant,
              class Inverse>
    struct JustUpdate {
      typedef Matrix matrix_type;
      typedef Determinant determinant_functor_type;
      typedef Inverse inverse_functor_type;

      matrix_type
      operator()(const matrix_type& D, const matrix_type& V,
                 const size_t numSteps, const double threshold);
    };
  }
}

#include <fast_slater/implementation/slater_determinant/just_update.cpp>

#endif
