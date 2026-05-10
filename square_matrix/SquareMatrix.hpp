#pragma once
#include <concepts>
#include "../array_sequence/MutableArraySequence.hpp"
#include "../sequence/Sequence.hpp"

template<typename Container, typename T>
concept Matrixable = requires(Container& container, T value, size_t index) {
    { container.append(value) };
    { container.set(index, value) };
    { container.get_reference(index) };
    { container.get_length() } -> std::convertible_to<size_t>;
};

template<typename T, template<typename> class Container>
requires Matrixable<Container<T>, T>
class SquareMatrix {
private:
    Container<T>* items_;
    size_t size_;
public:
    SquareMatrix();
    SquareMatrix(size_t size);
    SquareMatrix(const SquareMatrix<T, Container>& matrix);
    SquareMatrix<T, Container>& operator=(const SquareMatrix<T, Container>& matrix);
    ~SquareMatrix();


    T& get(size_t row, size_t column);
    const T& get(size_t row, size_t column) const;
    size_t get_size() const;
    void set(size_t row, size_t column, const T& value);


    SquareMatrix<T, Container> add(const SquareMatrix<T, Container>& matrix) const;
    SquareMatrix<T, Container> multiply_on_scalar(T scalar) const;
    double norm() const;

    SquareMatrix<T, Container>& swap_rows(size_t row_1, size_t row_2);
    SquareMatrix<T, Container>& swap_columns(size_t col_1, size_t col_2);

    SquareMatrix<T, Container>& multiply_row(size_t row, T value);
    SquareMatrix<T, Container>& multiply_column(size_t col, T value);

    SquareMatrix<T, Container>& sum_rows(size_t row_1, size_t row_2);
    SquareMatrix<T, Container>& sum_columns(size_t row_1, size_t row_2);

    auto begin();
    auto end();
    auto begin() const;
    auto end() const;

};

#include "SquareMatrix.tpp"