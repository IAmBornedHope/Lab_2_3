#pragma once
#include "ListSequence.hpp"

template<class T>
class MutableListSequence : public ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;

/**
 * @brief Возвращаем саму ListSequence
 * 
 * @return ListSequence<T>* 
 */
    ListSequence<T>* instance() override {
        return this;
    }

/**
 * @brief Клонирование MutableListSequence
 * 
 * @return ListSequence<T>* 
 */
    ListSequence<T>* clone() const override {
        return new MutableListSequence<T>(*this);
    }

/**
 * @brief Создание пустой MutableListSequence
 * 
 * @return ListSequence<T>* 
 */
    ListSequence<T>* construct_empty() const override {
        return new MutableListSequence<T>();
    }
    
    T& operator[](size_t index) {
        return this->items_->get_reference(index);
    }
};
