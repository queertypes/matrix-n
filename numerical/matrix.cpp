namespace numerical {

	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	Matrix<T, _OutAlloc, _InAlloc>::Matrix(const size_t n) 
		: _rows(n), _cols(n),
			_data(_outer_allocator.allocate(n))
	{
		for (size_t i = 0; i < n; ++i)
			_data[i] = _inner_allocator.allocate(n);
	}
	
	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	Matrix<T, _OutAlloc, _InAlloc>::Matrix(const size_t rows, const size_t cols) 
						: _rows(rows), _cols(cols),
						_data(_outer_allocator.allocate(rows))
	{
		for (size_t i = 0; i < rows; ++i)
			_data[i] = _inner_allocator.allocate(cols);
	}

	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	Matrix<T, _OutAlloc, _InAlloc>::~Matrix()
	{
		for (size_t i = 0; i < _rows; ++i)
			_inner_allocator.deallocate(_data[i], _cols);
		_outer_allocator.deallocate(_data, _rows);
	}

	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	T Matrix<T, 
					 _OutAlloc, 
					 _InAlloc>::operator()(const size_t row, const size_t col) const
	{
		return _data[row][col];
	}

	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	T Matrix<T, 
					 _OutAlloc, 
					 _InAlloc>::operator()(const size_t row, const size_t col)
	{
		return _data[row][col];
	}

	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	T** Matrix<T, _OutAlloc, _InAlloc>::data() const
	{
		return _data;
	}

	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	size_t Matrix<T, _OutAlloc, _InAlloc>::rows() const
	{
		return _rows;
	}


	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	size_t Matrix<T, _OutAlloc, _InAlloc>::cols() const
	{
		return _cols;
	}

	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	_OutAlloc Matrix<T, _OutAlloc, _InAlloc>::get_outer_allocator() constexpr
	{
		return _outer_allocator;
	}
	
	template <typename T,
						typename _OutAlloc,
						typename _InAlloc>
	_InAlloc Matrix<T, _OutAlloc, _InAlloc>::get_inner_allocator() constexpr
	{
		return _inner_allocator;
	}	
}
