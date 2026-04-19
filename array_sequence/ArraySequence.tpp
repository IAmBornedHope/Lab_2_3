#include <stdexcept>
#include <cstddef>
#include "ArraySequence.hpp"
#include "../exceptions/Exceptions.hpp"

template<class T>
ArraySequence<T>::ArraySequence() : items_(new DynamicArray<T>()) {}

template<class T>
ArraySequence<T>::ArraySequence(T* array, size_t count) {
    items_ = new DynamicArray<T>(array, count);
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& source_sequence) {
    items_ = new DynamicArray<T>(*source_sequence.items_);
}
template<class T>
ArraySequence<T>::~ArraySequence() {
    delete items_;
}

template<class T>
T ArraySequence<T>::get_first() const {
    if (items_->get_size() == 0) {
        throw IndexOutOfRangeException("Пустой сиквенс");
    }
    return items_->get(0);
};

template<class T>
T ArraySequence<T>::get_last() const {
    if (items_->get_size() == 0) {
        throw IndexOutOfRangeException("Пустой сиквенс");
    }
    return items_->get(items_->get_size() - 1);
}

template<class T>
T ArraySequence<T>::get(size_t index) const {
    return items_->get(index);
}

template<class T>
size_t ArraySequence<T>::get_length() const {
    return items_->get_size();
}

template<class T>
Sequence<T>* ArraySequence<T>::append(T temp) {
    size_t size = items_->get_size();
    items_->resize(size + 1);
    items_->set(size, temp);
    return this;
}

template<class T>
Sequence<T>* ArraySequence<T>::insert_at(T temp, size_t index) {
    size_t size = items_->get_size();
    if (index > size) {
        throw IndexOutOfRangeException("Индекс вне сиквенса");
    }
    items_->resize(size + 1);
    for (size_t cur = size; cur > index; cur--) {
        items_->set(cur, get(cur - 1));
    }
    items_->set(index, temp);
    return this;
}

template<class T>
Sequence<T>* ArraySequence<T>::prepend(T temp) {
    insert_at(temp, 0);
    return this;
}

template<class T>
Sequence<T>* ArraySequence<T>::get_subsequence(size_t start_index, size_t end_index) const {
    if (end_index >= get_length() || start_index > end_index) {
        throw IndexOutOfRangeException("Некорректные индексы подпоследовательности");
    }
    ArraySequence<T>* subsequence = new ArraySequence<T>();
    for (size_t cur = start_index; cur <= end_index; ++cur) {
        subsequence->append(items_->get(cur));
    }
    return subsequence;
}

template<class T>
Sequence<T>* ArraySequence<T>::concat(Sequence<T>* sequence) const {
    if (sequence == nullptr) {
        throw NullPointerException("Передан нулевой указатель");
    }
    ArraySequence<T>* new_sequence = new ArraySequence<T>(*this);
    for (size_t index = 0; index < sequence->get_length(); ++index) {
        new_sequence->append(sequence->get(index));
    }
    return new_sequence;
}

template<class T>
T& ArraySequence<T>::operator[](size_t index) {
    return items_->get_reference(index);
}

template<class T>
ArrayIterator<T> ArraySequence<T>::begin() {
    return items_->begin();
}

template<class T>
ArrayIterator<T> ArraySequence<T>::end() {
    return items_->end();
}

template<class T>
IEnumerator<T>* ArraySequence<T>::get_enumerator() const {
    T* start = items_->get_data();
    T* end = items_->get_data() + items_->get_size();
    return new ArrayIterator<T>(start, end);
}

template<class T>
Sequence<T>* ArraySequence<T>::map(T (*func)(T)) {
    ArraySequence<T>* mapped = new ArraySequence<T>();
    for (auto& item : *this) {
        mapped->append(func(item));
    }
    return mapped;
}

template<class T>
Sequence<T>* ArraySequence<T>::where(bool (*predicate)(T)) {
    ArraySequence<T>* filtered = new ArraySequence<T>();
    for (auto& item : *this) {
        if (predicate(item)) {
            filtered->append(item);
        }
    }
    return filtered;
}

template<class T>
T ArraySequence<T>::reduce(T (*func)(T, T), T starter) {
    T reduced = starter;
    for (auto& item : *this) {
        reduced = func(reduced, item);
    }
    return reduced;
}