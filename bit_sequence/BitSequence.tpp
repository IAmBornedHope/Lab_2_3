#include "BitSequence.hpp"
#include "../sequence/Sequence.hpp"
#include "../exceptions/Exceptions.hpp"


template<integral T>
BitSequence<T>::BitSequence() : data_(new DynamicArray<T>()), size_(0) {};

template<integral T>
BitSequence<T>::BitSequence(const BitSequence<T>& source_sequence) : size_(source_sequence.size_) {
    data_ = new DynamicArray<T>(*source_sequence.data_);
}

template<integral T>
BitSequence<T>::BitSequence(bool* bits, size_t count) : data_(nullptr), size_(count) {
    if (bits == nullptr) {
        throw NullPointerException("BitSequence: Конструктор из массива. Передан нулевой указатель.");
    }
    size_t batches = get_batch_count();
    data_ = new DynamicArray<T>(batches);

    for (size_t index = 0; index < batches; ++index) {
        data_->set(index, static_cast<T>(0));
    }

    for (size_t index = 0; index < size_; ++index) {
        if (bits[index]) {
            set_bit_at(index, bits[index]);
        }
    }
}

template<integral T>
BitSequence<T>::BitSequence(size_t size) : size_(size) {
    size_t batches = get_batch_count();
    data_ = new DynamicArray<T>(batches);

    for (size_t index = 0; index < batches; ++index) {
        data_->set(index, static_cast<T>(0));
    }
}

template<integral T>
BitSequence<T>::~BitSequence() {
    delete data_;
}

template<integral T>
bool BitSequence<T>::get_bit_at(size_t index) const {
    if (index >= size_) {
        throw IndexOutOfRangeException("BitSequence: get_bit_at. Индекс вне последовательности.");
    }
    size_t batch_index = get_batch_index(index);
    size_t bit_index = get_bit_index(index);

    T target_batch = data_->get(batch_index);

    return (target_batch >> bit_index) & static_cast<T>(1);
}

template<integral T>
void BitSequence<T>::set_bit_at(size_t index, bool value) {
    if (index >= size_) {
        throw IndexOutOfRangeException("BitSequence: set_bit_at. Индекс вне последовательности.");
    }

    size_t batch_index = get_batch_index(index);
    size_t bit_index = get_bit_index(index);

    T target_batch = data_->get(batch_index);

    if (value) {
        target_batch |= (static_cast<T>(1) << bit_index);
    }
    else {
        target_batch &= ~(static_cast<T>(1) << bit_index);
    }

    data_->set(batch_index, target_batch);
}

template<integral T>
Bit<T> BitSequence<T>::get(size_t index) const {
    if (index >= size_) {
        throw IndexOutOfRangeException("BitSequence: get. Индекс вне последовательности.");
    }
    return Bit<T>(get_bit_at(index));
}

template<integral T>
Bit<T> BitSequence<T>::get_first() const {
    if (size_ == 0) {
        throw EmptyListException("BitSequence: get_first. Последовательность пуста.");
    }
    return get(0);
}

template<integral T>
Bit<T> BitSequence<T>::get_last() const {
    if (size_ == 0) {
        throw EmptyListException("BitSequence: get_last. Последовательность пуста.");
    }
    return get(size_ - 1);
}

template<integral T>
size_t BitSequence<T>::get_length() const {
    return size_;
}

template<integral T>
Sequence<Bit<T>>* BitSequence<T>::insert_at(Bit<T> temp, size_t index) {
    if (index > size_) {
        throw IndexOutOfRangeException("BitSequence: insert_at. Индекс вне последовательности.");
    }
    size_t batches = get_batch_count();
    size_ = size_ + 1;
    size_t new_batches = get_batch_count();

    if (new_batches > batches) {
        data_->resize(new_batches);
        data_->set(new_batches - 1, 0);
    }

    for (size_t cur = size_ - 1; cur > index; --cur) {
        set_bit_at(cur, get_bit_at(cur - 1));
    }

    set_bit_at(index, temp.get_bit_at(0));
    return this;

}

template<integral T>
Sequence<Bit<T>>* BitSequence<T>::append(Bit<T> temp) {
    return insert_at(temp, size_);
}

template<integral T>
Sequence<Bit<T>>* BitSequence<T>::prepend(Bit<T> temp) {
    return insert_at(temp, 0);
}

template<integral T>
Sequence<Bit<T>>* BitSequence<T>::get_subsequence(size_t start_index, size_t end_index) const {
    if (end_index >= get_length() || start_index > end_index) {
        throw IndexOutOfRangeException("BitSequence: get_subsequence. Некорректные индексы для подпоследовательности.");
    }
    size_t sub_size = end_index - start_index + 1;
    BitSequence<T>* subsequence = new BitSequence<T>(sub_size);

    for (size_t cur = 0; cur < sub_size; ++cur) {
        subsequence->set_bit_at(cur, get_bit_at(start_index + cur));
    }
    return subsequence;
}

