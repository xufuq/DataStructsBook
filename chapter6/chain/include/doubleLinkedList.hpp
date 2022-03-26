#ifndef DOUBLELINKEDLIST_HPP
#define DOUBLELINKEDLIST_HPP

#include "linearList.h"
#include <iostream>
#include <algorithm>
#include <sstream>


template <class T>
struct doubleChainNode
{
    // data member
    T element;
    doubleChainNode<T>* next, * previous;

    // function
    doubleChainNode() {}
    doubleChainNode(const T& element) {this->element=element;}
    doubleChainNode(const T& element, doubleChainNode<T>* previous, doubleChainNode<T>* next) {this->element=element;this->previous = previous;this->next=next;}
};


template <class T>
class doubleLinkedList : public linearList<T>
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const doubleLinkedList<U>& x);
public:
    doubleLinkedList(int initialCapacity = 10);
    doubleLinkedList(const doubleLinkedList<T>& theChain);
    ~doubleLinkedList();


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
    void meld(doubleLinkedList<T>& leftChain, doubleLinkedList<T>& rightChain);
    // Q41
    void merge(doubleLinkedList<T>& leftChain, doubleLinkedList<T>& rightChain);
    // Q45
    void appendChain(doubleLinkedList<T>& rightChain);
    // Q48
    void split(doubleLinkedList<T>& leftChain, doubleLinkedList<T>& rightChain);

protected:
    void checkIndex(int theIndex) const;
    doubleChainNode<T>* firstNode, * lastNode; // 指向链表第一个节点的指针
    int listSize; // 当前链表的长度
};

template <class T>
doubleLinkedList<T>::doubleLinkedList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
    }
    firstNode = NULL;
    lastNode = NULL;
    listSize = 0;
}

template <class T>
doubleLinkedList<T>::doubleLinkedList(const doubleLinkedList<T>& theChain)
{
    listSize = theChain.listSize;
    if(listSize == 0)
    {
        firstNode = NULL;
        lastNode = NULL;
        return;
    }
    doubleChainNode<T>* sourceNode = theChain.firstNode;
    firstNode = new doubleChainNode<T>(sourceNode->element, NULL, NULL);
    lastNode = firstNode;
    doubleChainNode<T>* targetNode = firstNode, * preNode = NULL;
    sourceNode = sourceNode->next;
    while(sourceNode != NULL)
    {
        targetNode->previous = preNode;
        targetNode->next = new doubleChainNode<T>(sourceNode->element);
        preNode = targetNode;
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->previous = preNode;
    targetNode->next = NULL;
    lastNode = targetNode;
}

template <class T>
doubleLinkedList<T>::~doubleLinkedList()
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
void doubleLinkedList<T>::checkIndex(int theIndex) const
{
    if(theIndex >= listSize)
        throw "theIndex is bigger than listSize!";
}

template <class T>
T& doubleLinkedList<T>::get(int theIndex) const
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
        doubleChainNode<T>* currentNode = lastNode;
        for(int i=0; i<listSize-1-theIndex; i++)
            currentNode = currentNode->previous;
        return currentNode->element;
    }
}

template <class T>
int doubleLinkedList<T>::indexOf(const T& theElement) const
{
    doubleChainNode<T>* currentNode = firstNode;
    int theIndex = 0;
    while(currentNode->element != theElement && currentNode != NULL)
    {
        currentNode = currentNode->next;
        theIndex++;
    }
    if(currentNode == NULL)
        return -1;
    else
        return theIndex;
}

template <class T>
void doubleLinkedList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    doubleChainNode<T>* currentNode = firstNode, *deleteNode = NULL, * preNode = NULL;
    if(listSize == 1)
    {
        deleteNode = firstNode;
        firstNode=NULL;
        lastNode=NULL;
    }
    else if(theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
        firstNode->previous = NULL; // firsrNode的位置已经变过了
    }
    else
    {
        for(int i=0;i<theIndex;i++)
        {
            preNode = currentNode;
            currentNode = currentNode->next;
        }
        deleteNode = currentNode;
        if(theIndex == listSize-1)
        {
            preNode->next=NULL;
            lastNode=preNode;
        }
        else
        {
            currentNode->next->previous = preNode;
            preNode->next = currentNode->next;
        }
    }
    delete deleteNode;
    listSize--;
}

template <class T>
void doubleLinkedList<T>::insert(int theIndex, const T& theElement)
{
    checkIndex(theIndex-1);
    doubleChainNode<T>* currentNode = firstNode, * preNode = NULL;
    if(listSize == 0)
    {
        firstNode = new doubleChainNode<T>(theElement, NULL, NULL);
        lastNode = firstNode;
    }
    else if(theIndex == 0)
    {
        firstNode = new doubleChainNode<T>(theElement, NULL, firstNode);
        firstNode->next->previous = firstNode;
    }
    else if(theIndex == listSize)
    {
        lastNode->next = new doubleChainNode<T>(theElement, lastNode, NULL);
        lastNode = lastNode->next;
    }
    else
    {
        for(int i=0;i<theIndex;i++)
        {
            preNode = currentNode;
            currentNode = currentNode->next;
        }
        preNode->next = new doubleChainNode<T>(theElement, preNode, currentNode);
        currentNode->previous = preNode->next;
    }
    listSize++;
}

