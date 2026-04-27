#include <gtest/gtest.h>
#include "../list_sequence/ListSequence.hpp"
#include "../list_sequence/MutableListSequence.hpp"
#include "../list_sequence/ImmutableListSequence.hpp"
#include "../exceptions/Exceptions.hpp"

TEST(list_sequence_constructor, basic_constructor_test) {
    MutableListSequence<int> sequence;
    EXPECT_EQ(sequence.get_length(), 0);
}

TEST(list_sequence_constructor, constructor_from_array_test) {
    int array[] = {1, 2, 3, 4};
    MutableListSequence<int> sequence(array, 4);

    ASSERT_EQ(sequence.get_length(), 4);

    EXPECT_EQ(sequence.get(0), 1);
    EXPECT_EQ(sequence.get(1), 2);
    EXPECT_EQ(sequence.get(2), 3);
    EXPECT_EQ(sequence.get(3), 4);
}

TEST(list_sequence_constructor, constructor_from_array_test_2) {
    EXPECT_THROW(MutableListSequence<int> array(nullptr, 4), NullPointerException);
}

TEST(list_sequence_constructor, copy_constructor) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> source(array, 3);
    MutableListSequence<int> copy(source);

    ASSERT_EQ(copy.get_length(), 3);
    EXPECT_EQ(copy.get(0), 1);
    EXPECT_EQ(copy.get(1), 2);
    EXPECT_EQ(copy.get(2), 3);
}



TEST(list_sequence_elem_getters, correct_get_length) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    EXPECT_EQ(sequence.get_length(), 3);
}

TEST(list_sequence_elem_getters, correct_get_first) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    EXPECT_EQ(sequence.get(0), 1);
}

TEST(list_sequence_elem_getters, correct_get_last) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    EXPECT_EQ(sequence.get(2), 3);
}

TEST(list_sequence_elem_getters, correct_get_at) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    EXPECT_EQ(sequence.get(1), 2);
}

TEST(list_sequence_elem_getters, get_out_of_sequence) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    EXPECT_THROW(sequence.get(3), IndexOutOfRangeException);
}

TEST(list_sequence_elem_getters, get_below_zero) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    EXPECT_THROW(sequence.get(-1), IndexOutOfRangeException);
}

TEST(list_sequence_elem_getters, get_from_empty) {
    int array[] = {};
    MutableListSequence<int> sequence(array, 0);
    EXPECT_THROW(sequence.get(0), IndexOutOfRangeException);
    EXPECT_THROW(sequence.get_first(), EmptyListException);
    EXPECT_THROW(sequence.get_last(), EmptyListException);
}



TEST(list_sequence_inserts, correct_append) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    sequence.append(20);

    ASSERT_EQ(sequence.get_length(), 4);
    EXPECT_EQ(sequence.get(3), 20);
}

TEST(list_sequence_inserts, correct_prepend) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    sequence.prepend(10);

    ASSERT_EQ(sequence.get_length(), 4);
    EXPECT_EQ(sequence.get(0), 10);
}

TEST(list_sequence_inserts, correct_insert_at) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    sequence.insert_at(5, 1);

    ASSERT_EQ(sequence.get_length(), 4);
    EXPECT_EQ(sequence.get(1), 5);
}

TEST(list_sequence_inserts, insert_out_of_sequence) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    EXPECT_THROW(sequence.insert_at(10, 4), IndexOutOfRangeException);
}

TEST(list_sequence_inserts, insert_below_zero) {
    int array[] = {1, 2, 3};
    MutableListSequence<int> sequence(array, 3);
    EXPECT_THROW(sequence.insert_at(10, -1), IndexOutOfRangeException);
}



TEST(list_sequence_operations, correct_subsequence) {
    int array[] = {1, 2, 3, 4, 5};

    MutableListSequence<int> sequence(array, 5);
    Sequence<int>* subsequence = sequence.get_subsequence(0, 3);

    ASSERT_EQ(subsequence->get_length(), 4);
    EXPECT_EQ(subsequence->get(0), 1);
    EXPECT_EQ(subsequence->get(1), 2);
    EXPECT_EQ(subsequence->get(2), 3);
    EXPECT_EQ(subsequence->get(3), 4);
    delete subsequence;
}

TEST(list_sequence_operations, incorrect_subsequence) {
    int array[] = {1, 2, 3, 4, 5};

    MutableListSequence<int> sequence(array, 5);
    EXPECT_THROW(sequence.get_subsequence(0, 6), IndexOutOfRangeException);
}

TEST(list_sequence_operations, correct_concat) {
    int array_1[] = {1, 2};
    int array_2[] = {3, 4};

    MutableListSequence<int> first(array_1, 2);
    MutableListSequence<int> second(array_2, 2);

    Sequence<int>* result = first.concat(&second);

    ASSERT_EQ(result->get_length(), 4);
    EXPECT_EQ(result->get(0), 1);
    EXPECT_EQ(result->get(1), 2);
    EXPECT_EQ(result->get(2), 3);
    EXPECT_EQ(result->get(3), 4);
    delete result;
}

TEST(list_sequence_operations, concat_nullptr) {
    int array[] = {1, 2};
    MutableListSequence<int> sequence(array, 2);
    EXPECT_THROW(sequence.concat(nullptr), NullPointerException);
}

TEST(list_sequence_functions, correct_map) {
    int array[] = {1, 2, 3, 4};
    MutableListSequence<int> sequence(array, 4);

    auto square = [](int x) {
        return x * x;
    };

    Sequence<int>* mapped = sequence.map(square);
    ASSERT_EQ(mapped->get_length(), 4);
    EXPECT_EQ(mapped->get(0), 1);
    EXPECT_EQ(mapped->get(1), 4);
    EXPECT_EQ(mapped->get(2), 9);
    EXPECT_EQ(mapped->get(3), 16);
    delete mapped;
}

TEST(list_sequence_functions, correct_where) {
    int array[] = {1, 2, 3, 4};
    MutableListSequence<int> sequence(array, 4);

    auto pred = [](int x) {
        return x % 2 != 0;
    };

    Sequence<int>* filtered = sequence.where(pred);
    ASSERT_EQ(filtered->get_length(), 2);
    EXPECT_EQ(filtered->get(0), 1);
    EXPECT_EQ(filtered->get(1), 3);
    delete filtered;
}

TEST(list_sequence_functions, correct_reduce) {
    int array[] = {1, 2, 3, 4};
    MutableListSequence<int> sequence(array, 4);

    auto reducer = [](int a, int b) {
        return a + b;
    };
    int reduced = sequence.reduce(reducer, 0);
    EXPECT_EQ(reduced, 10);
}
