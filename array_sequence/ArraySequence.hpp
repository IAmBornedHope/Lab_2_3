#pragma once
#include <cstddef>
#include <stdexcept>
#include "../sequence/Sequence.hpp"
#include "../dynamic_array/DynamicArray.hpp"
#include "../sequence/IEnumerator.hpp"

template<class T>
class ArraySequence: public Sequence<T> {
protected:
    DynamicArray<T>* items_;
    ArraySequence<T>* append_internal(T temp);
    ArraySequence<T>* prepend_internal(T temp);
    ArraySequence<T>* insert_at_internal(T temp, size_t index);

    ArraySequence<T>* pop_at_internal(size_t index);
    ArraySequence<T>* pop_first_internal();
    ArraySequence<T>* pop_last_internal();
public:
/**
 * @brief Конструктор ArraySequence по умолчанию
 * 
 */
    ArraySequence();
/**
 * @brief Конструктор ArraySequence из масисва
 * 
 * @param array 
 * @param count 
 */
    ArraySequence(T* array, size_t count);
/**
 * @brief Конструктор копирования ArraySequence
 * 
 * @param source_sequence 
 */
    ArraySequence(const ArraySequence<T>& source_sequence);

/**
 * @brief Оператор присваивания для ArraySequence
 * 
 * @param sequence 
 * @return ArraySequence<T>& 
 */
    ArraySequence<T>& operator=(const ArraySequence<T>& sequence);

/**
 * @brief Деструктор ArraySequence
 * 
 */
    virtual ~ArraySequence();

/**
 * @brief Фукнция клонирования ArraySequence
 * 
 * @return ArraySequence<T>* 
 */
    virtual ArraySequence<T>* clone() const = 0;
/**
 * @brief Фукнция для выбора Mutable/Immutable вариации
 * 
 */
    virtual ArraySequence<T>* instance() = 0;
/**
 * @brief Создание пустой ArraySequence 
 * 
 * @return ArraySequence<T>* 
 */
    virtual ArraySequence<T>* construct_empty() const = 0;

/**
 * @brief Получить первый элемент ArraySequence
 * 
 * @return T 
 */
    T get_first() const override;
/**
 * @brief Получить последний элемент ArraySequence
 * 
 * @return T 
 */
    T get_last() const override;
/**
 * @brief Получение элемента ArraySequence по индексу
 * 
 * @param index 
 * @return T 
 */
    T get(size_t index) const override;

/**
 * @brief Получить ссылку по индексу в ArraySequence
 * 
 * @param index 
 * @return T& 
 */
    T& get_reference(size_t index);

/**
 * @brief Получить ссылку по индексу в ArraySequence (const)
 * 
 * @param index 
 * @return const T& 
 */
    const T& get_reference(size_t index) const;
/**
 * @brief Получение длины ArraySequence
 * 
 * @return size_t 
 */
    size_t get_length() const override;
/**
 * @brief Очистка ArraySequence
 * 
 */
    void clear() override;

/**
 * @brief Вставка в конец ArraySequence
 * 
 * @param temp 
 * @return Sequence<T>* 
 */
    Sequence<T>* append(T temp) override;
/**
 * @brief Вставка в начало ArraySequence
 * 
 * @param temp 
 * @return Sequence<T>* 
 */
    Sequence<T>* prepend(T temp) override;
/**
 * @brief Вставка по индексу в ArraySequence
 * 
 * @param temp 
 * @param index 
 * @return Sequence<T>* 
 */
    Sequence<T>* insert_at(T temp, size_t index) override;

/**
 * @brief Удаление по индексу в ArraySequence
 * 
 * @param index 
 * @return Sequence<T>* 
 */
    Sequence<T>* pop_at(size_t index) override;

/**
 * @brief Удаление первого элемента в ArraySequence
 * 
 * @return Sequence<T>* 
 */
    Sequence<T>* pop_first() override;

/**
 * @brief Удаление последнего элемента в ArraySequence
 * 
 * @return Sequence<T>* 
 */
    Sequence<T>* pop_last() override;
/**
 * @brief Конкатенация ArraySequence
 * 
 * @param sequence 
 * @return Sequence<T>* 
 */
    Sequence<T>* concat(Sequence<T>* sequence) const override;

/**
 * @brief Получение подпоследовательности из ArraySequence
 * 
 * @param start_index Индекс начала подпоследовательности
 * @param end_index Индекс конца подпоследовательности
 * @return Sequence<T>* 
 */
    Sequence<T>* get_subsequence(size_t start_index, size_t end_index) const override;

/**
 * @brief Получить итератор на начало ArraySequence
 * 
 * @return ArrayIterator<T> 
 */
    ArrayIterator<T> begin();
/**
 * @brief Получить итератор на конец ArraySequence
 * 
 * @return ArrayIterator<T> 
 */
    ArrayIterator<T> end();
/**
 * @brief Получить итератор для ArraySequence
 * 
 * @return IEnumerator<T>* 
 */
    IEnumerator<T>* get_enumerator() const override;

/**
 * @brief map для ArraySequence
 * 
 * @param func 
 * @return Sequence<T>* 
 */
    Sequence<T>* map(T (*func)(T)) override;
/**
 * @brief where для ArraySequence
 * 
 * @param predicate 
 * @return Sequence<T>* 
 */
    Sequence<T>* where(bool (*predicate)(T)) override;
/**
 * @brief reduce для ArraySequence
 * 
 * @param func 
 * @param accumulator 
 * @return T 
 */
    T reduce(T (*func)(T, T), T accumulator) override;

/**
 * @brief Оператор [] для ArraySequece
 * 
 * @param index 
 * @return T& 
 */
    T& operator[](size_t index);

/**
 * @brief Оператор [] для ArraySequence (const)
 * 
 * @param index 
 * @return const T& 
 */
    const T& operator[](size_t index) const;

};


#include "ArraySequence.tpp"