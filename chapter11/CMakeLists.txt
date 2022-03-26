cmake_minimum_required(VERSION 3.19)
project(chapter11)

set(CMAKE_CXX_STANDARD 14)

add_executable(chapter11 main.cpp include/binaryTreeNode.h include/binaryTree.h include/linkedBinaryTree.h)