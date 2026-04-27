#pragma once
#include "ArraySequence.hpp"

template<class T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    using ArraySequence<T>::ArraySequence;

/**
 * @brief Возвращаем копию ArraySequence
 * 
 * @return ArraySequence<T>* 
 */
    ArraySequence<T>* instance() override {
        return this->clone();
    }

    /**
     * @brief Клонирование ImmutableArraySequence
     * 
     * @return ArraySequence<T>* 
     */
    ArraySequence<T>* clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }

    /**
     * @brief Создание пустой ImmutableArraySequence
     * 
     * @return ArraySequence<T>* 
     */
    ArraySequence<T>* construct_empty() const override {
        return new ImmutableArraySequence<T>();
    }
    
    T operator[](size_t index) const {
        return this->items_->get(index);
    }
};
