cmake_minimum_required(VERSION 3.15)
project(lab_2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/wxWidgets)

add_subdirectory(dynamic_array)
add_subdirectory(linked_list)
add_subdirectory(exceptions)
add_subdirectory(array_sequence)
add_subdirectory(sequence)
add_subdirectory(list_sequence)
add_subdirectory(bit_sequence)
add_subdirectory(stack)
add_subdirectory(square_matrix)
add_subdirectory(hanoi)
add_subdirectory(gui)
add_subdirectory(libs/gtest)
add_subdirectory(tests)

add_executable(lab_3 main.cpp resource.rc)

target_link_libraries(lab_3
                      exceptions
                      dynamic_array
                      linked_list
                      sequence
                      array_sequence
                      list_sequence
                      bit_sequence
                      stack 
                      square_matrix
                      hanoi
                      lab_gui)