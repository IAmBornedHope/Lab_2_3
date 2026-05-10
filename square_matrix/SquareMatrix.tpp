#include <cstddef>
#include "SquareMatrix.hpp"

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container>::SquareMatrix() : items_{new Container<T>()}, size_{0} {}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container>::SquareMatrix(size_t size) : items_{new Container<T>()}, size_{size} {
    for (size_t counter = 0; counter < size * size; ++counter) {
        items_->append(T{});
    }
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container>::SquareMatrix(const SquareMatrix<T, Container>& matrix) :
    items_{new Container<T>(*matrix.items_)}, size_{matrix.size_} {}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container>& SquareMatrix<T, Container>::operator=(const SquareMatrix<T, Container>& matrix) {
    if (this != &matrix) {
        delete items_;
        size_ = matrix.size_;
        items_ = new Container<T>(*matrix.items_);
    }
    return *this;
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container>::~SquareMatrix() {
    delete items_;
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
T& SquareMatrix<T, Container>::get(size_t row, size_t column) {
    if (row >= size_ || column >= size_) {
        throw IndexOutOfRangeException("SquareMatrix: get. Индексы вне матрицы");
    }
    return items_->get_reference(row * size_ + column);
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
const T& SquareMatrix<T, Container>::get(size_t row, size_t column) const {
    if (row >= size_ || column >= size_) {
        throw IndexOutOfRangeException("SquareMatrix: get. Индексы вне матрицы");
    }
    return items_->get_reference(row * size_ + column);
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
size_t SquareMatrix<T, Container>::get_size() const {
    return size_;
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
void SquareMatrix<T, Container>::set(size_t row, size_t column, const T& value) {
    if (row >= size_ || column >= size_) {
        throw IndexOutOfRangeException("SquareMatrix: set. Индексы вне матрицы");
    }
    items_->set(row * size_ + column, value);
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
auto SquareMatrix<T, Container>::begin() {
    return items_->begin();
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
auto SquareMatrix<T, Container>::begin() const {
    return items_->begin();
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
auto SquareMatrix<T, Container>::end() {
    return items_->end();
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
auto SquareMatrix<T, Container>::end() const {
    return items_->end();
}

