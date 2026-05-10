#include <cstddef>
#include <cmath>
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
MatrixProxy<T, Container> SquareMatrix<T, Container>::operator[](size_t row) {
    if (row >= size_) {
        throw IndexOutOfRangeException("SquareMatrix: operator[]. Индексы вне матрицы.");
    }
    return MatrixProxy<T, Container>(*this, row);
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
ConstMatrixProxy<T, Container> SquareMatrix<T, Container>::operator[](size_t row) const {
    if (row >= size_) {
        throw IndexOutOfRangeException("SquareMatrix: operator[]. Индексы вне матрицы.");
    }
    return ConstMatrixProxy<T, Container>(*this, row);
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container> SquareMatrix<T, Container>::add(const SquareMatrix<T, Container>& matrix) const {
    if (size_ != matrix.size_) {
        throw MatrixSizeMismatchException("SquareMatrix: add. Размеры матриц не совпадают");
    }

    SquareMatrix<T, Container> result(size_);
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            result[i][j] = (*this)[i][j] + matrix[i][j];
        }
    }
    return result;
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container> SquareMatrix<T, Container>::multiply_on_scalar(T scalar) const {
    SquareMatrix<T, Container> result(size_);
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            result[i][j] = (*this)[i][j] * scalar;
        }
    }
    return result;
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
double SquareMatrix<T, Container>::norm() const {
    double norm_squared = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            if constexpr(std::is_arithmetic_v<T>) {
                double value = static_cast<double>((*this)[i][j]);
                norm_squared += value * value;
            }
            else {
                norm_squared += static_cast<double>((*this)[i][j].absolute_squared());
            }
        }
    }
    return std::sqrt(norm_squared);
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container>& SquareMatrix<T, Container>::swap_rows(size_t row_1, size_t row_2) {
    if (row_1 >= size_ || row_2 >= size_) {
        throw IndexOutOfRangeException("SquareMatrix: swap_rows. Индексы строк вне матрицы.");
    }
    if (row_1 == row_2) {
        return *this;
    }

    for (size_t column = 0; column < size_; ++column) {
        T temp = (*this)[row_1][column];
        (*this)[row_1][column] = (*this)[row_2][column];
        (*this)[row_2][column] = temp;
    }
    return *this;
}

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
SquareMatrix<T, Container>& SquareMatrix<T, Container>::swap_columns(size_t col_1, size_t col_2) {
    if (col_1 >= size_ || col_2 >= size_) {
        throw IndexOutOfRangeException("SquareMatrix: swap_rows. Индексы строк вне матрицы.");
    }
    if (col_1 == col_2) {
        return *this;
    }

    for (size_t row = 0; row < size_; ++row) {
        T temp = (*this)[row][col_1];
        (*this)[row][col_1] = (*this)[row][col_2];
        (*this)[row][col_2] = temp;
    }
    return *this;
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

