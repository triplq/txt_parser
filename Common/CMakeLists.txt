cmake_minimum_required(VERSION 3.10)
project(common)

set(CMAKE_CXX_STANDARD 20)

add_library(Common STATIC Person.cpp Person.h)

target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})