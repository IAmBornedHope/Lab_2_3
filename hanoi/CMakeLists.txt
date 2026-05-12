add_library(hanoi INTERFACE)
target_include_directories(hanoi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(hanoi INTERFACE stack array_sequence exceptions)