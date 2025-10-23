cmake_minimum_required(VERSION 3.10)
project(client)

set(CMAKE_CXX_STANDARD 20)

find_package(cppzmq)

add_executable(client main.cpp)

target_link_libraries(client cppzmq Common)