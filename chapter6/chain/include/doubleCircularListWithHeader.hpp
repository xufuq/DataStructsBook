#ifndef DOUBLECIRCULARLISTWITHHEADER_HPP
#define DOUBLECIRCULARLISTWITHHEADER_HPP

#include "doubleLinkedList.hpp"
#include "linearList.h"
#include <iostream>
#include <algorithm>
#include <sstream>

template <class T>
class doubleCircularListWithHeader : public linearList<T>
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const doubleCircularListWithHeader<U>& x);
public:
    doubleCircularListWithHeader(int initialCapacity = 10);
    doubleCircularListWithHeader(const doubleCircularListWithHeader<T>& theChain);
    ~doubleCircularListWithHeader();

    bool empty() const {return listSize == 0;} // 调用STL库的方法
    int size() const {return listSize;}  // STL
    T& get(int theIndex) const override;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream &out) const;
    void clear();
    void push_back(const T& theElement);

    // Q39
    void reverse();
    // Q40
    void meld(doubleCircularListWithHeader<T>& leftChain, doubleCircularListWithHeader<T>& rightChain);
    // Q41
    void merge(doubleCircularListWithHeader<T>& leftChain, doubleCircularListWithHeader<T>& rightChain);
    // Q48
    void split(doubleCircularListWithHeader<T>& leftChain, doubleCircularListWithHeader<T>& rightChain);

    class myIterator
    {
        // 构造函数
        myIterator(doubleChainNode<T>* theNode = NULL) {node = theNode;}

        // 解引用操作符
        T& operator*() const {return node->element;}
        T* operator->() const {return &node->element;}

        // 单向列表，只能递加操作，无递减操作
        myIterator& operator++() {node = node->next; return *this;} // 先改变自身，然后返回一个指针
        myIterator operator++(int) {myIterator p=*this; node = node->next;return p;} // 这里关于指针类型的问题很重要
        myIterator& operator--() {node = node->previous; return *this;}
        myIterator operator--(int) {myIterator p=*this; node = node->previous;return p;}

        // 相等检验
        bool operator==(const myIterator& right) const {return node == right.node;}
        bool operator!=(const myIterator& right) const {return node != right.node;}

    protected:
        doubleChainNode<T>* node;
    };

    myIterator begin() const {return myIterator(headerNode->next);}
    myIterator end() const {return myIterator(headerNode);}

protected:
    void checkIndex(int theIndex) const;
    doubleChainNode<T>* headerNode; // 指向链表第一个节点的指针
    int listSize; // 当前链表的长度
};

template <class T>
doubleCircularListWithHeader<T>::doubleCircularListWithHeader(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
    }
    headerNode = new doubleChainNode<T>();
    headerNode->next = headerNode;
    headerNode->previous = headerNode;
    listSize = 0;
}

template <class T>
doubleCircularListWithHeader<T>::doubleCircularListWithHeader(const doubleCircularListWithHeader<T>& theChain)
{
    listSize = theChain.listSize;
    headerNode = new doubleChainNode<T>();
    headerNode->next = headerNode;
    headerNode->previous = headerNode;
    if(listSize == 0)
        return;

    doubleChainNode<T>* sourceNode = theChain.headerNode->next;
    doubleChainNode<T>* targetNode = headerNode;
    while(sourceNode != theChain.headerNode)
    {
        targetNode->next = new doubleChainNode<T>(sourceNode->element, targetNode, headerNode);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
        headerNode->previous = targetNode;
    }
}

template <class T>
doubleCircularListWithHeader<T>::~doubleCircularListWithHeader()
{
    doubleChainNode<T>* nextNode;
    while((listSize--)>=0)
    {
        nextNode = headerNode->next;
        delete headerNode;
        headerNode = nextNode;
    }
}

template <class T>
void doubleCircularListWithHeader<T>::checkIndex(int theIndex) const
{
    if(theIndex >= listSize)
        throw "theIndex is bigger than listSize!";
}

template <class T>
T& doubleCircularListWithHeader<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    if(theIndex < listSize/2)
    {
        doubleChainNode<T>* currentNode = headerNode->next;
        for(int i=0; i<theIndex; i++)
            currentNode = currentNode->next;
        return currentNode->element;
    }
    else
    {
        doubleChainNode<T>* currentNode = headerNode->previous;
        for(int i=0; i<listSize-1-theIndex; i++)
            currentNode = currentNode->previous;
        return currentNode->element;
    }
}

template <class T>
int doubleCircularListWithHeader<T>::indexOf(const T& theElement) const
{
    doubleChainNode<T>* currentNode = headerNode->next;
    int theIndex = 0;
    while(currentNode->element != theElement && theIndex < listSize)
    {
        currentNode = currentNode->next;
        theIndex++;
    }
    if(theIndex == listSize)
        return -1;
    else
        return theIndex;
}

template <class T>
void doubleCircularListWithHeader<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    doubleChainNode<T>* currentNode = headerNode->next, *deleteNode = NULL, * preNode = NULL;
    for(int i=0;i<theIndex;i++)
        currentNode = currentNode->next;
    deleteNode = currentNode;
    currentNode->previous->next = currentNode->next;
    currentNode->next->previous = currentNode->previous;
    delete deleteNode;
    listSize--;
}

template <class T>
void doubleCircularListWithHeader<T>::insert(int theIndex, const T& theElement)
{
    checkIndex(theIndex-1);

    doubleChainNode<T>* currentNode = headerNode;
    for(int i=0;i<theIndex;i++)
        currentNode = currentNode->next;
    doubleChainNode<T>* nextNode = currentNode->next;
    currentNode->next = new doubleChainNode<T>(theElement, currentNode, nextNode);
    nextNode->previous = currentNode->next;
    listSize++;
}

