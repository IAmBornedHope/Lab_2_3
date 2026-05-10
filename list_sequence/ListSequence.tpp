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
ListSequence<T>& ListSequence<T>::operator=(const ListSequence<T>& list) {
    if (this != &list) {
        delete items_;
        items_ = new LinkedList<T>(*list.items_);
    }
    return *this;
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
T& ListSequence<T>::get_reference(size_t index) {
    if (index >= get_length()) {
        throw IndexOutOfRangeException("ListSequence. get_reference. Индекс вне последовательности.");
    }
    return items_->get_reference(index);
}

template<class T>
const T& ListSequence<T>::get_reference(size_t index) const {
    if (index >= get_length()) {
        throw IndexOutOfRangeException("ListSequence. get_reference. Индекс вне последовательности.");
    }
    return items_->get_reference(index);
}

template<class T>
size_t ListSequence<T>::get_length() const {
    return items_->get_length();
}

template<class T>
void ListSequence<T>::clear() {
    items_->clear();
}

template<class T>
ListSequence<T>* ListSequence<T>::append_internal(T temp) {
    items_->append(temp);
    return this;
}

template<class T>
ListSequence<T>* ListSequence<T>::insert_at_internal(T temp, size_t index) {
    items_->insert_at(temp, index);
    return this;
}

template<class T>
ListSequence<T>* ListSequence<T>::prepend_internal(T temp) {
    items_->prepend(temp);
    return this;
}

template<class T>
ListSequence<T>* ListSequence<T>::pop_at_internal(size_t index) {
    items_->pop_at(index);
    return this;
}

template<class T>
ListSequence<T>* ListSequence<T>::pop_first_internal() {
    items_->pop_first();
    return this;
}

template<class T>
ListSequence<T>* ListSequence<T>::pop_last_internal() {
    items_->pop_last();
    return this;
}

template<class T>
Sequence<T>* ListSequence<T>::append(T temp) {
    ListSequence<T>* target = instance();
    target->append_internal(temp);
    return target;
}

template<class T>
Sequence<T>* ListSequence<T>::prepend(T temp) {
    ListSequence<T>* target = instance();
    target->prepend_internal(temp);
    return target;
}

template<class T>
Sequence<T>* ListSequence<T>::insert_at(T temp, size_t index) {
    ListSequence<T>* target = instance();
    target->insert_at_internal(temp, index);
    return target;
}

template<class T>
Sequence<T>* ListSequence<T>::pop_at(size_t index) {
    ListSequence<T>* target = instance();
    target->pop_at_internal(index);
    return target;
}

template<class T>
Sequence<T>* ListSequence<T>::pop_first() {
    ListSequence<T>* target = instance();
    target->pop_first_internal();
    return target;
}

template<class T>
Sequence<T>* ListSequence<T>::pop_last() {
    ListSequence<T>* target = instance();
    target->pop_last_internal();
    return target;
}


template<class T>
Sequence<T>* ListSequence<T>::get_subsequence(size_t start_index, size_t end_index) const {
    if (end_index >= get_length() || start_index > end_index) {
        throw IndexOutOfRangeException("ListSequence: get_subsequence. Некорректные индексы для подпоследовательности.");
    }
    ListSequence<T>* subsequence = construct_empty();
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
    ListSequence<T>* new_sequence = construct_empty();

    for (size_t index = 0; index < this->get_length(); ++index) {
        new_sequence->append(this->get(index));
    }
    for (size_t index = 0; index < sequence->get_length(); ++index) {
        new_sequence->append(sequence->get(index));
    }
    return new_sequence;
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
    ListSequence<T>* mapped = construct_empty();
    for (auto& item : *this) {
        mapped->append_internal(func(item));
    }
    return mapped;
}

template<class T>
Sequence<T>* ListSequence<T>::where(bool (*predicate)(T)) {
    ListSequence<T>* filtered = construct_empty();
    for (auto& item : *this) {
        if (predicate(item)) {
            filtered->append_internal(item);
        }
    }
    return filtered;
}

template<class T>
T ListSequence<T>::reduce(T (*func)(T, T), T accumulator) {
    T reduced = accumulator;
    for (auto& item : *this) {
        reduced = func(reduced, item);
    }
    return reduced;
}

template<class T>
T& ListSequence<T>::operator[](size_t index) {
    return get_reference(index);
}

template<class T>
const T& ListSequence<T>::operator[](size_t index) const {
    return get_reference(index);
}