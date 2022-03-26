cmake_minimum_required(VERSION 3.19)
project(chapter9)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(
        include
)

add_executable(chapter9 main.cpp)