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
namespace numerical {
  
  template <class _Mat, class _Impl>
  typename _Mat::value_type
  Determinant<_Mat, _Impl>::operator()(const _Mat& m)
  {
    return _impl(m);
  }
}
