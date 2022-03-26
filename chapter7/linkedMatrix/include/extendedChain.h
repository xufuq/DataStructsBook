#ifndef EXTENDEDCHAIN_H
#define EXTENDEDCHAIN_H

#include "chain.h"


template <class T>
class extendedChain : public chain<T>  // 这里一定要加模板类型T
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const extendedChain<U>& theList);
public:                                                               // 这里访问基类成员一定要在前边加this指针
    extendedChain(int initialCapacity = 10):chain<T>(initialCapacity) {lastNode = this->firstNode;}
    extendedChain(const extendedChain<T>& theList) : chain<T>(theList)
    {
        chainNode<T>* currentNode = this->firstNode;
        lastNode = this->firstNode;
        while (currentNode != NULL)
        {
            lastNode=currentNode;
            currentNode = currentNode->next;
        }
    }

    void erase(int theIndex) override;
    void insert(int theIndex, const T& theElement) override;
    void clear();
    void push_back(const T& theElement);

    // Q2
    void setSize(int theSize);
    // Q3
    void set(int theIndex, const T& theElement);
    // Q4
    void removeRange(int fromIndex, int ToIndex);
    // Q5
    int lastIndexOf(const T& theElement);
    // Q6
    T& operator[](const int& theIndex);
    // Q7
    bool operator==(const extendedChain<T>& theRight) const;
    // Q8
    bool operator!=(const extendedChain<T>& theRight) const;
    // Q9
    bool operator<(const extendedChain<T>& theright);
    bool operator>(const extendedChain<T>& theright);
    void operator=(const extendedChain<T>& theright);
    // Q10
    void swap(extendedChain<T>& theright);
    // Q14
    void leftShift(const int& i);
    // Q15
    void reverse();
    // Q23
    void circularShift(const int shiftLength);

protected:
    chainNode<T>* lastNode;
};

template <class T>
void extendedChain<T>::erase(int theIndex)
{
    chain<T>::erase(theIndex);
    // erase之后listsize已经减一了，所以这里不用再减了
    if(theIndex == this->listSize)
    {
        chainNode<T>* currentNode = this->firstNode;
        while(currentNode != NULL)
        {
            lastNode=currentNode;
            currentNode = currentNode->next;
        }
    }
}

template <class T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{
    chain<T>::insert(theIndex, theElement);
    // 插入第一个值的时候firstNode的值被改变了，所以需要重新赋值
    if(this->listSize==1)  lastNode=this->firstNode;
    // 这里listsize又加了1
    // 这里的条件需要注意，很容易忽略第二个条件
    if((theIndex == this->listSize-1)&&(this->listSize-1>0))
        lastNode = lastNode->next;
}

template <class T>
void extendedChain<T>::clear()
{
    chainNode<T>* nextNode, *currentNode=this->firstNode;
    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    this->listSize=0; // 清空保存个数
    lastNode=this->firstNode;
}

template <class T>
void extendedChain<T>::push_back(const T& theElement)
{
    // 利用lastNode指针来加快速度

    if(this->listSize==0)
    {
        this->firstNode = new chainNode<T>(theElement, NULL);
        lastNode = this->firstNode;
    }
    else
    {
        lastNode->next=new chainNode<T>(theElement, NULL);
        lastNode = lastNode->next;
    }
    this->listSize++;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const extendedChain<T>& theList)
{
    theList.output(out);
    return out;
}

template <class T>
void extendedChain<T>::setSize(int theSize)
{
    if(theSize < this->listSize)
    {
        while(this->listSize>theSize)
            erase(this->listSize-1);        
    }
}

template <class T>
void extendedChain<T>::set(int theIndex, const T& theElement)
{
    chainNode<T>* currentNode = this->firstNode;
    for(int i=0;i<theIndex;i++)
        currentNode=currentNode->next;
    currentNode->element=theElement;
}

