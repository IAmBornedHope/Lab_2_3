#pragma once
#include <cstddef>
#include <stdexcept>
#include "../sequence/Sequence.hpp"
#include "../dynamic_array/DynamicArray.hpp"

template<class T>
class ArraySequence: public Sequence<T> {
private:
    DynamicArray<T>* items_;

public:
    ArraySequence();

    ArraySequence(T* array, size_t count);
    ArraySequence(const ArraySequence<T>& source_sequence);
    ~ArraySequence() override;

    T get_first() const override;
    T get_last() const override;
    T get(size_t index) const override;
    size_t get_length() const override;
    Sequence<T>* get_subsequence(size_t start_index, size_t end_index) const override;

    Sequence<T>* append(T temp) override;
    Sequence<T>* prepend(T temp) override;
    Sequence<T>* insert_at(T temp, size_t index) override;
    Sequence<T>* concat(Sequence<T>* sequence) const override;

    T& operator[](size_t index);

    ArrayIterator<T> begin();
    ArrayIterator<T> end();


};

#include "ArraySequence.tpp"