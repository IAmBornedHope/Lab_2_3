#pragma once
#include <cstddef>
#include <stdexcept>

template<class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

    };
    size_t length_;
    Node* head_;
    Node* tail_;

public:
    LinkedList();
    LinkedList(T* items, size_t count);
    LinkedList(const LinkedList <T>& list);
    //сюда initializer_list
    ~LinkedList();

    size_t get_length() const;
    T get_first() const;
    T get_last() const;
    Node* get_node(size_t index) const;
    T get(size_t index) const;

    void append(T item);
    void prepend(T item);
    void insert_at(T item, size_t index);
    
    LinkedList<T>* get_sublist(size_t start_index, size_t end_index) const;
    LinkedList<T>* concat(LinkedList<T>* list);

};

#include "LinkedList.tpp"