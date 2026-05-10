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