template<integral T>
Sequence<Bit<T>>* BitSequence<T>::concat(Sequence<Bit<T>>* sequence) const {
    if (sequence == nullptr) {
        throw NullPointerException("BitSequence: concat. Передан нулевой указатель.");
    }
    BitSequence<T>* new_sequence = new BitSequence<T>(*this);
    for (size_t index = 0; index < sequence->get_length(); ++index) {
        new_sequence->append(sequence->get(index));
    }
    return new_sequence;
}

template<integral T>
BitSequence<T>* BitSequence<T>::And(const BitSequence<T>& sequence) const {
    if (size_ != sequence.size_) {
        throw SequenceLengthMismatchException("BitSequence: And. Длины последовательностей не совпадают.");
    }

    BitSequence<T>* operated = new BitSequence<T>(size_);
    size_t batches = get_batch_count();

    for (size_t index = 0; index < batches; ++index) {
        T result = this->data_->get(index) & sequence.data_->get(index);
        operated->data_->set(index, result);
    }
    return operated;
}

template<integral T>
BitSequence<T>* BitSequence<T>::Or(const BitSequence<T>& sequence) const {
    if (size_ != sequence.size_) {
        throw SequenceLengthMismatchException("BitSequence: Or. Длины последовательностей не совпадают.");
    }

    BitSequence<T>* operated = new BitSequence<T>(size_);
    size_t batches = get_batch_count();

    for (size_t index = 0; index < batches; ++index) {
        T result = this->data_->get(index) | sequence.data_->get(index);
        operated->data_->set(index, result);
    }
    return operated;
}

template<integral T>
BitSequence<T>* BitSequence<T>::Not() const {
    BitSequence<T>* operated = new BitSequence<T>(size_);
    size_t batches = get_batch_count();

    for (size_t index = 0; index < batches; ++index) {
        T result = ~(this->data_->get(index));
        operated->data_->set(index, result);
    }
    return operated;
}

template<integral T>
BitSequence<T>* BitSequence<T>::Xor(const BitSequence<T>& sequence) const {
    if (size_ != sequence.size_) {
        throw SequenceLengthMismatchException("BitSequence: Xor. Длины последовательностей не совпадают.");
    }

    BitSequence<T>* operated = new BitSequence<T>(size_);
    size_t batches = get_batch_count();

    for (size_t index = 0; index < batches; ++index) {
        T result = this->data_->get(index) ^ sequence.data_->get(index);
        operated->data_->set(index, result);
    }
    return operated;
}

template <integral T>
BitSequence<T> BitSequence<T>::operator&(const BitSequence<T>& sequence) const {
    BitSequence<T>* temp = And(sequence);
    BitSequence<T> result(*temp);
    delete temp;
    return result;
}

template <integral T>
BitSequence<T> BitSequence<T>::operator|(const BitSequence<T>& sequence) const {
    BitSequence<T>* temp = Or(sequence);
    BitSequence<T> result(*temp);
    delete temp;
    return result;
}

template <integral T>
BitSequence<T> BitSequence<T>::operator~() const {
    BitSequence<T>* temp = Not();
    BitSequence<T> result(*temp);
    delete temp;
    return result;
}

template <integral T>
BitSequence<T> BitSequence<T>::operator^(const BitSequence<T>& sequence) const {
    BitSequence<T>* temp = Xor(sequence);
    BitSequence<T> result(*temp);
    delete temp;
    return result;
}

template<integral T>
BitIterator<T> BitSequence<T>::begin() {
    return BitIterator<T>(this, 0, size_);
}

template<integral T>
BitIterator<T> BitSequence<T>::end() {
    return BitIterator<T>(this, size_, size_);
}

template<integral T>
BitIterator<T> BitSequence<T>::begin() const {
    return BitIterator<T>(this, 0, size_);
}

template<integral T>
BitIterator<T> BitSequence<T>::end() const {
    return BitIterator<T>(this, size_, size_);
}

template<integral T>
IEnumerator<Bit<T>>* BitSequence<T>::get_enumerator() const {
    IEnumerator<Bit<T>>* ptr = new BitIterator<T>(this, 0, size_);
    return ptr;
}

template<integral T>
Sequence<Bit<T>>* BitSequence<T>::map(Bit<T> (*func)(Bit<T>)) {
    BitSequence<T>* mapped = new BitSequence<T>();
    for (const auto& item : *this) {
        Bit<T> mapped_bit = func(item);
        mapped->append(mapped_bit);
    }
    return mapped;
}

template<integral T>
Sequence<Bit<T>>* BitSequence<T>::where(bool (*predicate)(Bit<T>)) {
    BitSequence<T>* filtered = new BitSequence<T>();
    for (const auto& item : *this) {
        if (predicate(item)) {
            filtered->append(item);
        }
    }
    return filtered;
}

template<integral T>
Bit<T> BitSequence<T>::reduce(Bit<T> (*func)(Bit<T>, Bit<T>), Bit<T> accumulator) {
    Bit<T> reduced = accumulator;
    for (const auto& item : *this) {
        reduced = func(reduced, item);
    }
    return reduced;
}