namespace numerical {

	template <typename T,
						typename _Alloc>
	Matrix<T, _Alloc>::Matrix(const size_t n) 
		: _rows(n), _cols(n),
			_data(_allocator.allocate(n*n))
	{
		std::cout << "ctor\n";
	}
	
	template <typename T,
						typename _Alloc>
	Matrix<T, _Alloc>::Matrix(const size_t rows, const size_t cols) 
						: _rows(rows), _cols(cols),
						_data(_allocator.allocate(rows*cols))
	{
	}

	template <typename T,
						typename _Alloc>
	Matrix<T, _Alloc>&
	Matrix<T, _Alloc>::operator=(const Matrix& other)
	{
		std::cout << "copy ctor\n";
		_rows = other._rows;
		_cols = other._cols;
		_data = _allocator.allocate(_rows * _cols);

		for (size_t i = 0; i < _rows; ++i)
			for (size_t j = 0; j < _cols; ++j)
				*this(i,j) = other(i,j);

		return *this;
	}

	template <typename T,
						typename _Alloc>
	Matrix<T, _Alloc>::~Matrix()
	{
		std::cout << "dtor\n";
		_allocator.deallocate(_data, _rows * _cols);
	}

	template <typename T,
						typename _Alloc>
	Matrix<T, _Alloc>::Matrix(Matrix&& other)
	{
		std::cout << "move ctor\n";
		*this = std::move(other);
	}

	template <typename T,
						typename _Alloc>
	Matrix<T, _Alloc>& 
	Matrix<T, _Alloc>::operator=(Matrix&& other)
	{
		std::cout << "move =\n";
		std::swap(_rows, other._rows);
		std::swap(_cols, other._cols);
		std::swap(_data, other._data);

		return *this;
	}

	template <typename T,
						typename _Alloc>
	T& Matrix<T, 
					 _Alloc>::operator()(const size_t row, const size_t col) const
	{
		return _data[row * _cols + col];
	}

	template <typename T,
						typename _Alloc>
	T& Matrix<T, 
					 _Alloc>::operator()(const size_t row, const size_t col)
	{
		return _data[row * _cols + col];
	}

	template <typename T,
						typename _Alloc>
	T* Matrix<T, _Alloc>::data() const
	{
		return _data;
	}

	template <typename T,
						typename _Alloc>
	size_t Matrix<T, _Alloc>::rows() const
	{
		return _rows;
	}


	template <typename T,
						typename _Alloc>
	size_t Matrix<T, _Alloc>::cols() const
	{
		return _cols;
	}

	template <typename T,
						typename _Alloc>
	constexpr _Alloc 
	Matrix<T, _Alloc>::get_allocator() const
	{
		return _allocator;
	}
}