// 不删除索引为toIndex的元素
template <class T>
void extendedChain<T>::removeRange(int fromIndex, int toIndex)
{
    // 直接调用erase函数会使得程序时间复杂度过高
    this->checkIndex(fromIndex);
    // 因为不删除最后一个元素， 所以可以和listSize相等，但检查时要减一
    this->checkIndex(toIndex-1);
    bool ifLastChange = false;
    if(toIndex == this->listSize) ifLastChange=true;
    chainNode<T>* fromNode = this->firstNode, *currentNode=NULL, *deleteNode=this->firstNode;
    // 这里i=1是为了能够获得第一个被删除指针的前一个对象
    if(fromIndex != 0)
    {
        for(int i=1; i<fromIndex;i++)
            fromNode=fromNode->next;
        deleteNode=fromNode->next;
    }
    currentNode=deleteNode;
    for(int i=fromIndex;i<toIndex;i++)
    {
        currentNode=deleteNode->next;
        delete deleteNode;
        deleteNode = currentNode;
        this->listSize--;
    }
    if(fromIndex==0)
        this->firstNode=currentNode;
    else
        fromNode->next=currentNode; 
    // 看最后一个元素是否被删除
    if(ifLastChange==true)
        lastNode=fromNode;
}

template <class T>
int extendedChain<T>::lastIndexOf(const T& theElement)
{
    int i=0, index = -1;
    for(chainNode<T>* currentNode = this->firstNode; currentNode != NULL; currentNode=currentNode->next)
    {
        if(currentNode->element == theElement)
            index=i;
        i++;
    }
    return index;
}

template <class T>
T& extendedChain<T>::operator[](const int& theIndex)
{
    return this->get(theIndex);
}

template <class T>
bool extendedChain<T>::operator==(const extendedChain<T>& theRight) const
{
    bool value = false;
    if(this->listSize == theRight.listSize)
    {
        chainNode<T>* currentNodeR = theRight.firstNode;
        for(chainNode<T>* currentNodeL = this->firstNode; currentNodeL != NULL; currentNodeL=currentNodeL->next)
        {
            if(currentNodeL->element != currentNodeR->element)
                break;
            currentNodeR=currentNodeR->next;
        }
        if(currentNodeR == NULL)
            value=true;
    }
    return value;
}

template <class T>
bool extendedChain<T>::operator!=(const extendedChain<T>& theRight) const
{
    return !(*this == theRight);
}

template <class T>
bool extendedChain<T>::operator<(const extendedChain<T>& theRight)
{
    chainNode<T>* currentNodeL = this->firstNode, *currentNodeR = theRight.firstNode;
    int bothSize = std::min(this->listSize, theRight.listSize);
    for(int i=0; i<bothSize;i++)
    {
        if(currentNodeL->element < currentNodeR->element)
            return true;
        else if(currentNodeL->element > currentNodeR->element)
            return false;
    }
    // 如果共同长度的元素全部相等，比较长度
    if(this->listSize < theRight.listSize)
        return true;
    else
        return false;    
}

template <class T>
bool extendedChain<T>::operator>(const extendedChain<T>& theRight)
{
    chainNode<T>* currentNodeL = this->firstNode, *currentNodeR = theRight.firstNode;
    int bothSize = std::min(this->listSize, theRight.listSize);
    for(int i=0; i<bothSize;i++)
    {
        if(currentNodeL->element > currentNodeR->element)
            return true;
        else if(currentNodeL->element < currentNodeR->element)
            return false;
        currentNodeR=currentNodeR->next;
        currentNodeL=currentNodeL->next;
    }
    // 如果共同长度的元素全部相等，比较长度
    if(this->listSize > theRight.listSize)
        return true;
    else
        return false;    
}

