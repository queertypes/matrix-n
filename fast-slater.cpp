#include <cstdio>
#include <iostream>
#include <sstream>
#include <random>
#include <numeric>
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

template <typename T>
T generate_value()
{
	static mt19937 generator;

	return static_cast<T>(generator()) / numeric_limits<T>::max();
}

template <typename T>
T** generate_random_matrix(const size_t n)
{
	T** D;

	D = new T*[n];
	for (size_t i = 0; i < n; ++i)
		D[i] = new T[n];

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			D[i][j] = generate_value<T>();

	return D;
}

template <typename T>
void free_matrix(T** D, const size_t n)
{
	for (size_t i = 0; i < n; ++i)
		delete[] D[i];
	delete[] D;
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
	//D = std::move(generate_random_matrix<float>(n));
	Matrix<float> D = random(n);

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			//cout << D(i,j) << " ";
		}
		//cout << "\n";
	}

  return 0;
}
