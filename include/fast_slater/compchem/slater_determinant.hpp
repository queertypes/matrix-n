#ifndef FAST_SLATER_COMPCHEM_SLATER_DETERMINANT_HPP
#define FAST_SLATER_COMPCHEM_SLATER_DETERMINANT_HPP

namespace compchem {
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
    SlaterDeterminant(const SlaterDeterminant&) = default;
    SlaterDeterminant(SlaterDeterminant&&) = default;
    SlaterDeterminant& operator=(const SlaterDeterminant&) = default;

    matrix_type
    operator()(const matrix_type& D,
               const matrix_type& V,
               const size_t numSteps,
               const double threshold);
  private:
    slater_determinant_implementation_type _impl;
  };
}

#include <fast_slater/implementation/slater_determinant.cpp>

#endif