template <class T>
void doubleLinkedList<T>::clear()
{
    for(int i = 0; i< listSize; i++)
        erase(0);
    firstNode = NULL;
    lastNode = NULL;
    listSize = 0;
}

template <class T>
void doubleLinkedList<T>::output(std::ostream &out) const
{
    for(doubleChainNode<T>* currentNode=firstNode; currentNode != NULL; currentNode=currentNode->next)
        out << currentNode->element << " ";
}

template <class U>
std::ostream& operator<<(std::ostream& out, const doubleLinkedList<U>& theList)
{
    theList.output(out);
    return out;
}

template <class T>
void doubleLinkedList<T>::appendChain(doubleLinkedList<T>& rightChain)
{
    lastNode->next = rightChain.firstNode;
    rightChain.firstNode->previous = lastNode;
    lastNode = rightChain.lastNode;
    listSize += rightChain.listSize;
    rightChain.lastNode = NULL;
    rightChain.firstNode = NULL;
    rightChain.listSize = 0;
}

template <class T>
void doubleLinkedList<T>::reverse()
{
    doubleChainNode<T>* currentNode = firstNode, * tmpNode;
    while(currentNode!=NULL)
    {
        tmpNode = currentNode->next;
        currentNode->next = currentNode->previous;
        currentNode->previous = tmpNode;
        currentNode = tmpNode;
    }
    tmpNode = firstNode;
    firstNode = lastNode;
    lastNode = tmpNode;
}

template <class T>
void doubleLinkedList<T>::meld(doubleLinkedList<T>& leftChain, doubleLinkedList<T>& rightChain)
{
    clear();
    doubleChainNode<T>* currentNode = NULL, *leftNode = leftChain.firstNode, *rightNode = rightChain.firstNode;
    int shareSize = std::min(leftChain.size(), rightChain.size());
    for(int i=0; i<shareSize; i++)
    {
        if(i==0)
            currentNode = leftNode;
        else
        {
            leftNode->previous = currentNode;
            currentNode->next = leftNode;
            currentNode = currentNode->next;
        }
        leftNode = leftNode->next;

        rightNode->previous = currentNode;
        currentNode->next = rightNode;
        currentNode = currentNode->next;
        rightNode = rightNode->next;
    }
    if(leftChain.size() > rightChain.size())
    {
        leftNode->previous = currentNode;
        currentNode->next = leftNode;
        lastNode = leftChain.lastNode;
    }
    else
        // 因为上边的for循环最后就是链接到rightchain的
        // 所以省略了一些步骤
        lastNode = rightChain.lastNode;
    if(leftChain.size() != 0)
        firstNode = leftChain.firstNode;
    else
        firstNode = rightChain.firstNode;

    listSize = leftChain.size() + rightChain.size();
    rightChain.lastNode = NULL; rightChain.firstNode = NULL; rightChain.listSize = 0;
    leftChain.lastNode = NULL;  leftChain.firstNode = NULL; leftChain.listSize = 0;    
}

template <class T>
void doubleLinkedList<T>::merge(doubleLinkedList<T>& leftChain, doubleLinkedList<T>& rightChain)
{
    clear();
    doubleChainNode<T>* leftNode = leftChain.firstNode, *rightNode = rightChain.firstNode, *currentNode = NULL;
    if(leftNode->element < rightNode->element)
    {
        currentNode = leftNode;
        leftNode = leftNode->next;
    }
    else
    {
        currentNode = rightNode;
        rightNode = rightNode->next;
    }
    firstNode = currentNode; // 更新当前对象的头指针
    while(leftNode != NULL && rightNode != NULL)
    {
        if(leftNode->element < rightNode->element)
        {
            currentNode->next = leftNode;
            leftNode->previous = currentNode;
            currentNode = currentNode->next;
            leftNode = leftNode->next;
        }
        else
        {
            currentNode->next = rightNode;
            rightNode->previous = currentNode;
            currentNode = currentNode->next;
            rightNode = rightNode->next;
        }
    }
    doubleChainNode<T>* extraNode = (leftNode == NULL) ? rightNode : leftNode;
    currentNode->next = extraNode;
    extraNode->previous = currentNode;
    lastNode = (leftNode == NULL) ? rightChain.lastNode : leftChain.lastNode;
    listSize = leftChain.size() + rightChain.size();
    rightChain.lastNode = NULL; rightChain.firstNode = NULL; rightChain.listSize = 0;
    leftChain.lastNode = NULL;  leftChain.firstNode = NULL; leftChain.listSize = 0; 
}

template <class T>
void doubleLinkedList<T>::split(doubleLinkedList<T>& leftChain, doubleLinkedList<T>& rightChain)
{
    leftChain.clear();
    rightChain.clear();
    doubleChainNode<T>* currentNode = firstNode;
    while (currentNode != NULL)
    {
        leftChain.insert(leftChain.size(), currentNode->element);
        currentNode = currentNode->next;
        if(currentNode == NULL)
            break;
        rightChain.insert(rightChain.size(), currentNode->element);
        currentNode = currentNode->next;
    }    
}

#endif