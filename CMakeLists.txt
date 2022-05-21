cmake_minimum_required(VERSION 3.22)
project(custom_vector_class)

set(CMAKE_CXX_STANDARD 17)


include_directories(src)
add_subdirectory(src)
add_subdirectory(gtest)
add_subdirectory(lib/googletest)
