#pragma once
#include "ArraySequence.hpp"

template<class T>
class MutableArraySequence : public ArraySequence<T> {
public:
    using ArraySequence<T>::ArraySequence;

/**
 * @brief Возвращаем саму ArraySequence
 * 
 * @return ArraySequence<T>* 
 */
    ArraySequence<T>* instance() override {
        return this;
    }
/**
 * @brief Клонирование MutableArraySequence
 * 
 * @return ArraySequence<T>* 
 */
    ArraySequence<T>* clone() const override {
        return new MutableArraySequence<T>(*this);
    }
/**
 * @brief Создание пустой MutableArraySequence
 * 
 * @return ArraySequence<T>* 
 */
    ArraySequence<T>* construct_empty() const override {
        return new MutableArraySequence<T>();
    }
    
    T& operator[](size_t index) {
        return this->items_->get_reference(index);
    }
};
