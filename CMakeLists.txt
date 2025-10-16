cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(MyTask)

configure_file(${CMAKE_SOURCE_DIR}/text.txt ${CMAKE_BINARY_DIR}/text.txt COPYONLY)

add_executable(MyTask main.cpp text.txt)