#pragma once
#include "../sequence/IEnumerator.hpp"
#include "../exceptions/Exceptions.hpp"

template<class T>
class ListIterator: public IEnumerator<T> {

public:
    using ptr = typename LinkedList<T>::Node*;
    using rfr = T&;
    
    explicit ListIterator(ptr p) : ptr_(p) {}

    const T& get_elem() const override {
        if (!ptr_) {
            throw IteratorPointerException("ListIterator: get_elem. Итератор не определен.");
        }
        return ptr_->data;
    }

    void next_elem() override {
        if (ptr_) {
            ptr_ = ptr_->next;
        }
    }

    bool is_end() const override {
        return ptr_ == nullptr;
    }
    
    rfr operator*() const {
        if (!ptr_) {
            throw IteratorPointerException("ListIterator: operator*. Попытка разыменования nullptr.");
        }
        return ptr_->data;
    }
    
    ListIterator& operator++() {
        if (ptr_) {
            ptr_ = ptr_->next;
        }
        return *this;
    }
    
    bool operator==(const ListIterator& r) const {
        return ptr_ == r.ptr_;
    }

    bool operator!=(const ListIterator& r) const {
        return ptr_ != r.ptr_;
    }

private:
    ptr ptr_;
};
