/**
 * Current considerations:
 *
 * 1. Should Matrix._impl._data be a unique_ptr or a shared pointer?
 *   Using the unique_ptr approach is more efficient. However, there is
 *   a danger of having a dangling view.
 *
 *   Using a shared_ptr is less efficient, but by having the views be
 *   implemented using weak_ptr, there can be no dangling.
 */

/**
 * To-do (March 9. 2012):
 * 1. Update Matrix interface to use initializer lists and range
 *    construction.
 * 2. Update View interfaces to take a single template parameter
 *    and be implemented as described below.
 * 3. Test View implementations.
 */

/** Begin notes **/
/* interface level */

// matrix.hpp
template <class T, template <class,class> class MImpl, class Alloc>
class Matrix;

// various matrix implementations in matrix/*

// detail/matrix_view.hpp
template <class T>
class RowView;

template <class T>
class ColumnView;

/**
   No need to support RowView * ColumnView and ColumnView * RowView.
   Just have user convert RowView/ColumnView to Matrix to perform
   operation.

   This eliminates the need to have different implementations
   for views without sacrificing performance. Also, this eliminates
   the coupling created by MatrixTraits.

   Also, by using stl algorithms, it is possible to forward the
   parallelization effort to the underlying STL implementation
   for assigment operations.
   op= -> std::copy
*/

// supported operations
template <class T>
class RowView {
public:
  typedef T value_type;

  typedef T* iterator;
  typedef const T* const const_iterator;
  typedef std::random_access_iterator_tag iterator_category;

  RowView() = default;
  RowView(const RowView&) = default;
  RowView(RowView&&) = default;
  ~RowView() = default;
  RowView& operator=(RowView) = default;

  RowView(iterator begin, const size_t cols);

  iterator begin() const;
  const_iterator cbegin() const;
  iterator end() const;
  const_iterator cend() const;

  iterator data() const;

  value_type operator()(const size_t idx) const;

  RowView& operator+=(const RowView&);
  RowView& operator-=(const RowView&);

private:
  iterator _data;
};

RowView operator+(const RowView&, const RowView&);
RowView operator-(const RowView&, const RowView&);

template <class T>
class ColumnView {
public:
  typedef T value_type;
  typedef T* pointer;

  typedef ColumnIterator iterator;
  typedef const ColumnIterator const_iterator;

  ColumnView() = default;
  ColumnView(const ColumnView&) = default;
  ColumnView(ColumnView&&) = default;
  ColumnView& operator=(ColumnView) = default;
  ~ColumnView() = default;

  ColumnView(iterator begin,
             const size_t rows, const size_t cols);

  iterator begin() const;
  const_iterator cbegin() const;
  iterator end() const;
  const_iterator cend() const;

  pointer data() const;

  value_type operator()(const size_t idx) const;

  ColumnView& operator+=(const ColumnView&);
  ColumnView& operator-=(const ColumnView&);

  template <class T>
  struct ColumnIterator {

    typedef ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    ColumnIterator() = default;
    ColumnIterator(pointer begin,
                   const size_t rows, const size_t cols);
    ColumnIterator(const ColumnIterator&) = default;
    ColumnIterator(ColumnIterator&&) = default;
    ~ColumnIterator() = default;

    ColumnIterator& operator++() {
      return _data += _cols;
    }
    ColumnIterator& operator++(int);
    ColumnIterator& operator--();
    ColumnIterator& operator--(int);

    reference operator*() const;
    pointer operator->() const;

    size_t _cols; // how much to jump by
    pointer _data;
  };

private:
  ColumnIterator<value_type> _data;
};

ColumnView operator+(const ColumnView&, const ColumnView&);
ColumnView operator-(const ColumnView&, const ColumnView&);
