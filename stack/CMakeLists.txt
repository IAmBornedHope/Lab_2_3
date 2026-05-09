add_library(stack INTERFACE)
target_include_directories(stack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(stack INTERFACE sequence array_sequence exceptions)