#include <cstdio>
#include <iostream>
#include <numerical/matrix.hpp>
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
	//Matrix<float> D = numerical::random(n);

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			//cout << D(i,j) << " ";
		}
		//cout << "\n";
	}

  return 0;
}
