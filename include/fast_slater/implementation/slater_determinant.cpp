namespace compchem {

  template <class _Mat,
            class _Det,
            class _Inv,
            class _Impl>
  _Mat
  SlaterDeterminant<_Mat, _Det,
                    _Inv, _Impl>::operator()(const _Mat& D,
                                             const _Mat& V,
                                             const size_t numSteps,
                                             const double threshold)
  {
    return _impl(D, V, numSteps, threshold);
  }
}
