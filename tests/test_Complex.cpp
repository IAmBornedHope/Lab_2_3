#include <gtest/gtest.h>
#include "../my_types/Complex.hpp"
#include "Exceptions.hpp"

TEST(complex_constructor, basic_constructor_int_test) {
    Complex<int> z;

    EXPECT_EQ(z.get_re(), 0);
    EXPECT_EQ(z.get_im(), 0);
}

TEST(complex_constructor, basic_constructor_double_test) {
    Complex<double> z;

    EXPECT_EQ(z.get_re(), 0.0);
    EXPECT_EQ(z.get_im(), 0.0);
}

TEST(complex_constructor, value_constructor_int_test) {
    Complex<int> z(5, 10);

    EXPECT_EQ(z.get_re(), 5);
    EXPECT_EQ(z.get_im(), 10);
}

TEST(complex_constructor, value_constructor_double_test) {
    Complex<double> z(1.4, 4.2);

    EXPECT_EQ(z.get_re(), 1.4);
    EXPECT_EQ(z.get_im(), 4.2);
}



TEST(complex_setters, setter_int_test) {
    Complex<int> z;
    z.set_re(10);
    z.set_im(2);

    EXPECT_EQ(z.get_re(), 10);
    EXPECT_EQ(z.get_im(), 2);
}

TEST(complex_setters, setter_double_test) {
    Complex<double> z;
    z.set_re(-1.8);
    z.set_im(4.3);

    EXPECT_EQ(z.get_re(), -1.8);
    EXPECT_EQ(z.get_im(), 4.3);
}



TEST(complex_operators, unary_minus_int_test) {
    Complex<int> z(3, -3);
    Complex<int> result = -z;
    Complex<int> expected(-3, 3);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, unary_minus_double_test) {
    Complex<double> z(1.0, -5.2);
    Complex<double> result = -z;
    Complex<double> expected(-1.0, 5.2);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, binary_plus_int_test) {
    Complex<int> z1(1, 2);
    Complex<int> z2(2, 3);
    Complex<int> result = z1 + z2;
    Complex<int> expected = Complex<int>(3, 5);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, binary_plus_double_test) {
    Complex<double> z1(1.2, 2.5);
    Complex<double> z2(2.1, -3.0);
    Complex<double> result = z1 + z2;
    Complex<double> expected = Complex<double>(3.3, -0.5);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, binary_minus_int_test) {
    Complex<int> z1(10, 5);
    Complex<int> z2(5, 10);
    Complex<int> result = z1 - z2;
    Complex<int> expected = Complex<int>(5, -5);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, binary_minus_double_test) {
    Complex<double> z1(2.5, 5.7);
    Complex<double> z2(2.2, 5.5);
    Complex<double> result = z1 - z2;
    Complex<double> expected(0.3, 0.2);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, multiply_int_test) {
    Complex<double> z1(2, 5);
    Complex<double> z2(5, 2);
    Complex<double> result = z1 * z2;
    Complex<double> expected(0, 29);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, multiply_double_test) {
    Complex<double> z1(2.5, 5.7);
    Complex<double> z2(2.2, 5.5);
    Complex<double> result = z1 * z2;
    Complex<double> expected(-25.85, 26.29);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, division_int_test) {
    Complex<double> z1(1, 1);
    Complex<double> z2(1, 2);
    Complex<double> result = z1 / z2;
    Complex<double> expected(0.6, -0.2);

    EXPECT_EQ(result == expected, 1);
}

TEST(complex_operators, division_double_test) {
    Complex<double> z1(2.0, 5.0);
    Complex<double> z2(1.0, 3.0);
    Complex<double> result = z1 / z2;
    Complex<double> expected(1.7, -0.1);

    EXPECT_EQ(result == expected, 1);
}