#pragma once
#include <cstddef>
#include <stdexcept>

template<class T>
class DynamicArray {
private:
    size_t size_;
    T* data_;

public:
    DynamicArray();

    DynamicArray(T* items, size_t count);
    DynamicArray(size_t size);
    DynamicArray(const DynamicArray<T>& dynamic_array);
    DynamicArray<T>& operator=(const DynamicArray<T>& other);

    ~DynamicArray();

    T get(size_t index) const;
    size_t get_size() const;

    void set(size_t index, T value);
    void resize(size_t new_size);

};

#include "DynamicArray.tpp"