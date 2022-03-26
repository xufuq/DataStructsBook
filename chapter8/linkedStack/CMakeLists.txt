cmake_minimum_required(VERSION 3.17)
project(linkedStack)

set(CMAKE_CXX_STANDARD 14)
INCLUDE_DIRECTORIES(
        include
)
add_executable(linkedStack src/main.cpp)