template <class T>
void doubleCircularListWithHeader<T>::push_back(const T& theElement)
{
    doubleChainNode<T>* preNode = headerNode->previous;
    headerNode->previous = new doubleChainNode<T>(theElement, preNode, headerNode);
    preNode->next = headerNode->previous;
    listSize++;
}

template <class T>
void doubleCircularListWithHeader<T>::clear()
{
    // headerNode的指针自动复原
    for(int i = 0; i< listSize; i++)
        erase(0);
    listSize = 0;
}

template <class T>
void doubleCircularListWithHeader<T>::output(std::ostream &out) const
{
    int i=0;
    for(doubleChainNode<T>* currentNode=headerNode->next; currentNode != headerNode; currentNode=currentNode->next)
        out << currentNode->element << " ";
}

template <class U>
std::ostream& operator<<(std::ostream& out, const doubleCircularListWithHeader<U>& theList)
{
    theList.output(out);
    return out;
}

template <class T>
void doubleCircularListWithHeader<T>::reverse()
{
    doubleChainNode<T>* currentNode = headerNode, * tmpNode;
    // 多了一个头节点要置换
    for(int i=0; i<listSize+1; i++)
    {
        tmpNode = currentNode->next;
        currentNode->next = currentNode->previous;
        currentNode->previous = tmpNode;
        currentNode = tmpNode;
    }
}

// 两个输入都必须至少有一个元素
template <class T>
void doubleCircularListWithHeader<T>::meld(doubleCircularListWithHeader<T>& leftChain, doubleCircularListWithHeader<T>& rightChain)
{
    clear();
    doubleChainNode<T>* currentNode = headerNode, *leftNode = leftChain.headerNode->next, *rightNode = rightChain.headerNode->next;
    doubleChainNode<T>* leftLastNode = leftChain.headerNode->previous, * rightLastNode = rightChain.headerNode->previous;
    int shareSize = std::min(leftChain.size(), rightChain.size());
    for(int i=0; i<shareSize; i++)
    {
        
        leftNode->previous = currentNode;
        currentNode->next = leftNode;
        leftNode = leftNode->next;
        currentNode = currentNode->next;
        currentNode->next = headerNode;
        headerNode->previous = currentNode;


        rightNode->previous = currentNode;
        currentNode->next = rightNode;
        rightNode = rightNode->next;
        currentNode = currentNode->next;
        currentNode->next = headerNode;
        headerNode->previous = currentNode;
    }

    if(leftChain.size() > rightChain.size())
    {
        leftNode->previous = currentNode;
        currentNode->next = leftNode;
        leftLastNode->next = headerNode;
        headerNode->previous = leftLastNode;
    }
    else if(leftChain.size() < rightChain.size())
    {
        rightNode->previous = currentNode;
        currentNode->next = rightNode;
        rightLastNode->next = headerNode;
        headerNode->previous = rightLastNode;
    }

    listSize = leftChain.size() + rightChain.size();
    leftChain.headerNode->next = leftChain.headerNode; leftChain.headerNode->previous = leftChain.headerNode; leftChain.listSize = 0; 
    rightChain.headerNode->next = rightChain.headerNode; rightChain.headerNode->previous = rightChain.headerNode; rightChain.listSize = 0;
}

template <class T>
void doubleCircularListWithHeader<T>::merge(doubleCircularListWithHeader<T>& leftChain, doubleCircularListWithHeader<T>& rightChain)
{
    clear();
    doubleChainNode<T>* currentNode = headerNode, *leftNode = leftChain.headerNode->next, *rightNode = rightChain.headerNode->next;
    doubleChainNode<T>* leftLastNode = leftChain.headerNode->previous, * rightLastNode = rightChain.headerNode->previous;
    while(leftNode != leftChain.headerNode && rightNode != rightChain.headerNode)
    {
        if(leftNode->element < rightNode->element)
        {
            leftNode->previous = currentNode;
            currentNode->next = leftNode;
            leftNode = leftNode->next;
            currentNode = currentNode->next;
            currentNode->next = headerNode;
            headerNode->previous = currentNode;
        }
        else
        {
            rightNode->previous = currentNode;
            currentNode->next = rightNode;
            currentNode = currentNode->next;
            rightNode = rightNode->next;
            currentNode->next = headerNode;
            headerNode->previous = currentNode;
        }
    }
    doubleChainNode<T>* extraNode = (leftNode == leftChain.headerNode) ? rightNode : leftNode;
    doubleChainNode<T>* extraLast = (leftNode == leftChain.headerNode) ? rightLastNode : leftLastNode;
    currentNode->next = extraNode;
    extraNode->previous = currentNode;
    headerNode->previous = extraLast;
    extraLast->next = headerNode;
    listSize = leftChain.size() + rightChain.size();
    leftChain.headerNode->next = leftChain.headerNode; leftChain.headerNode->previous = leftChain.headerNode; leftChain.listSize = 0; 
    rightChain.headerNode->next = rightChain.headerNode; rightChain.headerNode->previous = rightChain.headerNode; rightChain.listSize = 0;
}

template <class T>
void doubleCircularListWithHeader<T>::split(doubleCircularListWithHeader<T>& leftChain, doubleCircularListWithHeader<T>& rightChain)
{
    leftChain.clear();
    rightChain.clear();
    doubleChainNode<T>* currentNode = headerNode->next;
    while(currentNode != headerNode)
    {
        // 这里可以采用更简单的方法
        leftChain.push_back(currentNode->element);
        currentNode = currentNode->next;
        if(currentNode == headerNode)
            break;
        rightChain.push_back(currentNode->element);
        currentNode = currentNode->next;
    }    
}

#endif