cmake_minimum_required(VERSION 3.17)
project(arrayStack)
set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(
        include
)

add_executable(arrayStack src/main.cpp include/arrayStack.h)