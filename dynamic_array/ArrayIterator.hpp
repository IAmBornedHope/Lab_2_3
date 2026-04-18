#pragma once
#include "../sequence/IEnumerator.hpp"

template<class T>
class ArrayIterator: public IEnumerator<T, ArrayIterator> {

public:
    using ptr = T*;
    using rfr = T&;
    
    explicit ArrayIterator(ptr p) : ptr_(p) {}
    
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

private:
    ptr ptr_;
};
