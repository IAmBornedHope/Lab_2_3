#pragma once
#include <concepts>
#include <cstddef>
#include "../Sequence/Sequence.hpp"
#include "../dynamic_array/DynamicArray.hpp"

using std::integral;

template<integral T>
class Bit {
private:
    T value_;

public:
    Bit() = default;
    Bit(const Bit& b) = default;
    Bit(T o) : value_(o) {}

    bool get_bit_at(size_t index) const {
        return (value_ >> index) & static_cast<T>(1);
    }
};

template<integral T>
class BitSequence: public Sequence<Bit<T>> {
private:
    DynamicArray<T>* data_;
    size_t size_;

    static constexpr size_t BITS_IN_BATCH = sizeof(T) * 8;
    size_t get_batch_index(size_t index) const {return index / BITS_IN_BATCH;}
    size_t get_bit_index(size_t index) const {return index % BITS_IN_BATCH;}
    size_t get_batch_count() const {return size_ / BITS_IN_BATCH + (size_ % BITS_IN_BATCH != 0);}

public:

    BitSequence();
    BitSequence(const BitSequence<T>& source_sequence);
    BitSequence(bool* bits, size_t count);
    BitSequence(size_t size);
    ~BitSequence() override;
    
    bool get_bit_at(size_t index) const;
    void set_bit_at(size_t index, bool value);

    Bit<T> get_first() const override;
    Bit<T> get_last() const override;
    Bit<T> get(size_t index) const override;
    size_t get_length() const override;
    Sequence<Bit<T>>* get_subsequence(size_t start_index, size_t end_index) const override;

    Sequence<Bit<T>>* append(Bit<T> temp) override;
    Sequence<Bit<T>>* prepend(Bit<T> temp) override;
    Sequence<Bit<T>>* insert_at(Bit<T> temp, size_t index) override;
    Sequence<Bit<T>>* concat(Sequence<Bit<T>>* sequence) const override;

    BitSequence<T>* And(const BitSequence<T>& sequence) const;
    BitSequence<T>* Or(const BitSequence<T>& sequence) const;
    BitSequence<T>* Not() const;
    BitSequence<T>* Xor(const BitSequence<T>& sequence) const;

    BitSequence<T> operator&(const BitSequence<T>& sequence) const;
    BitSequence<T> operator|(const BitSequence<T>& sequence) const;
    BitSequence<T> operator~() const;
    BitSequence<T> operator^(const BitSequence<T>& sequence) const;

};

#include "BitSequence.tpp"


