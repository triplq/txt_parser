cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(MyTask)

configure_file(${CMAKE_SOURCE_DIR}/student_file_1.txt ${CMAKE_BINARY_DIR}/student_file_1.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/student_file_2.txt ${CMAKE_BINARY_DIR}/student_file_2.txt COPYONLY)

add_executable(MyTask main.cpp Person.h Person.cpp)