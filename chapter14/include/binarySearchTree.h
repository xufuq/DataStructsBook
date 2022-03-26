//
// Created by Dell on 2021/6/30.
//

#ifndef CHAPTER14_BINARYSEARCHTREE_H
#define CHAPTER14_BINARYSEARCHTREE_H

#include "bsTree.h"
#include "linkedBinaryTree.h"

// overload << for pair
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const std::pair<K, E>& x);



template<class K, class E>
//class binarySearchTree : public bsTree<K, E>, public linkedBinaryTree<binaryTreeNode<std::pair<const K, E>>>
class binarySearchTree : public bsTree<K, E>, public linkedBinaryTree<std::pair<const K, E> > // 注意这里的第二个继承，是用pair<const K, E>替换其对应文件中的T的位置即可
{
public:
    bool empty() const {return this->treeSize == 0;}
    int size() const {return this->treeSize;}
    std::pair<const K, E>* find(const K& theKey) const;
    void insert(const std::pair<const K, E>& thePair);
    void erase(const K& theKey);

    // linkedBinaryTree已经有具体的实现了，所以其中的函数是可以直接用的，可能输出函数需要改一下，即visit的赋值
    void ascend() { this->inOrderOutput(); }
    void outputInRange(const K& theLow, const K& theHigh);
    binaryTreeNode<std::pair<const K, E>> * split(const K& theKey, binarySearchTree<K, E>& lessThanTree, binarySearchTree<K, E>& greaterThanTree);

private:
    void outputInRange(binaryTreeNode<std::pair<const K, E>> *, const K&, const K&);
    binaryTreeNode<std::pair<const K, E>> * split(const K& theKey, binaryTreeNode<std::pair<const K, E>> *&currentNode, binarySearchTree<K, E>& lessThanTree, binarySearchTree<K, E>& greaterThanTree);
};

template<class K, class E>
std::pair<const K, E> *binarySearchTree<K, E>::find(const K& theKey) const {
    binaryTreeNode<std::pair<const K, E>> *p = this->root;
    while (p != NULL){
        if (p->element.first > theKey)
            p = p->leftChild;
        else if (p->element.first < theKey)
            p = p->rightChild;
        else // 相等
            return &p->element;
    }
    return nullptr;
}

template<class K, class E>
void binarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair){
    binaryTreeNode<std::pair<const K, E> > *p = this->root, *pp = NULL;
    while (p != NULL)
    {// examine p->element
        pp = p; // pp获得的可能是合适的位置，如果没有相同节点的话
        // move p to a child
        if (thePair.first < p->element.first)
            p = p->leftChild;
        else if (thePair.first > p->element.first)
            p = p->rightChild;
        else
        {// replace old value
            p->element.second = thePair.second;
            return;
        }
    }

    // 不存在相等的关键字
    // get a node for thePair and attach to pp
    auto *newNode = new binaryTreeNode<std::pair<const K, E> > (thePair);
    if (this->root != NULL) // the tree is not empty
        if (thePair.first < pp->element.first)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;
    else
        this->root = newNode; // insertion into empty tree
    this->treeSize++;
}

