#pragma once
#include <concepts>
#include <cstddef>
#include "../Sequence/Sequence.hpp"
#include "../dynamic_array/DynamicArray.hpp"

using std::integral;
template <integral T> class BitIterator;

/**
 * @brief Структура бита
 * 
 * @tparam T 
 */
template<integral T>
class Bit {
private:
    T value_;

public:
/**
 * @brief Конструктор Bit по умолчанию
 * 
 */
    Bit() = default;
/**
 * @brief Конструктор копирования для Bit
 * 
 * @param b 
 */
    Bit(const Bit& b) = default;
/**
 * @brief Конструктор по значению для Bit
 * 
 * @param o 
 */
    Bit(T o) : value_(o) {}

/**
 * @brief Получить настоящий бит по индексу
 * 
 * @param index 
 * @return true 
 * @return false 
 */
    bool get_bit_at(size_t index) const {
        return (value_ >> index) & static_cast<T>(1);
    }
};

template<integral T>
class BitSequence: public Sequence<Bit<T>> {
private:
    DynamicArray<T>* data_;
    size_t size_;

    static constexpr size_t BITS_IN_BATCH = sizeof(T) * 8;
    size_t get_batch_index(size_t index) const {return index / BITS_IN_BATCH;}
    size_t get_bit_index(size_t index) const {return index % BITS_IN_BATCH;}
    size_t get_batch_count() const {return size_ / BITS_IN_BATCH + (size_ % BITS_IN_BATCH != 0);}

public:
/**
 * @brief Конструктор по умолчанию для BitSequence
 * 
 */
    BitSequence();
/**
 * @brief Конструктор копирования для BitSequence
 * 
 * @param source_sequence 
 */
    BitSequence(const BitSequence<T>& source_sequence);
/**
 * @brief Конструктор из массива для BitSequence
 * 
 * @param bits 
 * @param count 
 */
    BitSequence(bool* bits, size_t count);
/**
 * @brief Конструктор по размеру для BitSequence
 * 
 * @param size 
 */
    BitSequence(size_t size);
/**
 * @brief Деструктор для BitSequence
 * 
 */
    ~BitSequence() override;

/**
 * @brief Получить бит по индексу
 * 
 * @param index 
 * @return true 
 * @return false 
 */
    bool get_bit_at(size_t index) const;
/**
 * @brief Установить бит по индексу
 * 
 * @param index 
 * @param value 
 */
    void set_bit_at(size_t index, bool value);

/**
 * @brief Получить первый Bit
 * 
 * @return Bit<T> 
 */
    Bit<T> get_first() const override;
/**
 * @brief Получить последний Bit
 * 
 * @return Bit<T> 
 */
    Bit<T> get_last() const override;
/**
 * @brief Получить Bit по индексу
 * 
 * @param index 
 * @return Bit<T> 
 */
    Bit<T> get(size_t index) const override;
/**
 * @brief Получить длину BitSequence
 * 
 * @return size_t 
 */
    size_t get_length() const override;
/**
 * @brief Получить подпоследовательность BitSequence
 * 
 * @param start_index Индекс начала подпоследовательности
 * @param end_index Индекс конца подпоследовательности
 * @return Sequence<Bit<T>>* 
 */
    Sequence<Bit<T>>* get_subsequence(size_t start_index, size_t end_index) const override;
/**
 * @brief Очистка BitSequence
 * 
 */
    void clear() override;

/**
 * @brief Вставка Bit в конец BitSequence
 * 
 * @param temp 
 * @return Sequence<Bit<T>>* 
 */
    Sequence<Bit<T>>* append(Bit<T> temp) override;
/**
 * @brief Вставка Bit в начало BitSequence
 * 
 * @param temp 
 * @return Sequence<Bit<T>>* 
 */
    Sequence<Bit<T>>* prepend(Bit<T> temp) override;
/**
 * @brief Вставка Bit в BitSequence по индексу
 * 
 * @param temp 
 * @param index 
 * @return Sequence<Bit<T>>* 
 */
    Sequence<Bit<T>>* insert_at(Bit<T> temp, size_t index) override;
/**
 * @brief Конкатенация BitSequence
 * 
 * @param sequence 
 * @return Sequence<Bit<T>>* 
 */
    Sequence<Bit<T>>* concat(Sequence<Bit<T>>* sequence) const override;

/**
 * @brief Логическое "И" между BitSequence
 * 
 * @param sequence 
 * @return BitSequence<T>* 
 */
    BitSequence<T>* And(const BitSequence<T>& sequence) const;
/**
 * @brief Логическое "ИЛИ" между BitSequence
 * 
 * @param sequence 
 * @return BitSequence<T>* 
 */
    BitSequence<T>* Or(const BitSequence<T>& sequence) const;
/**
 * @brief Логическое "НЕ" над BitSequence
 * 
 * @return BitSequence<T>* 
 */
    BitSequence<T>* Not() const;
/**
 * @brief Логическое "ИЛИ-НЕ" между BitSequence
 * 
 * @param sequence 
 * @return BitSequence<T>* 
 */
    BitSequence<T>* Xor(const BitSequence<T>& sequence) const;

    BitSequence<T> operator&(const BitSequence<T>& sequence) const;
    BitSequence<T> operator|(const BitSequence<T>& sequence) const;
    BitSequence<T> operator~() const;
    BitSequence<T> operator^(const BitSequence<T>& sequence) const;

/**
 * @brief Получить итератор на начало BitSequence
 * 
 * @return BitIterator<T> 
 */
    BitIterator<T> begin();
/**
 * @brief Получить итератор на конец BitSequence
 * 
 * @return BitIterator<T> 
 */
    BitIterator<T> end();
/**
 * @brief Получить const итератор на начало BitSequence
 * 
 * @return BitIterator<T> 
 */
    BitIterator<T> begin() const;
/**
 * @brief Получить const итератор на конец BitSequence
 * 
 * @return BitIterator<T> 
 */
    BitIterator<T> end() const;
/**
 * @brief Получить итератор для BitSequence
 * 
 * @return IEnumerator<Bit<T>>* 
 */
    IEnumerator<Bit<T>>* get_enumerator() const override;

/**
 * @brief map для BitSequence
 * 
 * @param func 
 * @return Sequence<Bit<T>>* 
 */
    Sequence<Bit<T>>* map(Bit<T> (*func)(Bit<T>)) override;
/**
 * @brief where для BitSequence
 * 
 * @param predicate 
 * @return Sequence<Bit<T>>* 
 */
    Sequence<Bit<T>>* where(bool (*predicate)(Bit<T>)) override;
/**
 * @brief reduce для BitSequence
 * 
 * @param func 
 * @param accumulator 
 * @return Bit<T> 
 */
    Bit<T> reduce(Bit<T> (*func)(Bit<T>, Bit<T>), Bit<T> accumulator) override;

};

#include "BitIterator.hpp"
#include "BitSequence.tpp"


