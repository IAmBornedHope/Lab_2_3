#pragma once
#include <concepts>
#include "../sequence/IEnumerator.hpp"
#include "../exceptions/Exceptions.hpp"

using std::integral;
template<integral T> class Bit;
template<integral T> class BitSequence;


template<integral T>
class BitIterator: public IEnumerator<Bit<T>> {
public:
    using ptr = const BitSequence<T>*;
    
    explicit BitIterator(ptr p, size_t index, size_t size) : ptr_(p), index_(index), size_(size) {}

    const Bit<T>& get_elem() const override {
        if (!ptr_) {
            throw IteratorPointerException("BitIterator: get_elem. Итератор не определен.");
        }
        bit = Bit<T>(ptr_->get_bit_at(index_));
        return bit;
    }

    void next_elem() override {
        index_++;
    }

    bool is_end() const override {  
        return (index_ == size_);
    }
    
    Bit<T> operator*() const {
        if (!ptr_) {
            throw IteratorPointerException("BitIterator: operator*. Попытка разыменования nullptr");
        }
        return Bit<T>(ptr_->get_bit_at(index_));
    }
    
    BitIterator& operator++() {
        index_++;
        return *this;
    }
    
    bool operator==(const BitIterator& r) const {
        return ptr_ == r.ptr_ && index_ == r.index_;
    }

    bool operator!=(const BitIterator& r) const {
        return (ptr_ != r.ptr_) || (index_ != r.index_);
    }

private:
    ptr ptr_;
    size_t index_;
    size_t size_;
    mutable Bit<T> bit;
};
