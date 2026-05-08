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

    EXPECT_EQ(result.get_re(), -3);
    EXPECT_EQ(result.get_im(), 3);
}

TEST(complex_operators, unary_minus_double_test) {
    Complex<double> z(1.0, -5.2);
    Complex<double> result = -z;

    EXPECT_EQ(result.get_re(), -1.0);
    EXPECT_EQ(result.get_im(), 5.2);
}

TEST(complex_operators, binary_minus_int_test) {
    Complex<int> z1(10, 5);
    Complex<int> z2(5, 10);
    Complex<int> result = z1 - z2;

    EXPECT_EQ(result.get_re(), 5);
    EXPECT_EQ(result.get_im(), -5);
}

// TEST(complex_operators, binary_minus_double_test) {
//     Complex<double> z1(2.2, 5.5);
//     Complex<double> z2(2.2, 5.5);
//     Complex<double> result = z1 - z2;

//     EXPECT_EQ(result.get_re(), -0.5);
//     EXPECT_EQ(result.get_im(), 0.1);
// }