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
add_subdirectory(gui)

add_subdirectory(libs/gtest)
add_subdirectory(tests)

add_executable(lab_2 main.cpp resource.rc)

target_link_libraries(lab_2 dynamic_array)
target_link_libraries(lab_2 linked_list)
target_link_libraries(lab_2 array_sequence)
target_link_libraries(lab_2 exceptions)
target_link_libraries(lab_2 sequence)
target_link_libraries(lab_2 list_sequence)
target_link_libraries(lab_2 lab_gui)
target_link_libraries(lab_2 bit_sequence)