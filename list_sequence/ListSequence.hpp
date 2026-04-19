#pragma once
#include <cstddef>
#include <stdexcept>
#include "../sequence/Sequence.hpp"
#include "../linked_list/LinkedList.hpp"
#include "../sequence/IEnumerator.hpp"

template<class T>
class ListSequence: public Sequence<T> {
private:
    LinkedList<T>* items_;

public:
    ListSequence();

    ListSequence(T* items, size_t count);
    ListSequence(const ListSequence<T>& list);
    ~ListSequence() override;

    T get_first() const override;
    T get_last() const override;
    T get(size_t index) const override;
    size_t get_length() const override;
    Sequence<T>* get_subsequence(size_t start_index, size_t end_index) const override;

    Sequence<T>* append(T temp) override;
    Sequence<T>* prepend(T temp) override;
    Sequence<T>* insert_at(T temp, size_t index) override;
    Sequence<T>* concat(Sequence<T>* sequence) const override;

    T& operator[](size_t index);

    ListIterator<T> begin();
    ListIterator<T> end();
    IEnumerator<T>* get_enumerator() const override;

    Sequence<T>* map(T (*func)(T)) override;
    Sequence<T>* where(bool (*predicate)(T)) override;
    T reduce(T (*func)(T, T), T starter) override;
};

#include "ListSequence.tpp"