#ifndef CHAIN_H
#define CHAIN_H

#include "linearList.h"
#include <algorithm>
#include <iostream>
#include <sstream>

template <class T>
struct chainNode
{
    // data member
    T element;
    chainNode<T>* next;

    // function
    chainNode() {}
    chainNode(const T& element) {this->element=element;}
    chainNode(const T& element, chainNode<T>* next) {this->element=element;this->next=next;}
};

template <class T>
class chain : public linearList<T>
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const chain<U>& theList);
public:
    chain(int initialCapacity = 10);
    chain(const chain<T>& theChain);
    ~chain();

    bool empty() const {return listSize == 0;} // 调用STL库的方法
    int size() const {return listSize;}  // STL
    T& get(int theIndex) const override;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream &out) const;
    // Q18
    void meld(chain<T>& leftChain, chain<T>& rightChain);
    // Q20
    void merge(chain<T>& leftChain, chain<T>& rightChain);
    // Q22
    void split(chain<T>& leftChain, chain<T>& rightChain);
    // Q26
    void insertSort();
    // Q27
    void bubbleSort();
    void selectSort();
    void countSort(){}

    class myIterator
    {
    public:
        // 构造函数
        myIterator(chainNode<T>* theNode = NULL) {node = theNode;}

        // 解引用操作符
        T& operator*() const {return node->element;}
        T* operator->() const {return &node->element;}

        // 单向列表，只能递加操作，无递减操作
        myIterator& operator++() {node = node->next; return *this;} // 先改变自身，然后返回一个指针
        myIterator operator++(int) {myIterator p=*this; node = node->next;return p;} // 这里关于指针类型的问题很重要

        // 相等检验
        bool operator==(const myIterator& right) const {return node == right.node;}
        bool operator!=(const myIterator& right) const {return node != right.node;}

    protected:
        chainNode<T>* node;
    };

    // 这里指针的值要进行显示转换，因为要支持迭代器的各种操作
    myIterator begin() const {return myIterator(firstNode);}
    myIterator end() const {return myIterator(NULL);}

protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* firstNode; // 指向链表第一个节点的指针
    int listSize; // 当前链表的长度
};

template <class T>
chain<T>::chain(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        // throw s.str();
    }
    firstNode = NULL;
    listSize = 0;
}

template <class T>
chain<T>::chain(const chain<T>& theList)
{
    listSize = theList.listSize;
    if(listSize == 0)
    {
        firstNode=NULL;
        return;
    }

    // if the theChain is not empty
    chainNode<T>* sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element); // 复制一个源链表的数据，并生成他的指针赋给头指针

    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode;
    while(sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;
}

template <class T>
chain<T>::~chain()
{
    while(firstNode != NULL)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }    
}

template <class T>
void chain<T>::checkIndex(int theIndex) const
{
    if(theIndex >= listSize)
        throw "theIndex is bigger than listSize!";
}

template <class T>
T& chain<T>::get(const int theIndex) const
{
    checkIndex(theIndex);

    // 根据索引向前移动
    chainNode<T>* currentNode = firstNode;
    for(int i=0;i<theIndex;i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template <class T>
int chain<T>::indexOf(const T& theElement) const
{
    chainNode<T>* currentNode = firstNode;
    int index=0; // the index of current nodes
    for(;currentNode != NULL; currentNode = currentNode->next)
    {
        if(theElement == currentNode->element) break;
        index++;
    }
    if(currentNode == NULL)
        return -1;
    return index;
}

template <class T>
void chain<T>::erase(const int theIndex)
{
    checkIndex(theIndex);
    chainNode<T>* deleteNode, *currentNode = firstNode;
    if(theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        for(int i=0;i<theIndex-1;i++)
            currentNode = currentNode->next;
        deleteNode = currentNode->next;
        // here the next is the core problem
        // currentNode is a point, so it can change its member "next" from the address
        currentNode->next = currentNode->next->next; 
    }
    listSize--;
    delete deleteNode;    
}

template <class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
    // 因为可以在尾后插入，且计数从0开始，所以要减一
    checkIndex(theIndex - 1);
    if(theIndex==0)
        firstNode = new chainNode<T>(theElement, firstNode);
    else
    {
        chainNode<T>* currentNode = firstNode;
        for(int i=0;i<theIndex-1;i++)
            currentNode = currentNode->next;
        // here the next is the core problem
        // currentNode is a point, so it can change its member "next" from the address
        currentNode->next = new chainNode<T>(theElement, currentNode->next);
    }
    listSize++;
}

template <class T>
void chain<T>::output(std::ostream& out) const
{
    for(chainNode<T>* currentNode=firstNode; currentNode != NULL; currentNode=currentNode->next)
        out << currentNode->element << " ";
    
}

template <class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& theList)
{
    theList.output(out);
    return out;
}