template<class K, class E>
void binarySearchTree<K, E>::erase(const K& theKey){
    binaryTreeNode<std::pair<const K, E> > *p = this->root, *pp = NULL;
    while (p != NULL && p->element.first != theKey)
    {// move to a child of p
        pp = p;
        if (theKey < p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    if (p == NULL) // 没有相应关键字
        return; // no pair with key theKey

    // restructure tree
    // handle case when p has two children
    if (p->leftChild != NULL && p->rightChild != NULL)
    {// two children
        // convert to zero or one child case
        // find largest element in left subtree of p
        binaryTreeNode<std::pair<const K, E> > *s = p->leftChild, *ps = p;  // parent of s
        while (s->rightChild != NULL) // 找到左子树的最大元素，所以一直求右子树及其对应的根节点
        {// move to larger element
            ps = s;
            s = s->rightChild;
        }

        // move largest from s to p, can't do a simple move
        // p->element = s->element as key is const
        // pp是删除节点p的父节点
        // ps是替补节点s的父节点，最初等于p
        auto *q = new binaryTreeNode<std::pair<const K, E> > (s->element, p->leftChild, p->rightChild);
        if (pp == NULL) // 删除的是根节点
            this->root = q;
        else if (p == pp->leftChild) // 删除的是左节点
            pp->leftChild = q;
        else // 右节点
            pp->rightChild = q;

        // 这里pp的值是为了下面的做准备
        // 求出的是替补的s的父节点
        // 然后p又代替了即将要被删掉的多余的s
        if (ps == p) pp = q; // 左子树没有右节点
        else pp = ps;
        delete p;
        p = s;
    }

    // p has at most one child
    // save child pointer in c
    // 删除被替换的s和删除本来要删除的p(只有一个子树的情况或没有子树)的过程是相同的
    binaryTreeNode<std::pair<const K, E> > *c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;

    // delete p
    if (p == this->root)
        this->root = c;
    else
    {// is p left or right child of pp?
        if (p == pp->leftChild)
            pp->leftChild = c;
        else pp->rightChild = c;
    }
    this->treeSize--;
    delete p;
}

template<class K, class E>
void binarySearchTree<K, E>::outputInRange(const K &theLow, const K &theHigh) {
    if (this->root!=NULL)
        outputInRange(this->root, theLow, theHigh);
}

template<class K, class E>
void binarySearchTree<K, E>::outputInRange(binaryTreeNode<std::pair<const K, E>> *currentNode, const K &theLow, const K &theHigh) {
    if (currentNode->leftChild!=NULL)
        outputInRange(currentNode->leftChild, theLow, theHigh);
    if (currentNode->element.first >= theLow && currentNode->element.first < theHigh) // 根节点的信息不能作为判断子节点是否在范围内的依据
        std::cout << currentNode->element << std::endl;
    if (currentNode->rightChild!=NULL)
        outputInRange(currentNode->rightChild, theLow, theHigh);
}

template<class K, class E>
binaryTreeNode<std::pair<const K, E>> * binarySearchTree<K, E>::split(const K &theKey, binarySearchTree<K, E> &lessThanTree,
                                                                       binarySearchTree<K, E> &greaterThanTree) {
    binaryTreeNode<std::pair<const K, E>> * result;
    if (this->root!=NULL)
        result = split(theKey, this->root, lessThanTree, greaterThanTree);
    this->treeSize=0;
    return result;
}

template<class K, class E>
binaryTreeNode<std::pair<const K, E>> * binarySearchTree<K, E>::split(const K &theKey, binaryTreeNode<std::pair<const K, E>> *&currentNode,
                                    binarySearchTree<K, E> &lessThanTree, binarySearchTree<K, E> &greaterThanTree) {
    if (currentNode!=NULL){
        binaryTreeNode<std::pair<const K, E>>* leftRe = split(theKey, currentNode->leftChild, lessThanTree, greaterThanTree);
        binaryTreeNode<std::pair<const K, E>>* rightRe = split(theKey, currentNode->rightChild, lessThanTree, greaterThanTree);
        if (currentNode->element.first < theKey)
            lessThanTree.insert(currentNode->element);
        else if (currentNode->element.first > theKey)
            greaterThanTree.insert(currentNode->element);
        else // 相等, 则不删除当前节点，因为没有重复元素。所以不用再往下执行
            return currentNode;

        // 删除当前节点,这里应该是从子节点依次开始删除的，不应该报错啊
        delete currentNode;
        currentNode = NULL;

        if (leftRe != NULL)
            return leftRe;
        else
            return rightRe;
    }
    return NULL;
}

template <class K, class E>
std::ostream& operator<<(std::ostream& out, const std::pair<K, E>& x)
{out << x.first << ' ' << x.second; return out;}

#endif //CHAPTER14_BINARYSEARCHTREE_H
