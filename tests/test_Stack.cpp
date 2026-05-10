#include <gtest/gtest.h>
#include "../array_sequence/MutableArraySequence.hpp"
#include "../list_sequence/MutableListSequence.hpp"
#include "../stack/Stack.hpp"

TEST(stack_constructor, basic_constructor_test) {
    Stack<int, MutableArraySequence> stack;
    EXPECT_EQ(stack.get_length(), 0);
}

TEST(stack_constructor, basic_constructor_test2) {
    Stack<int, MutableListSequence> stack;
    EXPECT_EQ(stack.get_length(), 0);
}

TEST(stack_constructor, constructor_from_arraysequence_test) {
    int array[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> sequence(array, 5);
    Stack<int, MutableArraySequence> stack(sequence);

    ASSERT_EQ(stack.get_length(), 5);
    EXPECT_EQ(stack.top(), 5);
}

TEST(stack_constructor, constructor_from_listsequence_test) {
    int array[] = {1, 2, 3, 4, 5};
    MutableListSequence<int> sequence(array, 5);
    Stack<int, MutableListSequence> stack(sequence);

    ASSERT_EQ(stack.get_length(), 5);
    EXPECT_EQ(stack.top(), 5);
}

TEST(stack_constructor, copy_constructor_test) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    Stack<int, MutableArraySequence> stack(sequence);
    Stack<int, MutableArraySequence> copy(stack);

    ASSERT_EQ(copy.get_length(), 3);
    EXPECT_EQ(copy.top(), 3);
    copy.pop();
    EXPECT_EQ(copy.top(), 2);
    copy.pop();
    EXPECT_EQ(copy.top(), 1);
    EXPECT_EQ(stack.get_length(), 3);
}



TEST(stack_assignment, correct_assignment_test) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> source(array, 3);
    Stack<int, MutableArraySequence> stack(source);
    Stack<int, MutableArraySequence> result;

    result = stack;

    ASSERT_EQ(result.get_length(), 3);
    EXPECT_EQ(result.top(), 3);
    result.pop();
    EXPECT_EQ(result.top(), 2);
    result.pop();
    EXPECT_EQ(result.top(), 1);
    EXPECT_EQ(stack.get_length(), 3);
}

TEST(stack_assignment, self_assignment) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    Stack<int, MutableArraySequence> stack(sequence);
    stack = stack;

    ASSERT_EQ(stack.get_length(), 3);
    EXPECT_EQ(stack.top(), 3);
}



TEST(stack_basic_operations, push_test) {
    Stack<int, MutableArraySequence> stack;
    stack.push(10);
    ASSERT_EQ(stack.get_length(), 1);
    EXPECT_EQ(stack.top(), 10);
}

TEST(stack_basic_operations, pop_test) {
    Stack<int, MutableArraySequence> stack;
    stack.push(10);
    EXPECT_EQ(stack.get_length(), 1);
    stack.pop();
    EXPECT_EQ(stack.is_empty(), 1);
}

TEST(stack_basic_operations, empty_pop_test) {
    Stack<int, MutableArraySequence> stack;
    EXPECT_THROW(stack.pop(), EmptyListException);
}

TEST(stack_basic_operations, empty_top_test) {
    Stack<int, MutableArraySequence> stack;
    EXPECT_THROW(stack.top(), EmptyListException);
}

TEST(stack_basic_operations, top_test) {
    Stack<int, MutableArraySequence> stack;
    stack.push(10);
    EXPECT_EQ(stack.get_length(), 1);
    EXPECT_EQ(stack.top(), 10);
    stack.push(20);
    EXPECT_EQ(stack.top(), 20);
}

TEST(stack_basic_operations, is_empty_test) {
    Stack<int, MutableArraySequence> stack;
    EXPECT_EQ(stack.is_empty(), 1);
    stack.push(10);
    EXPECT_EQ(stack.is_empty(), 0);
    stack.pop();
    EXPECT_EQ(stack.is_empty(), 1);
}

TEST(stack_basic_operations, get_length_test) {
    Stack<int, MutableArraySequence> stack;
    stack.push(10);
    stack.push(10);
    stack.push(10);
    EXPECT_EQ(stack.get_length(), 3);
}



TEST(stack_functions, map_test) {
    Stack<int, MutableArraySequence> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    auto square = [](int x) {
        return x * x;
    };

    Stack<int, MutableArraySequence> mapped = stack.map(square);
    ASSERT_EQ(mapped.get_length(), 3);
    EXPECT_EQ(mapped.top(), 9);
    mapped.pop();
    EXPECT_EQ(mapped.top(), 4);
    mapped.pop();
    EXPECT_EQ(mapped.top(), 1);
}

TEST(stack_functions, where_test) {
    Stack<int, MutableArraySequence> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    
    auto pred = [](int x) {
        return x % 2 != 0;
    };

    Stack<int, MutableArraySequence> mapped = stack.where(pred);
    ASSERT_EQ(mapped.get_length(), 2);
    EXPECT_EQ(mapped.top(), 3);
    mapped.pop();
    EXPECT_EQ(mapped.top(), 1);
}

TEST(stack_functions, reduce_test) {
    Stack<int, MutableArraySequence> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    
    auto reducer = [](int a, int b) {
        return a + b;
    };

    int reduced = stack.reduce(reducer, 0);
    EXPECT_EQ(reduced, 10);
}



TEST(stack_concat, concat_test) {
    Stack<int, MutableArraySequence> first;
    Stack<int, MutableArraySequence> second;
    first.push(1);
    first.push(2);
    second.push(3);
    second.push(4);
    
    Stack<int, MutableArraySequence> result = first.concat(second);
  
    ASSERT_EQ(result.get_length(), 4);
    EXPECT_EQ(result.top(), 4);
    result.pop();
    EXPECT_EQ(result.top(), 3);
    result.pop();
    EXPECT_EQ(result.top(), 2);
    result.pop();
    EXPECT_EQ(result.top(), 1);
}