#pragma once
#include <stdexcept>
#include <cstddef>
#include "IEnumerator.hpp"
#include "../bit_sequence/BitIterator.hpp"

template<class T>
class Sequence {
public:
    virtual ~Sequence() = default;
    virtual T get_first() const = 0;
    virtual T get_last() const = 0;
    virtual T get(size_t index) const = 0;
    virtual size_t get_length() const = 0;
    virtual Sequence<T>* get_subsequence(size_t start_index, size_t end_index) const = 0;

    virtual Sequence<T>* append(T temp) = 0;
    virtual Sequence<T>* prepend(T temp) = 0;
    virtual Sequence<T>* insert_at(T temp, size_t index) = 0;
    virtual Sequence<T>* pop_at(size_t index) = 0;
    virtual Sequence<T>* pop_front() = 0;
    virtual Sequence<T>* pop_back() = 0;
    virtual Sequence<T>* concat(Sequence<T>* sequence) const = 0;
    virtual IEnumerator<T>* get_enumerator() const = 0;
    virtual void clear() = 0;

    virtual Sequence<T>* map(T (*func)(T)) = 0;
    virtual Sequence<T>* where(bool (*predicate)(T)) = 0;
    virtual T reduce(T (*func)(T, T), T starter) = 0;

};