//
// Created by Dell on 2021/6/9.
//

#ifndef CHAPTER11_BINARYTREENODE_H
#define CHAPTER11_BINARYTREENODE_H

#include "string"
#include "stack"
#include "queue"
#include "vector"
#include "queue"

//using namespace std;

template<class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;

    binaryTreeNode() {leftChild=rightChild=NULL;}
    explicit binaryTreeNode(const T& theElement) : element(theElement){
        leftChild=rightChild=NULL;
    }
    binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeft, binaryTreeNode<T>*theRight):element(theElement), leftChild(theLeft), rightChild(theRight) {}
};

#endif //CHAPTER11_BINARYTREENODE_H
