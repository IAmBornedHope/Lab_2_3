#include <cstddef>
#include "Stack.hpp"

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container>::Stack() : items_(new Container<T>()) {}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container>::Stack(const Container<T>& container) {/////
    items_ = new Container<T>(container);
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container>::Stack(const Stack<T, Container>& stack) {
    items_ = new Container<T>(*stack.items_);
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container>& Stack<T, Container>::operator=(const Stack<T, Container>& stack) {
    if (this != &stack) {
        delete items_;
        items_ = new Container<T>(*stack.items_);
    }
    return *this;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container>::~Stack() {
    delete items_;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
void Stack<T, Container>::push(const T& temp) {
    items_->append(temp);
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
void Stack<T, Container>::pop() {
    if (is_empty()) {
        throw EmptyListException("Stack: pop. Стек пуст.");
    }
    items_->pop_back();
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
T Stack<T, Container>::top() const {
    if (is_empty()) {
        throw EmptyListException("Stack: top. Стек пуст.");
    }
    return items_->get_last();
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
bool Stack<T, Container>::is_empty() const {
    return items_->get_length() == 0;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
size_t Stack<T, Container>::get_length() const {
    return items_->get_length();
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container> Stack<T, Container>::map(T (*func)(T)) const {
    Stack<T, Container> mapped;
        for (auto& item : *this) {
            mapped.push(func(item));
        }
        return mapped;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
auto Stack<T, Container>::where(bool (*predicate)(T)) const {
    Stack<T, Container> filtered;
        for (auto& item : *this) {
            if(predicate(item)) {
                filtered.push(item);
            }
        }
        return filtered;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
T Stack<T, Container>::reduce(T (*func)(T, T), T starter) const {
    T reduced = starter;
    for (auto& item : *this) {
        reduced = func(reduced, item);
    }
    return reduced;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container> Stack<T, Container>::concat(const Stack<T, Container>& stack) const {
    Stack<T, Container> result(*this);
    for (auto& item: stack) {
        result.push(item);
    }
    return result;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container> Stack<T, Container>::get_substack(size_t start_index, size_t end_index) const {
    if (end_index >= get_length() || start_index > end_index) {
        throw IndexOutOfRangeException("Stack: get_substack. Некорректные индексы для подпоследовательности.");
    }
    Stack<T, Container> substack;
    size_t current = 0;
    for (auto& item : *this) {
        if (current > end_index) break;
        if (current >= start_index) {
            substack.push(item);
        }
        ++current;
    }
    return substack;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
bool Stack<T, Container>::search(const Stack<T, Container>& substack) const {
    size_t length = get_length();
    size_t sub_length = substack.get_length();

    if (sub_length > length) return false;
    if (sub_length == 0) return true;

    for (size_t start = 0; start <= length - sub_length; ++start) {
        bool flag = true;
        for (size_t current = 0; current < sub_length; ++current) {
            if (items_->get(start + current) != substack.items_->get(current)) {
                flag = false;
                break;
            }
        }
        if (flag) return true;
    }
    return false;

}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
auto Stack<T, Container>::begin() {
    return items_->begin();
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
auto Stack<T, Container>::end() {
    return items_->end();
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
auto Stack<T, Container>::begin() const {
    return items_->begin();
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
auto Stack<T, Container>::end() const {
    return items_->end();
}



