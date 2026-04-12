cmake_minimum_required(VERSION 3.15)
project(Lab_2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(lab_2 main.cpp)

add_subdirectory(dynamic_array)

target_link_libraries(lab_2 dynamic_array)