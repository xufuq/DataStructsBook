//
// Created by Dell on 2021/6/28.
//

#ifndef CHAPTER11_BINARYTREE_H
#define CHAPTER11_BINARYTREE_H

template<class T>
class binaryTree
{
public:
    virtual ~binaryTree() = default;;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*)(T *)) = 0; // 以函数指针作为入口参数
    virtual void inOrder(void (*)(T *)) = 0;
    virtual void postOrder(void (*)(T *)) = 0;
//    virtual void levelOrder(void (*)(T *)) const = 0;
};


#endif //CHAPTER11_BINARYTREE_H