template <class T>
void chain<T>::meld(chain<T>& leftChain, chain<T>& rightChain)
{
    // 先释放原来的内存
    for(int i=0; i<listSize; i++)
        erase(0);
    chainNode<T>* currentNode = NULL, *leftNode = leftChain.firstNode, *rightNode = rightChain.firstNode;

    int shareSize = std::min(leftChain.size(), rightChain.size());
    // 下边这一段要好好揣摩，画图
    // 尝试有没有更好的实现方法
    for(int i=0; i<shareSize; i++)
    {
        if(i==0)
            currentNode=leftNode;
        else
        {
            currentNode->next=leftNode;
            currentNode=currentNode->next;
        }
        leftNode=leftNode->next;
        
        currentNode->next = rightNode;
        rightNode=rightNode->next;
        currentNode = currentNode->next;
    }
    if(leftChain.size() > rightChain.size())
        currentNode->next=leftNode;
    listSize = leftChain.size() + rightChain.size();
    firstNode = leftChain.firstNode;
    // 将输入链表设为空
    leftChain.firstNode=NULL;
    leftChain.listSize=0;
    rightChain.firstNode=NULL;
    rightChain.listSize=0;
}

template <class T>
void chain<T>::merge(chain<T>& leftChain, chain<T>& rightChain)
{
    // 先释放原来的内存
    for(int i=0; i<listSize; i++)
        erase(0);
    chainNode<T>* leftNode = leftChain.firstNode, *rightNode = rightChain.firstNode, *currentNode = NULL;
    // 首先确定第一个
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
    chainNode<T>* extraNode = (leftNode == NULL) ? rightNode : leftNode;
    currentNode->next=extraNode;
    listSize = leftChain.size() + rightChain.size();
    leftChain.listSize = 0, rightChain.listSize = 0;
    leftChain.firstNode = NULL, rightChain.firstNode = NULL;
}

template <class T>
void chain<T>::split(chain<T>& leftChain, chain<T>& rightChain)
{
    for(int i=0; i<leftChain.size(); i++)
        leftChain.erase(0);
    for(int i=0; i<rightChain.size(); i++)
        rightChain.erase(0);

    typename chain<T>::myIterator fromIter = begin(), endIter = end();
    while (fromIter != NULL)
    {
        leftChain.insert(leftChain.size(), *fromIter++);
        if(fromIter == NULL)   
            break;
        rightChain.insert(rightChain.size(), *fromIter++);
    }
}

// 链表排序
// 也可以不利用指针操作，而是直接对指针内的元素进行元素替换
template <class T>
void chain<T>::insertSort()
{
    // 第一个不用排序
    chainNode<T>* preNode = firstNode, *currentNode = firstNode->next, *nextNode = currentNode->next;
    for(int i=1; i<listSize; i++)
    {
        preNode->next = nextNode;
        
        int j=0; // 用j记录firstnode是否被替换
        chainNode<T>* searchLeftNode = NULL, * searchRightNode = firstNode;
        for(j=0; j<i && currentNode->element > searchRightNode->element;j++)
        {
            searchLeftNode = searchRightNode;
            searchRightNode = searchRightNode->next;
        }
        if(j == 0)
            firstNode = currentNode;
        else
            searchLeftNode->next = currentNode;
        currentNode->next = searchRightNode;
        if(j == i)
            preNode = currentNode; // 只有当currentNode放回原位时preNode才用迭代
        currentNode = nextNode;
        if(nextNode != NULL)
            nextNode = nextNode->next;
    }
}

// 冒泡排序
template <class T>
void chain<T>::bubbleSort()
{
    
    for(int j=listSize; j>1; j--)
    {
        chainNode<T>* currentNode = firstNode, *nextNode = firstNode->next;
        for(int i=0; i<j-1; i++)
        {
            if(currentNode->element > nextNode->element)
            {
                T tmp = currentNode->element;
                currentNode->element = nextNode->element;
                nextNode->element = tmp;
            }
            currentNode=nextNode;
            nextNode=nextNode->next;
        }
    }
}

template <class T>
void chain<T>::selectSort()
{
    // 找最大，方法类似
}



#endif