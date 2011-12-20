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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <cstdio>
#include <iostream>
#include <numerical/matrix.hpp>
#include <numerical/matrix_generator.hpp>
using namespace std;
using namespace numerical;

void parse_args(const int argc, const char *const *const argv,
                size_t &n, size_t &m)
{
  if (argc != 3) {
     fprintf(stderr, "usage: %s <num_electrons> <num_steps>\n", argv[0]);
     return;
  }

  if (sscanf(argv[1], "%u", &n) != 1) {
    fprintf(stderr, "error: converting arg %s to integer failed.\n", argv[1]);
    return;
  }

  if (sscanf(argv[2], "%u", &m) != 1) {
    fprintf(stderr, "error: converting arg %s to integer failed.\n", argv[2]);
    return;
  }
}

int main(int argc, char **argv)
{
  size_t n = 0 , m = 0;

  parse_args(argc, argv, n, m);

  if ( (n == 0) || (m == 0) ) {
    fprintf(stderr, "error: parsing arguments failed. Aborting.\n");
    return 1;
  }

  printf("Running simultaion with %u electrons for %u steps\n", n, m);
	Matrix<float> D = random<Matrix<float> >(n);
	//Matrix<float> v = random<Matrix<float> >(1, n);

	cout << D.rows() << " " << D.cols() << endl;

	/*
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			cout << D(i,j) << " ";
		}
		cout << "\n";
	}
	*/

	/*
	cout << "\n";
	for (size_t i = 0; i < n; ++i)
		cout << v(0,i) << " ";
	cout << "\n";
	*/

  return 0;
}
