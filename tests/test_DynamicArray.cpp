#include <gtest/gtest.h>
#include "../dynamic_array/DynamicArray.hpp"

TEST(dynamic_array_test, constructor_test) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.get_size(), 0);
}
