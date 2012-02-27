#ifndef NUMERICAL_DETAIL_SERIAL_MATRIX_IMPLEMENTATION_HPP
#define NUMERICAL_DETAIL_SERIAL_MATRIX_IMPLEMENTATION_HPP

namespace numerical {
	namespace impl {
		
		template <class T,
							class Allocator = std::allocator<T> >
		class SerialMatrixImplementation {

    public:
      
			typedef T value_type;
			typedef Allocator allocator_type;
      
		public:

			explicit SerialMatrixImplementation(const size_t n);

		private:
			size_t _rows, _cols;
			T* _data;
			static allocator_type _allocator;
		};
	}
}
#endif
