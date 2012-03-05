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
namespace qmc {
  template <class _Mat,
            class _Det,
            class _Inv,
            class _SlaterImpl>
  _Mat
  SlaterDeterminant<_Mat,
                    _Det,
                    _Inv,
                    _SlaterImpl>::operator()(const _Mat& D,
                                             const _Mat& V,
                                             const size_t numSteps,
                                             const double threshold)
  {
    return _impl(D, V, numSteps, threshold);
  }
}
