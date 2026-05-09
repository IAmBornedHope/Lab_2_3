#pragma once
#include <cstddef>
#include <stdexcept>
#include <initializer_list>

template <typename T> class ListIterator;

template<class T>
class LinkedList {
    friend class ListIterator<T>;
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

    };
    size_t length_;
    Node* head_;
    Node* tail_;

public:
/**
 * @brief Конструктор по умолчанию для LinkedList
 * 
 */
    LinkedList();
/**
 * @brief Конструктор из массива для LinkedList
 * 
 * @param items 
 * @param count 
 */
    LinkedList(T* items, size_t count);
/**
 * @brief Конструктор копирования для LinkedList
 * 
 * @param list 
 */
    LinkedList(const LinkedList <T>& list);
/**
 * @brief initializer list для LinkedList
 * 
 * @param linked_list 
 */
    LinkedList(const std::initializer_list<T>& linked_list);
/**
 * @brief Деструктор для LinkedList
 * 
 */
    ~LinkedList();

/**
 * @brief Получить длину для LinkedList
 * 
 * @return size_t 
 */
    size_t get_length() const;
/**
 * @brief Получить первый элемент для LinkedList
 * 
 * @return T 
 */
    T get_first() const;
/**
 * @brief Получить последний элемент для LinkedList
 * 
 * @return T 
 */
    T get_last() const;
/**
 * @brief Получить узел по индексу для LinkedList
 * 
 * @param index 
 * @return Node* 
 */
    Node* get_node(size_t index) const;
/**
 * @brief Получить голову списка для LinkedList
 * 
 * @return Node* 
 */
    Node* get_head() const;
/**
 * @brief Получить ссылку на элемент для LinkedList
 * 
 * @param index 
 * @return T& 
 */
    T& get_reference(size_t index) const;
/**
 * @brief Вернуть элемент по индексу для LinkedList
 * 
 * @param index 
 * @return T 
 */
    T get(size_t index) const;

/**
 * @brief Добавить элемент в конец LinkedList
 * 
 * @param item 
 */
    void append(T item);
/**
 * @brief Добавить элемент в начало LinkedList
 * 
 * @param item 
 */
    void prepend(T item);
/**
 * @brief Вставка по индексу для LinkedList
 * 
 * @param item 
 * @param index 
 */
    void insert_at(T item, size_t index);

/**
 * @brief Удаление узла по индексу для LinkedList
 * 
 * @param index 
 */
    void pop_at(size_t index);

/**
 * @brief Удаление первого узла для LinkedList
 * 
 */
    void pop_first();

/**
 * @brief Удаление последнего узла для LinkedList
 * 
 */
    void pop_last();
/**
 * @brief Очистка LinkedList
 * 
 */
    void clear();

/**
 * @brief Получить подсписок для LinkedList
 * 
 * @param start_index 
 * @param end_index 
 * @return LinkedList<T>* 
 */
    LinkedList<T>* get_sublist(size_t start_index, size_t end_index) const;
/**
 * @brief Конкатенация для LinkedList
 * 
 * @param list 
 * @return LinkedList<T>* 
 */
    LinkedList<T>* concat(LinkedList<T>* list);

/**
 * @brief Получить итератор на начало для LinkedList
 * 
 * @return ListIterator<T> 
 */
    ListIterator<T> begin();
/**
 * @brief Получить итератор на конец для LinkedList
 * 
 * @return ListIterator<T> 
 */
    ListIterator<T> end();
/**
 * @brief Получить const итератор на начало для LinkedList
 * 
 * @return ListIterator<T> 
 */
    ListIterator<T> begin() const;
/**
 * @brief Получить const итератор на конец для LinkedList
 * 
 * @return ListIterator<T> 
 */
    ListIterator<T> end() const;

};
#include "ListIterator.hpp"
#include "LinkedList.tpp"