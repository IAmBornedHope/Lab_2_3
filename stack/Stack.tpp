#include <cstddef>
#include "Stack.hpp"

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container>::Stack() : items_(new Container<T>()) {}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container>::Stack(const Container<T>& container) {
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
    items_->pop_last();
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
Stack<T, Container> Stack<T, Container>::map(T (*func)(T)) {
    Stack<T, Container> mapped;
        for (auto& item : *this) {
            mapped.push(func(item));
        }
        return mapped;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container> Stack<T, Container>::where(bool (*predicate)(T)) {
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
T Stack<T, Container>::reduce(T (*func)(T, T), T starter) {
    T reduced = starter;
    for (auto& item : *this) {
        reduced = func(reduced, item);
    }
    return reduced;
}

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
Stack<T, Container> Stack<T, Container>::concat(Stack<T, Container>& stack) {
    Stack<T, Container> result(*this);
    for (auto& item: stack) {
        result.push(item);
    }
    return result;
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


