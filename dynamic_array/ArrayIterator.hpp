#pragma once
#include "../sequence/IEnumerator.hpp"
#include "../exceptions/Exceptions.hpp"

template<class T>
class ArrayIterator: public IEnumerator<T> {

public:
    using ptr = T*;
    using rfr = T&;
    
    explicit ArrayIterator(ptr p, ptr end) : ptr_(p), end_(end) {}

    const T& get_elem() const override {
        if (!ptr_) {
            throw IteratorPointerException("ArrayIterator: get_elem. Итератор не определен");
        }
        return *ptr_;
    }

    void next_elem() override {
        ptr_++;
    }

    bool is_end() const override {
        return ptr_ == end_;
    }
    
    rfr operator*() const {
        return *ptr_;
    }
    
    ArrayIterator& operator++() {
        ptr_++;
        return *this;
    }
    
    bool operator==(const ArrayIterator& r) const {
        return ptr_ == r.ptr_;
    }

    bool operator!=(const ArrayIterator& r) const {
        return ptr_ != r.ptr_;
    }

private:
    ptr ptr_;
    ptr end_;
};
