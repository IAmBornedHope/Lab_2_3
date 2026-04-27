#pragma once
#include <cstddef>
#include <stdexcept>
#include "ArrayIterator.hpp"

template<class T>
class DynamicArray {
private:
    size_t size_;
    T* data_;

public:
/**
 * @brief Конструктор по умолчанию для DynamicArray
 * 
 */
    DynamicArray();

/**
 * @brief Конструктор из массива для DynamicArray
 * 
 * @param items 
 * @param count 
 */
    DynamicArray(T* items, size_t count);
/**
 * @brief Конструктор по размеру для DynamicArray
 * 
 * @param size 
 */
    DynamicArray(size_t size);
/**
 * @brief Конструктор копирования для DynamicArray
 * 
 * @param source_array 
 */
    DynamicArray(const DynamicArray<T>& source_array);
/**
 * @brief Присваивание для DynamicArray
 * 
 * @param source_array 
 * @return DynamicArray<T>& 
 */
    DynamicArray<T>& operator=(const DynamicArray<T>& source_array);

/**
 * @brief Деструктор для DynamicArray
 * 
 */
    ~DynamicArray();

/**
 * @brief Получение элемента для DynamicArray по индексу
 * 
 * @param index 
 * @return T 
 */
    T get(size_t index) const;

/**
 * @brief Получение размера для для DynamicArray
 * 
 * @return size_t 
 */
    size_t get_size() const;
/**
 * @brief Получение ссылки по индексу для DynamicArray
 * 
 * @param index 
 * @return T& 
 */
    T& get_reference(size_t index) const;
/**
 * @brief Получение указатель на данные для DynamicArray
 * 
 * @return T* 
 */
    T* get_data() const;

/**
 * @brief Изменение элемента по индексу для DynamicArray
 * 
 * @param index 
 * @param value 
 */
    void set(size_t index, T value);

/**
 * @brief Изменение размера массива для DynamicArray
 * 
 * @param new_size 
 */
    void resize(size_t new_size);

/**
 * @brief Получить итератор на начало DynamicArray
 * 
 * @return ArrayIterator<T> 
 */
    ArrayIterator<T> begin();
/**
 * @brief Получить итератор на конец DynamicArray
 * 
 * @return ArrayIterator<T> 
 */
    ArrayIterator<T> end();
/**
 * @brief Получить const итератор на начало DynamicArray
 * 
 * @return ArrayIterator<T> 
 */
    ArrayIterator<T> begin() const;
/**
 * @brief Получить const итератор на конец DynamicArray
 * 
 * @return ArrayIterator<T> 
 */
    ArrayIterator<T> end() const;

};

#include "DynamicArray.tpp"