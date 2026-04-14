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
    }
    size_t size_;
    Node* head_;
    Node* tail_;

public:
    LinkedList();
    LinkedList(T* items, size_t count);
    LinkedList(LinkedList <T>& list const);
    //сюда initializer_list
    ~LinkedList();

    T get_first() const;
    T get_last() const;
    T get(size_t index);
    size_t get_length();
    
    LinkedList<T> get_sublist(size_t start_index, size_t end_index) const;
    LinkedList<T>* concat(LinkedList<T>* list);

    void append(T item);
    void prepend(T item);
    void insert_at (T item, size_t index);


};

#include "LinkedList.tpp"