template <class T>
void extendedChain<T>::operator=(const extendedChain<T>& theright)
{
    this->clear();


    this->listSize = theright.listSize;
    if(this->listSize == 0)
    {
        this->firstNode=NULL;
        return;
    }

    // if the theChain is not empty
    chainNode<T>* sourceNode = theright.firstNode;
    this->firstNode = new chainNode<T>(sourceNode->element); // 复制一个源链表的数据，并生成他的指针赋给头指针

    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = this->firstNode;
    while(sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;
    chainNode<T>* currentNode = this->firstNode;
    lastNode = this->firstNode;
    while (currentNode != NULL)
    {
        lastNode=currentNode;
        currentNode = currentNode->next;
    }
}

template <class T>
void extendedChain<T>::swap(extendedChain<T>& theright)
{
    int tmpSize = this->listSize;
    chainNode<T>* tmpFirst = this->firstNode, *tmpLast = this->lastNode;
    this->listSize=theright.listSize;
    this->lastNode=theright.lastNode;
    this->firstNode=theright.firstNode;
    theright.listSize=tmpSize;
    theright.firstNode=tmpFirst;
    theright.lastNode=tmpLast;
}

template <class T>
void extendedChain<T>::leftShift(const int& length)
{
    this->checkIndex(length-1);
    for(int i=0; i<length; i++)
        erase(0);
}

// 原地翻转，两个指针循环迭代
template <class T>
void extendedChain<T>::reverse()
{
    chainNode<T>* aNode = this->firstNode, *bNode = aNode->next, *cNode = NULL;
    aNode->next=NULL; // 首节点变为末节点，下一个为空
    while(bNode != NULL)
    {
        cNode=bNode->next;
        bNode->next=aNode;
        aNode=bNode;
        bNode=cNode;
    }
    lastNode = this->firstNode;
    this->firstNode=aNode;
}

// Q17
template <class T>
extendedChain<T> meld(const extendedChain<T>& leftChain, const extendedChain<T>& rightChain)
{
    extendedChain<T> tmp;
    typename chain<T>::myIterator leftIterator = leftChain.begin(), rightIterator = rightChain.begin();
    int shareSize = std::min(leftChain.size(), rightChain.size());
    for(int i=0; i<shareSize; i++)
    {
        tmp.push_back(*leftIterator++);
        tmp.push_back(*rightIterator++);
        // leftIterator++;
        // rightIterator++;
    }
    if(leftChain.size() < rightChain.size())
        while(rightIterator != NULL)
            tmp.push_back(*rightIterator++);
    else
        while(leftIterator != NULL)
            tmp.push_back(*leftIterator++);
    return tmp;
}

template <class T>
extendedChain<T> merge(const extendedChain<T>& leftChain, const extendedChain<T>& rightChain)
{
    extendedChain<T> tmp;
    typename extendedChain<T>::myIterator leftIter = leftChain.begin(), rightIter = rightChain.begin();
    while(leftIter!=NULL && rightIter!=NULL)
    {
        if(*leftIter<*rightIter)
            tmp.push_back(*leftIter++);
        else
            tmp.push_back(*rightIter++);

    }
    typename extendedChain<T>::myIterator extraIter = (leftIter==NULL) ? rightIter : leftIter;
    while(extraIter!=NULL)
        tmp.push_back(*extraIter++);
    return tmp;
}

// Q21
template <class T>
void split(extendedChain<T>& fromChain, extendedChain<T>& leftChain, extendedChain<T>& rightChain)
{
    leftChain.clear();
    rightChain.clear();
    typename chain<T>::myIterator fromIter = fromChain.begin(), endIter = fromChain.end();
    while (fromIter != NULL)
    {
        leftChain.push_back(*fromIter++);
        if(fromIter == NULL)   
            break;
        rightChain.push_back(*fromIter++);
    }
}

template <class T>
void extendedChain<T>::circularShift(const int shiftLength)
{
    for(int i=0;i<shiftLength;i++)
    {
        lastNode->next = this->firstNode;
        lastNode=lastNode->next;
        this->firstNode = this->firstNode->next;
        lastNode->next = NULL;
    }
}

#endif