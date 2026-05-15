#pragma once
#include <cstddef>
#include <stdexcept>
#include "../sequence/Sequence.hpp"
#include "../linked_list/LinkedList.hpp"
#include "../sequence/IEnumerator.hpp"

template<class T>
class ListSequence: public Sequence<T> {
protected:
    LinkedList<T>* items_;
    ListSequence<T>* append_internal(T temp);
    ListSequence<T>* prepend_internal(T temp);
    ListSequence<T>* insert_at_internal(T temp, size_t index);

    ListSequence<T>* pop_at_internal(size_t index);
    ListSequence<T>* pop_front_internal();
    ListSequence<T>* pop_back_internal();

public:
/**
 * @brief Конструктор по умолчанию для ListSequence
 * 
 */
    ListSequence();
/**
 * @brief Конструктор из массива для ListSequence
 * 
 * @param items 
 * @param count 
 */
    ListSequence(T* items, size_t count);
/**
 * @brief Конструктор копирования для ListSequence
 * 
 * @param list 
 */
    ListSequence(const ListSequence<T>& list);

/**
 * @brief Оператор присваивания для ListSequence
 * 
 * @param other 
 * @return ListSequence<T>& 
 */
    ListSequence<T>& operator=(const ListSequence<T>& other);

/**
 * @brief Деструктор для для ListSequence
 * 
 */
    virtual ~ListSequence();

/**
 * @brief Функция клонирования ListSequence
 * 
 * @return ListSequence<T>* 
 */
    virtual ListSequence<T>* clone() const = 0;
/**
 * @brief Функция для выбора Mutable/Immutable вариации
 * 
 * @return ListSequence<T>* 
 */
    virtual ListSequence<T>* instance() = 0;
/**
 * @brief Создание пустой ListSequence
 * 
 * @return ListSequence<T>* 
 */
    virtual ListSequence<T>* construct_empty() const = 0;

/**
 * @brief Получить первый элемент ListSequence
 * 
 * @return T 
 */
    T get_first() const override;
/**
 * @brief Получить последний элемент ListSequence
 * 
 * @return T 
 */
    T get_last() const override;
/**
 * @brief Получить элемент по индексу из ListSequence
 * 
 * @param index 
 * @return T 
 */
    T get(size_t index) const override;

/**
 * @brief Получить ссылку на элемент по индексу для ListSequence
 * 
 * @param index 
 * @return T& 
 */
    T& get_reference(size_t index);

/**
 * @brief Получить ссылку на элемент по индексу для ListSequence (const)
 * 
 * @param index 
 * @return const T& 
 */
    const T& get_reference(size_t index) const;
/**
 * @brief Получить длину ListSequence
 * 
 * @return size_t 
 */
    size_t get_length() const override;
/**
 * @brief Очистка ListSequence
 * 
 */
    void clear() override;

/**
 * @brief Установка по индексу для ListSequence
 * 
 * @param index 
 * @param temp 
 */
    void set(size_t index, T temp);

/**
 * @brief Вставка в конец ListSequence
 * 
 * @param temp 
 * @return Sequence<T>* 
 */
    Sequence<T>* append(T temp) override;
/**
 * @brief Вставка в начало ListSequence
 * 
 * @param temp 
 * @return Sequence<T>* 
 */
    Sequence<T>* prepend(T temp) override;
/**
 * @brief Вставка по индексу в ListSequence
 * 
 * @param temp 
 * @param index 
 * @return Sequence<T>* 
 */
    Sequence<T>* insert_at(T temp, size_t index) override;

/**
 * @brief Удаление по индексу в ListSequence
 * 
 * @param index 
 * @return Sequence<T>* 
 */
    Sequence<T>* pop_at(size_t index) override;

/**
 * @brief Удаление первого элемента в ListSequence
 * 
 * @return Sequence<T>* 
 */
    Sequence<T>* pop_front() override;

/**
 * @brief Удаление последнего элемента в ListSequence
 * 
 * @return Sequence<T>* 
 */
    Sequence<T>* pop_back() override;

/**
 * @brief Конкатенация для ListSequence
 * 
 * @param sequence 
 * @return Sequence<T>* 
 */
    Sequence<T>* concat(Sequence<T>* sequence) const override;
/**
 * @brief Получение подпоследовательности из ListSequence
 * 
 * @param start_index Индекс начала подпоследовательности
 * @param end_index Индекс конца подпоследовательности
 * @return Sequence<T>* 
 */
    Sequence<T>* get_subsequence(size_t start_index, size_t end_index) const override;

/**
 * @brief Получить итератор на начало ListSequence
 * 
 * @return ListIterator<T> 
 */
    ListIterator<T> begin();
/**
 * @brief Получить итератор на конец ListSequence
 * 
 * @return ListIterator<T> 
 */
    ListIterator<T> end();
/**
 * @brief Получить итератор для ListSequence
 * 
 * @return IEnumerator<T>* 
 */
    IEnumerator<T>* get_enumerator() const override;

/**
 * @brief map для ListSequence
 * 
 * @param func 
 * @return Sequence<T>* 
 */
    Sequence<T>* map(T (*func)(T)) override;
/**
 * @brief where для ListSequence
 * 
 * @param predicate 
 * @return Sequence<T>* 
 */
    Sequence<T>* where(bool (*predicate)(T)) override;
/**
 * @brief reduce для ListSequence
 * 
 * @param func 
 * @param accumulator 
 * @return T 
 */
    T reduce(T (*func)(T, T), T accumulator) override;

/**
 * @brief Оператор [] для ListSequence
 * 
 * @param index 
 * @return T& 
 */
    T& operator[](size_t index);
/**
 * @brief Оператор [] для ListSequence (const)
 * 
 * @param index 
 * @return const T& 
 */
    const T& operator[](size_t index) const;
};



#include "ListSequence.tpp"