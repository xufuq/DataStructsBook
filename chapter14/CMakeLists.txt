cmake_minimum_required(VERSION 3.19)
project(chapter14)

set(CMAKE_CXX_STANDARD 14)

add_executable(chapter14 main.cpp include/bsTree.h include/dictionary.h include/indexedBSTree.h include/binaryTreeNode.h include/binaryTree.h include/linkedBinaryTree.h include/binarySearchTree.h)