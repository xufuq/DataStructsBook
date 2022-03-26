#ifndef CIRCULARLISTWITHHEADER
#define CIRCULARLISTWITHHEADER

#include "chain.h"
#include "linearList.h"
#include <iostream>
#include <algorithm>
#include <sstream>



template <class T>
class circularListWithHeader : public linearList<T>
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const circularListWithHeader<U>& x);
public:
    circularListWithHeader(int initialCapacity = 10);
    circularListWithHeader(const circularListWithHeader<T>& theChain);
    ~circularListWithHeader();


    bool empty() const {return listSize == 0;} // 调用STL库的方法
    int size() const {return listSize;}  // STL
    T& get(int theIndex) const override;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream &out) const;

    // Q39
    void reverse();
    // Q40
    void meld(circularListWithHeader<T>& leftChain, circularListWithHeader<T>& rightChain);
    // Q41
    void merge(circularListWithHeader<T>& leftChain, circularListWithHeader<T>& rightChain);

protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* headerNode; // 指向链表第一个节点的指针
    int listSize; // 当前链表的长度
};

template <class T>
circularListWithHeader<T>::circularListWithHeader(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
    }
    headerNode = new chainNode<T>();
    headerNode->next = headerNode;
    listSize = 0;
}

template <class T>
circularListWithHeader<T>::circularListWithHeader(const circularListWithHeader<T>& theChain)
{
    listSize = theChain.listSize;
    headerNode = new chainNode<T>();
    if(listSize == 0)
    {    
        headerNode->next = headerNode;
        return;
    }
    chainNode<T>* sourceNode = theChain.headerNode;
    chainNode<T>* targetNode = headerNode;
    while(sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = headerNode;
}

template <class T>
circularListWithHeader<T>::~circularListWithHeader()
{
    chainNode<T>* nextNode;
    while((listSize--)>=0)
    {
        nextNode = headerNode->next;
        delete headerNode;
        headerNode = nextNode;
    }
}

template <class T>
void circularListWithHeader<T>::checkIndex(int theIndex) const
{
    if(theIndex >= listSize)
        throw "theIndex is bigger than listSize!";
}

template <class T>
T& circularListWithHeader<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    chainNode<T>* currentNode = headerNode->next;
    for(int i=0; i<theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template <class T>
int circularListWithHeader<T>::indexOf(const T& theElement) const
{
    chainNode<T>* currentNode = headerNode->next;
    int theIndex = 0;
    while(currentNode->element != theElement && currentNode != headerNode)
    {
        currentNode = currentNode->next;
        theIndex++;
    }
    if(currentNode == headerNode)
        return -1;
    else
        return theIndex;
}

template <class T>
void circularListWithHeader<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    chainNode<T>* currentNode = headerNode->next, *preNode = headerNode;
    for(int i=0; i<theIndex; i++)
    {
        preNode = currentNode;
        currentNode = currentNode->next;
    }
    chainNode<T>* deleteNode = currentNode;
    preNode->next = currentNode->next;
    delete deleteNode;
    listSize--;
}

template <class T>
void circularListWithHeader<T>::insert(int theIndex, const T& theElement)
{
    checkIndex(theIndex-1);
    chainNode<T>* currentNode = headerNode->next, *preNode = headerNode;
    for(int i=0; i<theIndex; i++)
    {
        preNode = currentNode;
        currentNode = currentNode->next;
    }
    preNode->next = new chainNode<T>(theElement, currentNode);
    listSize++;
}

template <class T>
void circularListWithHeader<T>::output(std::ostream &out) const
{
    for(chainNode<T>* currentNode=headerNode->next; currentNode != headerNode; currentNode=currentNode->next)
        out << currentNode->element << " ";
}

template <class U>
std::ostream& operator<<(std::ostream& out, const circularListWithHeader<U>& theList)
{
    theList.output(out);
    return out;
}

template <class T>
void circularListWithHeader<T>::reverse()
{
    chainNode<T>* preNode = headerNode, *currentNode = headerNode->next, *nextNode = currentNode->next;
    // 因为还有头节点，所以需要加1
    for(int i=0;i<listSize+1;i++)
    {
        currentNode->next = preNode;
        preNode = currentNode;
        currentNode = nextNode;
        nextNode = currentNode->next;
    }
}

template <class T>
void circularListWithHeader<T>::meld(circularListWithHeader<T>& leftChain, circularListWithHeader<T>& rightChain)
{
    for(int i=0; i<listSize; i++)
        erase(0);
    chainNode<T>* currentNode = headerNode, *leftNode = leftChain.headerNode->next, *rightNode = rightChain.headerNode->next;

    int shareSize = std::min(leftChain.size(), rightChain.size());
    for(int i=0; i<shareSize; i++)
    {
        currentNode->next=leftNode;
        currentNode=currentNode->next;
        leftNode=leftNode->next;
        
        currentNode->next = rightNode;
        rightNode=rightNode->next;
        currentNode = currentNode->next;
    }
    if(leftChain.size() > rightChain.size())
    {
        while(leftNode != leftChain.headerNode)
        {
            currentNode->next = leftNode;
            leftNode = leftNode->next;
            currentNode = currentNode->next;
        }
    }
    else
    {
        while(rightNode != rightChain.headerNode)
        {
            currentNode->next = rightNode;
            rightNode = rightNode->next;
            currentNode = currentNode->next;
        }
    }
    currentNode->next = headerNode;
    listSize = leftChain.size() + rightChain.size();
    leftChain.headerNode->next=leftChain.headerNode;
    rightChain.headerNode->next=rightChain.headerNode;
    leftChain.listSize=0;
    rightChain.listSize=0;    
}

template <class T>
void circularListWithHeader<T>::merge(circularListWithHeader<T>& leftChain, circularListWithHeader<T>& rightChain)
{
    for(int i=0; i<listSize; i++)
        erase(0);
    chainNode<T>* currentNode = headerNode, *leftNode = leftChain.headerNode->next, *rightNode = rightChain.headerNode->next;
    while(leftNode != leftChain.headerNode && rightNode != rightChain.headerNode)
    {
        if(leftNode->element < rightNode->element)
        {
            currentNode->next = leftNode;
            currentNode = currentNode->next;
            leftNode = leftNode->next;
        }
        else
        {
            currentNode->next = rightNode;
            currentNode = currentNode->next;
            rightNode = rightNode->next;
        }
    }
    chainNode<T>* extraNode = (leftNode == leftChain.headerNode) ? rightNode : leftNode;
    chainNode<T>* theHeader = (leftNode == leftChain.headerNode) ? rightChain.headerNode : leftChain.headerNode;
    while(extraNode != theHeader)
    {
        currentNode->next = extraNode;
        currentNode = currentNode->next;
        extraNode = extraNode->next;
    }
    currentNode->next = headerNode;
    listSize = leftChain.size() + rightChain.size();
    leftChain.headerNode->next=leftChain.headerNode;
    rightChain.headerNode->next=rightChain.headerNode;
    leftChain.listSize=0;
    rightChain.listSize=0;
}

#endif