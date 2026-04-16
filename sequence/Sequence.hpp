#pragma once
#include <stdexcept>
#include <cstddef>

template<class T>
class Sequence {
public:
    virtual ~Sequence() = default;
    virtual T get_first() const = 0;
    virtual T get_last() const = 0;
    virtual T get(size_t index) const = 0;
    virtual size_t get_length() const = 0;
    virtual Sequence<T>* get_subsequence(size_t start_index, size_t end_index) const = 0;

    virtual void append(T temp) = 0;
    virtual void prepend(T temp) = 0;
    virtual void insert_at(T temp) = 0;
    virtual Sequence<T>* concat(Sequence<T>* sequence) const = 0;

};