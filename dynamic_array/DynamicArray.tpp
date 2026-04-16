#include "DynamicArray.hpp"
#include "../exceptions/Exceptions.hpp"

template<class T>
DynamicArray<T>::DynamicArray() : size_(0), data_(nullptr) {}

template<class T>
DynamicArray<T>::DynamicArray(T* items, size_t count) : size_(count), data_(nullptr) {
    if (count > 0 && items == nullptr) {
        throw NullPointerException("Передан нулевой указатель");
    }
    if (count > 0) {
        data_ = new T[count]();
        for (size_t index = 0; index < count; ++index) {
            data_[index] = items[index];
        }
    }
}

template<class T>
DynamicArray<T>::DynamicArray(size_t size) : size_(size), data_(nullptr) {
    
    if (size > 0) {
        data_ = new T[size]();
    }
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& source_array) : size_(source_array.size_), data_(nullptr) {
    if (size_ > 0) {
        if (source_array.data_ == nullptr) {
            throw NullPointerException("Передан нулевой указатель");
        }
        data_ = new T[size_]();
        for (size_t index = 0; index < size_; ++index) {
            data_[index] = source_array.data_[index];
        }
    }
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& source_array) {
    if (this != &source_array) {
        T* new_data = nullptr;
        size_t source_size = source_array.size_;

        if (source_size > 0) {
            if (source_array.data_ == nullptr) {
                throw NullPointerException("Передан нулевой указатель");
            }
            new_data = new T[source_size]();
            for (size_t index = 0; index < source_size; ++index) {
                new_data[index] = source_array.data_[index];
            }
        }
        delete[] data_;
        data_ = new_data;
        size_ = source_size;
    }
    return *this;
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data_;
    data_ = nullptr;
}

template<class T>
T DynamicArray<T>::get(size_t index) const {
    if (index >= size_) {
        throw IndexOutOfRangeException("Индекс вне массива");
    }
    if (data_ == nullptr) {
        throw NullPointerException("Указатель на данные - nullptr");
    }
    return data_[index];
}

template<class T>
size_t DynamicArray<T>::get_size() const {
    return size_;   
}

template<class T>
void DynamicArray<T>::set(size_t index, T value) {
    if (index >= size_) {
        throw IndexOutOfRangeException("Индекс вне массива");
    }
    if (data_ == nullptr) {
        throw NullPointerException("Данные в массиве - nullptr");
    }
    data_[index] = value;
}

template<class T>
void DynamicArray<T>::resize(size_t new_size) {
    if (new_size == size_) {
        return;
    }

    T* new_data = nullptr;

    if (new_size > 0) {
        new_data = new T[new_size]();
    }

    size_t copied = (size_ < new_size) ? size_ : new_size;

    for (size_t index = 0; index < copied; ++index) {
        new_data[index] = data_[index];
    }
    
    delete[] data_;
    data_ = new_data;
    size_ = new_size;
}