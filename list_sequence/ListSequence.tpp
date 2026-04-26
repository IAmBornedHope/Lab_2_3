#include <stdexcept>
#include <cstddef>
#include "ListSequence.hpp"
#include "../exceptions/Exceptions.hpp"

template<class T>
ListSequence<T>::ListSequence() : items_(new LinkedList<T>()) {}

template<class T>
ListSequence<T>::ListSequence(T* items, size_t count) {
    items_ = new LinkedList<T>(items, count);
}

template<class T>
ListSequence<T>::ListSequence(const ListSequence<T>& list) {
    items_ = new LinkedList<T>(*list.items_);
}
template<class T>
ListSequence<T>::~ListSequence() {
    delete items_;
}

template<class T>
T ListSequence<T>::get_first() const {
    return items_->get_first();
}

template<class T>
T ListSequence<T>::get_last() const {
    return items_->get_last();
}

template<class T>
T ListSequence<T>::get(size_t index) const {
    return items_->get(index);
}

template<class T>
size_t ListSequence<T>::get_length() const {
    return items_->get_length();
}

template<class T>
Sequence<T>* ListSequence<T>::append(T temp) {
    items_->append(temp);
    return this;
}

template<class T>
Sequence<T>* ListSequence<T>::insert_at(T temp, size_t index) {
    items_->insert_at(temp, index);
    return this;
}

template<class T>
Sequence<T>* ListSequence<T>::prepend(T temp) {
    items_->prepend(temp);
    return this;
}

template<class T>
Sequence<T>* ListSequence<T>::get_subsequence(size_t start_index, size_t end_index) const {
    if (end_index >= get_length() || start_index > end_index) {
        throw IndexOutOfRangeException("ListSequence: get_subsequence. Некорректные индексы для подпоследовательности.");
    }
    ListSequence<T>* subsequence = new ListSequence<T>();
    for (size_t cur = start_index; cur <= end_index; ++cur) {
        subsequence->append(items_->get(cur));
    }
    return subsequence;
}

template<class T>
Sequence<T>* ListSequence<T>::concat(Sequence<T>* sequence) const {
    if (sequence == nullptr) {
        throw NullPointerException("ListSequence: concat. Передан нулевой указатель.");
    }
    ListSequence<T>* new_sequence = new ListSequence<T>(*this);
    for (size_t index = 0; index < sequence->get_length(); ++index) {
        new_sequence->append(sequence->get(index));
    }
    return new_sequence;
}

template<class T>
T& ListSequence<T>::operator[](size_t index) {
    return items_->get_reference(index);
}

template<class T>
ListIterator<T> ListSequence<T>::begin() {
    return items_->begin();
}

template<class T>
ListIterator<T> ListSequence<T>::end() {
    return items_->end();
}

template<class T>
IEnumerator<T>* ListSequence<T>::get_enumerator() const {
    return new ListIterator<T>(items_->get_head());
}

template<class T>
Sequence<T>* ListSequence<T>::map(T (*func)(T)) {
    ListSequence<T>* mapped = new ListSequence<T>();
    for (auto& item : *this) {
        mapped->append(func(item));
    }
    return mapped;
}

template<class T>
Sequence<T>* ListSequence<T>::where(bool (*predicate)(T)) {
    ListSequence<T>* filtered = new ListSequence<T>();
    for (auto& item : *this) {
        if (predicate(item)) {
            filtered->append(item);
        }
    }
    return filtered;
}

template<class T>
T ListSequence<T>::reduce(T (*func)(T, T), T starter) {
    T reduced = starter;
    for (auto& item : *this) {
        reduced = func(reduced, item);
    }
    return reduced;
}