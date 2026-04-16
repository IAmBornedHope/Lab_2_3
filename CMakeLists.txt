cmake_minimum_required(VERSION 3.15)
project(lab_2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(lab_2 main.cpp)

add_subdirectory(dynamic_array)
add_subdirectory(linked_list)
add_subdirectory(exceptions)

add_subdirectory(googletest-1.17.0)
add_subdirectory(tests)

target_link_libraries(lab_2 dynamic_array)
target_link_libraries(lab_2 linked_list)

