namespace compchem {
  namespace impl {

    template <class _Mat,
              class _Det,
              class _Inv>
    _Mat
    ShermanMorrison<_Mat, _Det, _Inv>::operator()(const _Mat& D,
                                                  const _Mat& V,
                                                  const size_t numSteps,
                                                  const double threshold)
    {
      _Det det;
      _Inv inv;

      const size_t numElectrons = D.rows();
      size_t p = 0;
      size_t step = 0;

      _Mat iD = inv(D);

      while (step < numSteps) {
        p %= numElectrons;
        
        //_Mat Vrow(1, V.cols());
        //_Mat iDcol(D.rows(), 1);

        //Vrow.row(0) = V.row(step);
        //iDcol.col(0) = iD.col(p);

        const double R = (1.0d + (V.row(step) * iD.col(p)))(0,0);
        
        if (abs(R) > threshold) {
          iD -= ((iD.col(p) * (V.row(step) * iD)) / R);
          ++step;
        }

        ++p;
      }

      return iD;
    }
  }
}
