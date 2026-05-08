#include <gtest/gtest.h>
#include "../array_sequence/ArraySequence.hpp"
#include "../array_sequence/MutableArraySequence.hpp"
#include "../array_sequence/ImmutableArraySequence.hpp"
#include "../exceptions/Exceptions.hpp"

TEST(array_sequence_constructor, basic_constructor_test) {
    MutableArraySequence<int> sequence;
    EXPECT_EQ(sequence.get_length(), 0);
}

TEST(array_sequence_constructor, constructor_from_array_test) {
    int array[] = {1, 2, 3, 4};
    MutableArraySequence<int> sequence(array, 4);

    ASSERT_EQ(sequence.get_length(), 4);

    EXPECT_EQ(sequence.get(0), 1);
    EXPECT_EQ(sequence.get(1), 2);
    EXPECT_EQ(sequence.get(2), 3);
    EXPECT_EQ(sequence.get(3), 4);
}

TEST(array_sequence_constructor, constructor_from_array_test_2) {
    EXPECT_THROW(MutableArraySequence<int> array(nullptr, 4), NullPointerException);
}

TEST(array_sequence_constructor, copy_constructor) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> source(array, 3);
    MutableArraySequence<int> copy(source);

    ASSERT_EQ(copy.get_length(), 3);
    EXPECT_EQ(copy.get(0), 1);
    EXPECT_EQ(copy.get(1), 2);
    EXPECT_EQ(copy.get(2), 3);
}



TEST(array_sequence_elem_getters, correct_get_length) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    EXPECT_EQ(sequence.get_length(), 3);
}

TEST(array_sequence_elem_getters, correct_get_first) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    EXPECT_EQ(sequence.get(0), 1);
}

TEST(array_sequence_elem_getters, correct_get_last) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    EXPECT_EQ(sequence.get(2), 3);
}

TEST(array_sequence_elem_getters, correct_get_at) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    EXPECT_EQ(sequence.get(1), 2);
}

TEST(array_sequence_elem_getters, get_out_of_sequence) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    EXPECT_THROW(sequence.get(3), IndexOutOfRangeException);
}

TEST(array_sequence_elem_getters, get_below_zero) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    EXPECT_THROW(sequence.get(-1), IndexOutOfRangeException);
}

TEST(array_sequence_elem_getters, get_from_empty) {
    int array[] = {};
    MutableArraySequence<int> sequence(array, 0);
    EXPECT_THROW(sequence.get(0), IndexOutOfRangeException);
    EXPECT_THROW(sequence.get_first(), EmptyListException);
    EXPECT_THROW(sequence.get_last(), EmptyListException);
}



TEST(array_sequence_inserts, correct_append) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    sequence.append(20);

    ASSERT_EQ(sequence.get_length(), 4);
    EXPECT_EQ(sequence.get(3), 20);
}

TEST(array_sequence_inserts, correct_prepend) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    sequence.prepend(10);

    ASSERT_EQ(sequence.get_length(), 4);
    EXPECT_EQ(sequence.get(0), 10);
}

TEST(array_sequence_inserts, correct_insert_at) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    sequence.insert_at(5, 1);

    ASSERT_EQ(sequence.get_length(), 4);
    EXPECT_EQ(sequence.get(1), 5);
}

TEST(array_sequence_inserts, insert_out_of_sequence) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    EXPECT_THROW(sequence.insert_at(10, 4), IndexOutOfRangeException);
}

TEST(array_sequence_inserts, insert_below_zero) {
    int array[] = {1, 2, 3};
    MutableArraySequence<int> sequence(array, 3);
    EXPECT_THROW(sequence.insert_at(10, -1), IndexOutOfRangeException);
}



TEST(array_sequence_operations, correct_subsequence) {
    int array[] = {1, 2, 3, 4, 5};

    MutableArraySequence<int> sequence(array, 5);
    Sequence<int>* subsequence = sequence.get_subsequence(0, 3);

    ASSERT_EQ(subsequence->get_length(), 4);
    EXPECT_EQ(subsequence->get(0), 1);
    EXPECT_EQ(subsequence->get(1), 2);
    EXPECT_EQ(subsequence->get(2), 3);
    EXPECT_EQ(subsequence->get(3), 4);
    delete subsequence;
}

TEST(array_sequence_operations, incorrect_subsequence) {
    int array[] = {1, 2, 3, 4, 5};

    MutableArraySequence<int> sequence(array, 5);
    EXPECT_THROW(sequence.get_subsequence(0, 6), IndexOutOfRangeException);
}

TEST(array_sequence_operations, correct_concat) {
    int array_1[] = {1, 2};
    int array_2[] = {3, 4};

    MutableArraySequence<int> first(array_1, 2);
    MutableArraySequence<int> second(array_2, 2);

    Sequence<int>* result = first.concat(&second);

    ASSERT_EQ(result->get_length(), 4);
    EXPECT_EQ(result->get(0), 1);
    EXPECT_EQ(result->get(1), 2);
    EXPECT_EQ(result->get(2), 3);
    EXPECT_EQ(result->get(3), 4);
    delete result;
}

TEST(array_sequence_operations, concat_nullptr) {
    int array[] = {1, 2};
    MutableArraySequence<int> sequence(array, 2);
    EXPECT_THROW(sequence.concat(nullptr), NullPointerException);
}

TEST(array_sequence_functions, correct_map) {
    int array[] = {1, 2, 3, 4};
    MutableArraySequence<int> sequence(array, 4);

    auto mul = [](int x) {
        return [x](int y) {
            return x*y;
        };
    };
    auto sq = [mul](int x) { return mul(x)(x); };

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

TEST(array_sequence_functions, correct_where) {
    int array[] = {1, 2, 3, 4};
    MutableArraySequence<int> sequence(array, 4);

    auto pred = [](int x) {
        return x % 2 != 0;
    };

    Sequence<int>* filtered = sequence.where(pred);
    ASSERT_EQ(filtered->get_length(), 2);
    EXPECT_EQ(filtered->get(0), 1);
    EXPECT_EQ(filtered->get(1), 3);
    delete filtered;
}

TEST(array_sequence_functions, correct_reduce) {
    int array[] = {1, 2, 3, 4};
    MutableArraySequence<int> sequence(array, 4);

    auto reducer = [](int a, int b) {
        return a + b;
    };
    int reduced = sequence.reduce(reducer, 0);
    EXPECT_EQ(reduced, 10);
}
