#pragma once
#include <concepts>
#include "../array_sequence/MutableArraySequence.hpp"
#include "../sequence/Sequence.hpp"

template<typename Container, typename T>
concept Stackable = requires(Container& container, T value, size_t index) {
    { container.append(value) };
    { container.pop_back() };
    { container.begin() };
    { container.end() };
    { container.get(index) } -> std::common_reference_with<T>;
    { container.get_last() } -> std::common_reference_with<T>;
    { container.get_length() } -> std::convertible_to<size_t>;
};

template<typename T, template<typename> class Container>
requires Stackable<Container<T>, T>
class Stack {
private:
    Container<T>* items_;
public:
    Stack();
    Stack(const Container<T>& container);
    ///
    Stack(const Stack<T, Container>& stack);
    Stack<T, Container>& operator=(const Stack<T, Container>& stack);
    ~Stack();

    void push(const T& temp);
    void pop();
    T top() const;
    bool is_empty() const;
    size_t get_length() const;

    auto map(T (*func)(T)) const;
    auto where(bool (*predicate)(T)) const;
    T reduce(T (*func)(T, T), T starter) const;

    auto concat(const Stack<T, Container>& stack) const;
    auto get_substack(size_t start_index, size_t end_index) const;
    bool search(const Stack<T, Container>& substack) const;

    auto begin();
    auto end();
    auto begin() const;
    auto end() const;
    
};

#include "Stack.tpp"
