#include "LinkedList.hpp"
#include "../exceptions/Exceptions.hpp"

template<class T>
LinkedList<T>::LinkedList() : length_(0), head_(nullptr), tail_(nullptr) {}

template<class T>
LinkedList<T>::LinkedList(T* items, size_t count) : LinkedList() {
    for (size_t index = 0; index < count; ++index) {
        append(items[index]);
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& source_list) : LinkedList() {
        for (const auto& item : source_list) {
            append(item);
        }
}

template<class T>
LinkedList<T>::LinkedList(const std::initializer_list<T>& linked_list) : LinkedList() {
    for (const auto& item : linked_list) {
        append(item);
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template<class T>
size_t LinkedList<T>::get_length() const {
    return length_;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::get_node(size_t index) const {
    if (index >= length_) {
        throw IndexOutOfRangeException("LinkedList: get_node. Индекс вне списка.");
    }
    Node* current;
    if (index < length_ / 2) {
        current = head_;
        for (size_t cur = 0; cur < index; ++cur) {
            current = current->next;
        }
    }
    else {
        current = tail_;
        for (size_t cur = length_ - 1; cur > index; --cur) {
            current = current->prev;
        }
    }
    return current;
}

template<class T>
T LinkedList<T>::get_first() const {
   if (length_ == 0) {
    throw EmptyListException("LinkedList: get_first. Список пуст.");
   }
   return head_->data;
}

template<class T>
T LinkedList<T>::get_last() const {
    if (length_ == 0) {
        throw EmptyListException("LinkedList: get_last. Список пуст.");
    }
    return tail_->data; 
}

template<class T>
T LinkedList<T>::get(size_t index) const {
    return get_node(index)->data;
}

template<class T>
T& LinkedList<T>::get_reference(size_t index) const {
    return get_node(index)->data;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::get_head() const {
    return head_;
}

template<class T>
void LinkedList<T>::append(T item) {
    Node* new_node = new Node(item);
    if (head_ == nullptr) {
        head_ = new_node;
        tail_ = new_node;
    }
    else {
        tail_->next = new_node;
        new_node->prev = tail_;
        tail_ = new_node;
    }
    length_++;
}

template<class T>
void LinkedList<T>::prepend(T item) {
    Node* new_node = new Node(item);
    if (head_ == nullptr) {
        head_ = new_node;
        tail_ = new_node;
    }
    else {
        head_->prev = new_node;
        new_node->next = head_;
        head_ = new_node;
    }
    length_++;
}

template<class T>
void LinkedList<T>::insert_at(T item, size_t index) {
    if (index >= length_) {
        throw IndexOutOfRangeException("LinkedList: insert_at. Индекс вне списка.");
    }
    if (index == length_) {
        append(item);
    }
    else if (index == 0) {
        prepend(item);
    }

    else {
        Node* target = get_node(index);
        Node* new_node = new Node(item);

        new_node->next = target;
        new_node->prev = target->prev;

        target->prev->next = new_node;
        target->prev = new_node;

        length_++;
    }
}

template<class T>
LinkedList<T>* LinkedList<T>::get_sublist(size_t start_index, size_t end_index) const {
    if (end_index >= length_ || start_index > end_index) {
        throw IndexOutOfRangeException("LinkedList: get_sublist. Некорректные индексы для подсписка.");
    }

    LinkedList<T>* sublist = new LinkedList<T>();
    Node* current = get_node(start_index);

    for (size_t cur = start_index; cur <= end_index; ++cur) {
        sublist->append(current->data);
        current = current->next;
    }
    return sublist;
}

template<class T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T>* list) {
    if (list == nullptr) {
        throw NullPointerException("LinkedList: concat. Передан нулевой указатель.");
    }
    LinkedList<T>* new_list = new LinkedList<T>(*this);
    Node* current = list->head_;
    
    while (current != nullptr) {
        new_list->append(current->data);
        current = current->next;
    }
    return new_list;
}

template<class T>
ListIterator<T> LinkedList<T>::begin() {
    return ListIterator<T>(head_);
}

template<class T>
ListIterator<T> LinkedList<T>::end() {
    return ListIterator<T>(nullptr);
}

template<class T>
ListIterator<T> LinkedList<T>::begin() const {
    return ListIterator<T>(head_);
}

template<class T>
ListIterator<T> LinkedList<T>::end() const {
    return ListIterator<T>(nullptr);
}