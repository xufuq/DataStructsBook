#ifndef DOUBLECIRCULARLIST_HPP
#define DOUBLECIRCULARLIST_HPP

#include "doubleLinkedList.hpp"
#include "linearList.h"
#include <iostream>
#include <algorithm>
#include <sstream>

template <class T>
class doubleCircularList : public linearList<T>
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const doubleLinkedList<U>& x);
public:
    doubleCircularList(int initialCapacity = 10);
    doubleCircularList(const doubleCircularList<T>& theChain);
    ~doubleCircularList();

    bool empty() const {return listSize == 0;} // 调用STL库的方法
    int size() const {return listSize;}  // STL
    T& get(int theIndex) const override;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream &out) const;
    void clear();

    // Q39
    void reverse();
    // Q40
    void meld(doubleCircularList<T>& leftChain, doubleCircularList<T>& rightChain);
    // Q41
    void merge(doubleCircularList<T>& leftChain, doubleCircularList<T>& rightChain);
    // Q48
    void split(doubleCircularList<T>& leftChain, doubleCircularList<T>& rightChain);

protected:
    void checkIndex(int theIndex) const;
    doubleChainNode<T>* firstNode; // 指向链表第一个节点的指针
    int listSize; // 当前链表的长度
};

template <class T>
doubleCircularList<T>::doubleCircularList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
    }
    firstNode = NULL;
    listSize = 0;
}

template <class T>
doubleCircularList<T>::doubleCircularList(const doubleCircularList<T>& theChain)
{
    listSize = theChain.listSize;
    if(listSize == 0)
    {
        firstNode = NULL;
        return;
    }
    doubleChainNode<T>* sourceNode = theChain.firstNode;
    firstNode = new doubleChainNode<T>(sourceNode->element, NULL, NULL);
    firstNode->next = firstNode;
    firstNode->previous = firstNode;
    doubleChainNode<T>* targetNode = firstNode;
    sourceNode = sourceNode->next;
    while(sourceNode != theChain.firstNode)
    {
        targetNode->next = new doubleChainNode<T>(sourceNode->element, targetNode, firstNode);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
        firstNode->previous = targetNode;
    }
}

