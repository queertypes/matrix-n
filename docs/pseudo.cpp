template <typename T>
T fast_slater(const Matrix<T>& D,
							const Matrix<T>& v,
							const size_t n,
							const size_t num_steps)
{	
	return recursive_slater(D, v, zeros<T>(n,1), 0.0f, 
													n, num_steps, 0);
}

template <typename T>
T recursive_slater(const Matrix<T>& D,
									 const Matrix<T>& v,
									 const Matrix<T>& u,
									 const T* gamma,
									 const size_t n,
									 const size_t num_steps,
									 const size_t k)
{
	Matrix<T> e = zeros(n,1);
	e( k % e.rows() , 0) = 1;
	
	u[k] = inv(D) * e;
	for (size_t i = 0; i < k; ++i) {
		u[k] = u[k] - gamma[i] (transpose(v[i]) * u[k]) * u[i];
	}
	R[k] = 1 + transpose(v[k]) * u[k];
	if (R[k] > threshold) {
		gamma[k] = 1 / R[k];
		++k;
	}
	recursive_slater(D, v, u, gamma, n, num_steps, k);
}

