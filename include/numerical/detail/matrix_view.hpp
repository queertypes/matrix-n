#ifndef NUMERICAL_DETAIL_MATRIX_VIEW_HPP
#define NUMERICAL_DETAIL_MATRIX_VIEW_HPP

namespace numerical {
  namespace detail {
    template <class T, 
              template <class,class> class ViewImpl,
              class Allocator = std::allocator<T>>
      class RowView {
      public:
        
      private:
        ViewImpl _impl;
      };
  }
}
    
#endif