template <class T>
doubleCircularList<T>::~doubleCircularList()
{
    doubleChainNode<T>* nextNode;
    while((listSize--)>0)
    {
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
void doubleCircularList<T>::checkIndex(int theIndex) const
{
    if(theIndex >= listSize)
        throw "theIndex is bigger than listSize!";
}

template <class T>
T& doubleCircularList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    if(theIndex < listSize/2)
    {
        doubleChainNode<T>* currentNode = firstNode;
        for(int i=0; i<theIndex; i++)
            currentNode = currentNode->next;
        return currentNode->element;
    }
    else
    {
        doubleChainNode<T>* currentNode = firstNode->previous;
        for(int i=0; i<listSize-1-theIndex; i++)
            currentNode = currentNode->previous;
        return currentNode->element;
    }
}

template <class T>
int doubleCircularList<T>::indexOf(const T& theElement) const
{
    doubleChainNode<T>* currentNode = firstNode;
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
void doubleCircularList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    doubleChainNode<T>* currentNode = firstNode, *deleteNode = NULL, * preNode = NULL;
    // if(listSize == 1)
    // {
    //     deleteNode = firstNode;
    //     firstNode=NULL;
    // }
    if(theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode->next->previous = firstNode->previous;
        firstNode->previous->next = firstNode->next;
        firstNode = firstNode->next;
    }
    else
    {
        for(int i=0;i<theIndex;i++)
            currentNode = currentNode->next;
        deleteNode = currentNode;
        currentNode->previous->next = currentNode->next;
        currentNode->next->previous = currentNode->previous;
    }
    delete deleteNode;
    listSize--;   
}

template <class T>
void doubleCircularList<T>::insert(int theIndex, const T& theElement)
{
    checkIndex(theIndex-1);
    if(listSize == 0)
    {
        firstNode = new doubleChainNode<T>(theElement, NULL, NULL);
        firstNode->next = firstNode; 
        firstNode->previous = firstNode;
    }
    else if(theIndex == 0)
    {
        firstNode = new doubleChainNode<T>(theElement, firstNode->previous, firstNode);
        firstNode->next->previous = firstNode;
        firstNode->previous->next = firstNode;
    }
    else
    {
        doubleChainNode<T>* currentNode = firstNode;
        for(int i=0;i<theIndex;i++)
            currentNode = currentNode->next;
        currentNode->previous->next = new doubleChainNode<T>(theElement, currentNode->previous, currentNode);
        currentNode->previous = currentNode->previous->next;        
    }
    listSize++;    
}

template <class T>
void doubleCircularList<T>::clear()
{
    for(int i = 0; i< listSize; i++)
        erase(0);
    firstNode = NULL;
    listSize = 0;
}

template <class T>
void doubleCircularList<T>::output(std::ostream &out) const
{
    int i=0;
    for(doubleChainNode<T>* currentNode=firstNode; i<listSize; currentNode=currentNode->next, i++)
        out << currentNode->element << " ";
}

template <class U>
std::ostream& operator<<(std::ostream& out, const doubleCircularList<U>& theList)
{
    theList.output(out);
    return out;
}

template <class T>
void doubleCircularList<T>::reverse()
{
    doubleChainNode<T>* currentNode = firstNode, * tmpNode;
    for(int i=0; i<listSize; i++)
    {
        tmpNode = currentNode->next;
        currentNode->next = currentNode->previous;
        currentNode->previous = tmpNode;
        currentNode = tmpNode;
    }
}

// 两个输入都必须至少有一个元素
template <class T>
void doubleCircularList<T>::meld(doubleCircularList<T>& leftChain, doubleCircularList<T>& rightChain)
{
    clear();
    doubleChainNode<T>* currentNode = NULL, *leftNode = leftChain.firstNode, *rightNode = rightChain.firstNode;
    doubleChainNode<T>* leftLastNode = leftNode->previous, * rightLastNode = rightNode->previous;
    int shareSize = std::min(leftChain.size(), rightChain.size());
    for(int i=0; i<shareSize; i++)
    {
        if(i==0)
        {
            currentNode = leftNode;
            leftNode = leftNode->next;
            firstNode = currentNode;
            currentNode->previous = currentNode;
            currentNode->next = currentNode;
        }
        else
        {
            leftNode->previous = currentNode;
            currentNode->next = leftNode;
            leftNode = leftNode->next;
            currentNode = currentNode->next;
            currentNode->next = firstNode;
            firstNode->previous = currentNode;
        }

        rightNode->previous = currentNode;
        currentNode->next = rightNode;
        currentNode = currentNode->next;
        rightNode = rightNode->next;
        currentNode->next = firstNode;
        firstNode->previous = currentNode;
    }

    if(leftChain.size() > rightChain.size())
    {
        leftNode->previous = currentNode;
        currentNode->next = leftNode;
        leftLastNode->next = firstNode;
        firstNode->previous = leftLastNode;
    }
    else
    {
        // 因为上边的for循环最后就是链接到rightchain的
        // 所以省略了一些步骤
        rightLastNode->next = firstNode;
        firstNode->previous = rightLastNode;
    }

    listSize = leftChain.size() + rightChain.size();
    leftChain.firstNode = NULL; leftChain.listSize = 0; 
    rightChain.firstNode = NULL; rightChain.listSize = 0;
}

template <class T>
void doubleCircularList<T>::merge(doubleCircularList<T>& leftChain, doubleCircularList<T>& rightChain)
{
    clear();
    doubleChainNode<T>* currentNode = NULL, *leftNode = leftChain.firstNode, *rightNode = rightChain.firstNode;
    doubleChainNode<T>* leftLastNode = leftNode->previous, * rightLastNode = rightNode->previous;
    int leftCount = leftChain.size(), rightCount = rightChain.size();
    if(leftNode->element < rightNode->element)
    {
        currentNode = leftNode;
        leftNode = leftNode->next;
        leftCount--;
    }
    else
    {
        currentNode = rightNode;
        rightNode = rightNode->next;
        rightCount--;
    }
    firstNode = currentNode; // 更新当前对象的头指针
    firstNode->next = firstNode;
    firstNode->previous = firstNode;
    while(leftCount != 0 && rightCount != 0)
    {
        if(leftNode->element < rightNode->element)
        {
            leftNode->previous = currentNode;
            currentNode->next = leftNode;
            leftNode = leftNode->next;
            currentNode = currentNode->next;
            currentNode->next = firstNode;
            firstNode->previous = currentNode;
            leftCount--;
        }
        else
        {
            rightNode->previous = currentNode;
            currentNode->next = rightNode;
            currentNode = currentNode->next;
            rightNode = rightNode->next;
            currentNode->next = firstNode;
            firstNode->previous = currentNode;
            rightCount--;
        }
    }
    doubleChainNode<T>* extraNode = (leftCount == 0) ? rightNode : leftNode;
    doubleChainNode<T>* extraLast = (leftCount == 0) ? rightLastNode : leftLastNode;
    currentNode->next = extraNode;
    extraNode->previous = currentNode;
    firstNode->previous = extraLast;
    extraLast->next = firstNode;
    listSize = leftChain.size() + rightChain.size();
    rightChain.firstNode = NULL; rightChain.listSize = 0;
    leftChain.firstNode = NULL; leftChain.listSize = 0; 
}

template <class T>
void doubleCircularList<T>::split(doubleCircularList<T>& leftChain, doubleCircularList<T>& rightChain)
{
    leftChain.clear();
    rightChain.clear();
    doubleChainNode<T>* currentNode = firstNode;
    for(int i=0; i<listSize;)
    {
        leftChain.insert(leftChain.size(), currentNode->element);
        currentNode = currentNode->next;
        i++;
        if(i == listSize)
            break;
        rightChain.insert(rightChain.size(), currentNode->element);
        currentNode = currentNode->next;
        i++;
    }    
}

#endif