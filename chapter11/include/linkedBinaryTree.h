//
// Created by Dell on 2021/6/28.
//
#ifndef CHAPTER11_LINKEDBINARYTREE_H
#define CHAPTER11_LINKEDBINARYTREE_H

#include "binaryTree.h"
#include "binaryTreeNode.h"
#include "stack"

template<class T>
class linkedBinaryTree : public binaryTree<binaryTreeNode<T> > // 把节点作为元素的数据类型
{
public:
    linkedBinaryTree() {root=NULL, treeSize=0;}
    ~linkedBinaryTree() {erase();}; // 这里为什么多一个分号
    bool empty() const {return treeSize==0;}
    int size() const {return treeSize;}
    void preOrder(void (*theVisit)(binaryTreeNode<T>*)) {visit = theVisit, preOrder(root);}
    void inOrder(void(*theVisit)(binaryTreeNode<T>*)) {visit = theVisit, inOrder(root);}
    void postOrder(void(*theVisit)(binaryTreeNode<T>*)) {visit = theVisit, postOrder(root);}
    void erase()
    {
        postOrder(dispose); // 用此函数对visit函数进行赋值
        root = NULL;
        treeSize = 0;
    }
    static void output(binaryTreeNode<T>* t) {std::cout << t->element << " "; }
    void preOrderOutput() { preOrder(output), std::cout << std::endl;} // 传递函数指针,所以output不用指定参数，内部调用visit时会指定
    void inOrderOutput() { inOrder(output), std::cout << std::endl;}
    void postOrderOutput() { postOrder(output), std::cout << std::endl;}

    int height() const { return height(root); }
    int height(binaryTreeNode<T> *);

    linkedBinaryTree(const linkedBinaryTree<T> &); // 复制构造函数
    void initialize(binaryTreeNode<T> *); // 从一个已有根节点的二叉树结构的初始化此类对象
    bool compare(const linkedBinaryTree<T> &);
    void swapTrees();

    // 中序输出
    class forwardIterator{
    public:
        friend forwardIterator linkedBinaryTree<T>::begin();
        explicit forwardIterator(binaryTreeNode<T>* theNode = NULL) { node = theNode; }
        //解引用操作符
        T& operator*() const { return node->element; }
        T* operator->() const {return &node->element; }

        // 相等验证
        bool operator==(const forwardIterator& right) const { return node == right.node; }
        bool operator!=(const forwardIterator& right) const { return node != right.node; }

        // 单向递增
        forwardIterator& operator++() {node=nodeQueue.front();nodeQueue.pop();return *this;}
        forwardIterator operator++(int) {forwardIterator temp=node;node=nodeQueue.front();nodeQueue.pop();return temp;}
    private:
        binaryTreeNode<T>* node;
        std::queue<binaryTreeNode<T>*> nodeQueue;
    };

    forwardIterator begin() {
        forwardIterator temp;
        getForwardIteratorQueue(temp.nodeQueue, root);
        temp.nodeQueue.push(NULL); // 用于判断是否到尾
        temp.node = temp.nodeQueue.front();
        temp.nodeQueue.pop();
        return temp;
    }
    forwardIterator end() const {return forwardIterator();}

private:
    binaryTreeNode<T> *root;
    int treeSize;
    // 函数指针，用来访问节点元素,可以对这个函数指针进行赋值
    // 那么就会将赋值的指针的函数的功能传递过来，所以visit本质是一个指针变量
    // static函数是类的所用对象共有，只能修改static成员变量
    static void (*visit)(binaryTreeNode<T>*);
    void preOrder(binaryTreeNode<T> *);
    void inOrder(binaryTreeNode<T> *);
    void postOrder(binaryTreeNode<T> *);
    static void dispose(binaryTreeNode<T>* t) { delete t;}
    void copyConstructor(binaryTreeNode<T>* srcNode, binaryTreeNode<T>* &targetNode);
    bool compare(const binaryTreeNode<T>* firstNode, const binaryTreeNode<T>* secondNode);
    void swapTrees(binaryTreeNode<T>* &firstNode, binaryTreeNode<T>* &secondNode);
    void getForwardIteratorQueue(std::queue<binaryTreeNode<T>*> &myQueue, binaryTreeNode<T>* x);
};

// 这里很重要，由于visit是函数指针，本质是一个普通变量
// 而且又是一个static变量，所以需要在类外进行初始化
template<class T>
void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T>*) = nullptr;

template<class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T> *t) {
    if (t==NULL)
        return 0;
    int hl = height(t->leftChild);
    int hr = height(t->rightChild);
    if (hl > hr) // 还要加上本层的高度
        return ++hl;
    else
        return ++hr;
}

template<class T>
linkedBinaryTree<T>::linkedBinaryTree(const linkedBinaryTree<T> &srcTree) {
    copyConstructor(srcTree.root, this->root);
    this->treeSize = srcTree.treeSize;
}


template<class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T> *t) {
    if (t != NULL){
        visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T> *t) {
    if (t != NULL){
        inOrder(t->leftChild);
        visit(t);
        inOrder(t->rightChild);
    }
}

template<class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T> *t) {
    if (t != NULL){
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        visit(t);
    }
}

// 注意这里指针的引用
template<class T>
void linkedBinaryTree<T>::copyConstructor(binaryTreeNode<T>* srcNode, binaryTreeNode<T>* &targetNode) {
    if (srcNode != NULL){
        ++treeSize;
        targetNode = new binaryTreeNode<T>(srcNode->element);
        copyConstructor(srcNode->leftChild, targetNode->leftChild);
        copyConstructor(srcNode->rightChild, targetNode->rightChild);
    }
}

template<class T>
void linkedBinaryTree<T>::initialize(binaryTreeNode<T> *srcNode) {
    this->treeSize=0;
    copyConstructor(srcNode, root);
}

template<class T>
bool linkedBinaryTree<T>::compare(const linkedBinaryTree<T> &theTree) {
    if (size()!=theTree.size())
        return false;
    return compare(root, theTree.root);
}

template<class T>
bool linkedBinaryTree<T>::compare(const binaryTreeNode<T> *firstNode, const binaryTreeNode<T> *secondNode) {
    if (firstNode==NULL && secondNode==NULL)
        return true;
    if ((firstNode==NULL && secondNode!=NULL) || (firstNode!=NULL && secondNode==NULL))
        return false;
    // 全都有值
    if (firstNode->element != secondNode->element)
        return false;
    else // 在元素值相等的前提下
        return compare(firstNode->leftChild, secondNode->leftChild) && compare(firstNode->rightChild, secondNode->rightChild);
}

template<class T>
void linkedBinaryTree<T>::swapTrees() {
    swapTrees(root->leftChild, root->rightChild);
}

template<class T>
void linkedBinaryTree<T>::swapTrees(binaryTreeNode<T>* &firstNode, binaryTreeNode<T>* &secondNode) {
    if (firstNode!=NULL && secondNode!=NULL) {
        binaryTreeNode<T>* temp;
        temp = firstNode;
        firstNode = secondNode;
        secondNode = temp;
        swapTrees(firstNode->leftChild, firstNode->rightChild);
        swapTrees(secondNode->leftChild, secondNode->rightChild);
    }
}

template<class T>
void linkedBinaryTree<T>::getForwardIteratorQueue(std::queue<binaryTreeNode<T> *> &myQueue, binaryTreeNode<T> *x) {
    if(x!=NULL){
        getForwardIteratorQueue(myQueue, x->leftChild);
        myQueue.push(x);
        getForwardIteratorQueue(myQueue, x->rightChild);
    }
}


#endif //CHAPTER11_LINKEDBINARYTREE_H

