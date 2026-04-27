#pragma once
#include "ListSequence.hpp"

template<class T>
class ImmutableListSequence : public ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;

/**
 * @brief Возвращаем копию ListSequence
 * 
 * @return ListSequence<T>* 
 */
    ListSequence<T>* instance() override {
        return this->clone();
    }

/**
 * @brief Клонирование ImmutableListSequence
 * 
 * @return ListSequence<T>* 
 */
    ListSequence<T>* clone() const override {
        return new ImmutableListSequence<T>(*this);
    }

/**
 * @brief Создание пустой ImmutableListSequence
 * 
 * @return ListSequence<T>* 
 */
    ListSequence<T>* construct_empty() const override {
        return new ImmutableListSequence<T>();
    }
    
    T operator[](size_t index) const {
        return this->items_->get(index);
    }
};
