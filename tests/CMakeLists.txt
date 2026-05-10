cmake_minimum_required(VERSION 3.15)
project(lab_test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)


add_executable(lab_test main.cpp test_DynamicArray.cpp test_LinkedList.cpp test_BitSequence.cpp
                test_ArraySequence.cpp test_ListSequence.cpp test_Complex.cpp test_Stack.cpp)
target_link_libraries(lab_test gtest_main dynamic_array linked_list bit_sequence array_sequence list_sequence stack)

target_include_directories(lab_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
