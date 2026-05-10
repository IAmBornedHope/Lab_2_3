#include <gtest/gtest.h>
#include "../square_matrix/SquareMatrix.hpp"
#include "../list_sequence/MutableListSequence.hpp"

TEST(matrix_constructor, basic_constructor_test) {
    SquareMatrix<int, MutableArraySequence> matrix{};
    ASSERT_EQ(matrix.get_size(), 0);
}

TEST(matrix_constructor, basic_constructor_test2) {
    SquareMatrix<int, MutableListSequence> matrix{};
    ASSERT_EQ(matrix.get_size(), 0);
}

TEST(matrix_constructor, constructor_by_size_test) {
    SquareMatrix<int, MutableListSequence> matrix(3);
    ASSERT_EQ(matrix.get_size(), 3);
}

TEST(matrix_constructor, copy_constructor_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};
    SquareMatrix<int, MutableArraySequence> copy(matrix);

    ASSERT_EQ(copy.get_size(), 2);
    EXPECT_EQ(copy[0][0], 1);
    EXPECT_EQ(copy[0][1], 2);
    EXPECT_EQ(copy[1][0], 3);
    EXPECT_EQ(copy[1][1], 4);
}



TEST(matrix_assignment, correct_assignment_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};
    SquareMatrix<int, MutableArraySequence> result{};

    result = matrix;
    ASSERT_EQ(result.get_size(), 2);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 2);
    EXPECT_EQ(result[1][0], 3);
    EXPECT_EQ(result[1][1], 4);
}

TEST(matrix_assignment, self_assignment_test) {
    SquareMatrix<int, MutableArraySequence> result = {{1, 2}, {3, 4}};

    result = result;
    ASSERT_EQ(result.get_size(), 2);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 2);
    EXPECT_EQ(result[1][0], 3);
    EXPECT_EQ(result[1][1], 4);
}

TEST(matrix_init_list, correct_init_list_test) {
    SquareMatrix<int, MutableArraySequence> result = {{1, 2}, {3, 4}};

    ASSERT_EQ(result.get_size(), 2);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 2);
    EXPECT_EQ(result[1][0], 3);
    EXPECT_EQ(result[1][1], 4);
}

TEST(matrix_getters, correct_get_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(1, 1), 4);
}

TEST(matrix_getters, index_below_zero_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    EXPECT_THROW(matrix.get(-1, 0), IndexOutOfRangeException);
}

TEST(matrix_getters, index_out_of_matrix_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    EXPECT_THROW(matrix.get(2, 0), IndexOutOfRangeException);
}

TEST(matrix_getters, get_size_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    ASSERT_EQ(matrix.get_size(), 2);
}

TEST(matrix_getters, short_getter_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    ASSERT_EQ(matrix[0][0], 1);
    ASSERT_EQ(matrix[1][1], 4);
}

TEST(matrix_getters, incorrect_short_getter_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    EXPECT_THROW(matrix[-1][0], IndexOutOfRangeException);
}

TEST(matrix_getters, incorrect_short_getter_test_2) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    EXPECT_THROW(matrix[2][0], IndexOutOfRangeException);
}



TEST(matrix_setters, correct_set_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};
    matrix.set(0, 0, 999);

    EXPECT_EQ(matrix[0][0], 999);
}

TEST(matrix_setters, incorrect_set_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    EXPECT_THROW(matrix.set(-1, 0, 999), IndexOutOfRangeException);
}

TEST(matrix_setters, set_out_of_matrix_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};

    EXPECT_THROW(matrix.set(2, 0, 999), IndexOutOfRangeException);
}

TEST(matrix_setters, short_set_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};
    matrix[0][0] = 999;

    EXPECT_EQ(matrix[0][0], 999);
}

TEST(matrix_setters, incorrect_short_set_test) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};
    
    EXPECT_THROW(matrix[-1][0] = 999, IndexOutOfRangeException);
}

TEST(matrix_setters, incorrect_short_set_test_2) {
    SquareMatrix<int, MutableArraySequence> matrix = {{1, 2}, {3, 4}};
    
    EXPECT_THROW(matrix[2][0] = 999, IndexOutOfRangeException);
}



TEST(matrix_operations, correct_matrix_add_test) {
    SquareMatrix<int, MutableArraySequence> matrix_1 = {{1, 2}, {3, 4}};
    SquareMatrix<int, MutableArraySequence> matrix_2 = {{4, 3}, {2, 1}};
    
    SquareMatrix<int, MutableArraySequence> result = matrix_1.add(matrix_2);
    ASSERT_EQ(result.get_size(), 2);
    EXPECT_EQ(result[0][0], 5);
    EXPECT_EQ(result[0][1], 5);
    EXPECT_EQ(result[1][0], 5);
    EXPECT_EQ(result[1][1], 5);

}

TEST(matrix_operations, incorrect_matrix_add_test) {
    SquareMatrix<int, MutableArraySequence> matrix_1 = {{1, 2}, {3, 4}};
    SquareMatrix<int, MutableArraySequence> matrix_2 = {{1}};
    
    SquareMatrix<int, MutableArraySequence> result{};
    EXPECT_THROW(result = matrix_1.add(matrix_2), MatrixSizeMismatchException);
}

TEST(matrix_operations, matrix_on_scalar_test) {
    SquareMatrix<int, MutableArraySequence> matrix_1 = {{1, 2}, {3, 4}};
    int scalar = 8;
    
    SquareMatrix<int, MutableArraySequence> result = matrix_1.multiply_on_scalar(scalar);
    EXPECT_EQ(result[0][0], 8);
    EXPECT_EQ(result[0][1], 16);
    EXPECT_EQ(result[1][0], 24);
    EXPECT_EQ(result[1][1], 32);
}