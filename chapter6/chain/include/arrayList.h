#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "linearList.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <utility>


// linearList<T> 要指出其是模板类

template <class T>
class arrayList : public linearList<T>
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const arrayList<U>& x);
    template <class U>
    friend bool operator==(arrayList<U>& left, arrayList<U>& right);
    template <class U>
    friend bool operator!=(arrayList<U>& left, arrayList<U>& right){return !(left == right);}
public:
    // arrayList(int initialCapacity = 10); // 构造函数
    // Q4
    arrayList(int initialCapacity = 10, int increaseStep = 0);
    arrayList(const arrayList<T> &);
    ~arrayList() {delete [] element;} // 释放元素数组指针所指向的内存

    // 实现虚函数
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int theIndex) const override;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream &out) const;
    // 获取数组总容量
    int capacity() const {return arrayLength;}
    // Q5
    void trimToSize();

    // Q6
    void setSize(int newSize);

    // Q7
    T& operator[](int x){return this->element[x];}
    bool operator<(const arrayList<T>& right);
    void operator=(const arrayList<T>& right);
    // Q11
    void push_back(const T& theElement);
    void pop_back();
    // Q13
    void swap(arrayList<T>& theList);
    // Q15
    T set(int theIndex, const T& theElement);
    // Q16
    void clear();
    // Q17
    void removeRange(const int& startIndex, const int& endIndex);
    // Q18
    int lastIndex(const T& theElement);
    // Q22
    void reverse(const int& startIndex, const int& endIndex);
    // Q23
    void leftShift(const int& i);
    // Q24
    void LeftMove(const int& i);
    // Q25
    void half();
    // Q28
    void meld(arrayList<T>& a, arrayList<T>& b);

    // 这种是内置迭代器类
    // 还有一种把迭代器当做友元类
    class myIterator
    {
    public:
        myIterator(T* thePosition){position = thePosition;}

        // 解引用操作符
        T& operator*() const {return *position;}
        T* operator->() const {return &*position;}

        // 迭代器的值增加
        myIterator& operator++(){++position;return position;}
        myIterator& operator++(int)
        {
            myIterator old=*this;
            position++;
            return old;
        }
        // 递减计算
        myIterator& operator--(){--position;return position;}
        myIterator& operator--(int){
            myIterator old = *this;
            --position;
            return old;
        }
        // +运算,不能使用引用返回的形式，因为结果是临时变量
        myIterator operator+(const int& i){return position+i;}
        // -运算
        myIterator operator-(const int& i){return position-i;}

        // 测试是否相等
        bool operator!=(const myIterator Right) const{return position != Right.position;}
        bool operator==(const myIterator Right) const{return position == Right.position;}

    protected:
        T* position;
    };

    myIterator begin(){return myIterator(element);} // 指向首元素
    myIterator end() {return myIterator(element+listSize);} // 尾后迭代器

protected:
    // 检查索引是否有效，无效则抛出异常
    void checkIndex(int theIndex) const;
    T* element;
    int arrayLength;   // 数组荣烺
    int listSize;    // 实际存储的数据的数量
    int IncreaseStep = 0;
    int InitialArrayLength;
};



// 构造函数
// template<class T>
// arrayList<T>::arrayList(int initialCapacity)
// {
//     if(initialCapacity < 1)
//     {
//         std::ostringstream s;
//         s << "Initial capacity = " << initialCapacity << " Must be > 0";
//         // throw s.str();
//     }

//     arrayLength = initialCapacity;
//     element = new T[arrayLength];
//     listSize = 0;
// }


// Q4
template<class T>
arrayList<T>::arrayList(int initialCapacity, int increaseStep)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        // throw s.str();
    }

    arrayLength = initialCapacity;
    IncreaseStep = increaseStep;
    element = new T[arrayLength];
    InitialArrayLength = initialCapacity;
    listSize = 0;
}

// 复制构造函数
template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    IncreaseStep = theList.IncreaseStep;
    element = new T[arrayLength];
    InitialArrayLength = theList.InitialArrayLength;
    // 将数组数据复制到当前位置
    std::copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index= "<< theIndex << " size = " << listSize;
        // throw s.str();
    }
}

template <class T>
T& arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T& theElement) const
{
    // 返回元素第一次出现时的索引
    // find函数找到的是对应元素的地址，需要减去数组首地址就得到了元素的索引
    int theIndex = (int)(std::find(element, element+listSize,theElement)-element);
    if(theIndex == listSize)
        return -1;
    else
        return theIndex;
}

template <class T>
void arrayList<T>::erase(int theIndex)
{
    // 将后边的元素整体向前移动，然后删除空余的尾项
    checkIndex(theIndex);
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T(); // 删除最后一个元素（已经被向前移动了一个了）

    // Q20(1)
    if(listSize < arrayLength/4)
    {
        int newSize = std::max(arrayLength/2, InitialArrayLength);
        T* temp = new T[newSize];
        changeLength1D(element, arrayLength, newSize);
            arrayLength = newSize;
    }
}

template <class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
    // 首先检查无效索引
    checkIndex(theIndex);

    // 有效索引，确定数组是否已满
    if(listSize == arrayLength)
    {
        // 将已满的数组空间扩充到二倍
        // Q4问题所要求的增长方式
        // changeLength1D(element, arrayLength, 2 * arrayLength);
        if(IncreaseStep == 0)
        {
            changeLength1D(element, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        }
        else
        {
            changeLength1D(element, arrayLength, arrayLength + IncreaseStep);
            arrayLength += IncreaseStep;
        } 
    }

    // 将数组元素向右移动一个位置
    // 从后往前按序移动
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    listSize++;
}

template <class T>
void arrayList<T>::output(std::ostream &out) const
{
    std::copy(element, element + listSize, std::ostream_iterator<T>(out, "  "));
}

template <class T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
    x.output(out);
    return out;
}
// Q8
template <class U>
bool operator==(arrayList<U>& left, arrayList<U>& right)
{
    // 尺寸相等的前提下有可能相等
    if(left.size() == right.size())
    {
        for(int i=0; i < left.size(); i++)
        {
            if(left[i] != right[i])
                return false;
        }
        return true;
    }
    return false;
}

template <class T>
void arrayList<T>::trimToSize()
{
    int length = std::max(listSize, 1);
    changeLength1D(element, arrayLength, length);
    arrayLength = length;
    listSize = length;
}

template <class T>
void arrayList<T>::setSize(int newSize)
{
    int newlistsize = newSize;
    if(newSize < listSize)
    {
        for (;newSize < listSize; newSize++)
            element[newSize].~T();
            // element[newSize] = 0;
        listSize = newlistsize;
    }    
}

template <class T>
bool arrayList<T>::operator<(const arrayList<T>& right)
{
    int bothLength = std::min(this->size(), right.size());
    for(int i=0; i<bothLength; i++)
    {
        if((*this)[i]<right[i])
            return true;
        else if((*this)[i]>right[i])
            return false;
    }
    if(this->size() < right.size())
        return true;
    else 
        return false;
}

template <class T>
void arrayList<T>::operator=(const arrayList<T>& theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    T* deleteArray = element;
    element = new T[arrayLength];
    // 将数组数据复制到当前位置
    std::copy(theList.element, theList.element + listSize, element);
    delete [] deleteArray;
}


template <class T>
void arrayList<T>::push_back(const T& theElement)
{
    // 有效索引，确定数组是否已满
    if(listSize == arrayLength)
    {
        if(IncreaseStep == 0)
        {
            changeLength1D(element, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        }
        else
        {
            changeLength1D(element, arrayLength, arrayLength + IncreaseStep);
            arrayLength += IncreaseStep;
        }        
    }
    element[listSize] = theElement;
    listSize++;
}

template <class T>
void arrayList<T>::pop_back()
{
    if(listSize > 0)
    {
        --listSize;
        element[listSize].~T();
    }
    // Q20(1)
    if(listSize < arrayLength/4)
    {
        int newSize = std::max(arrayLength/2, InitialArrayLength);
        T* temp = new T[newSize];
        changeLength1D(element, arrayLength, newSize);
            arrayLength = newSize;
    }
}

template <class T>
T arrayList<T>::set(int theIndex, const T& theElement)
{
    T temp = element[theIndex];
    element[theIndex] = theElement;
    return temp;
}

template <class T>
void arrayList<T>::clear()
{
    while (listSize)
        pop_back();
}

template <class T>
void arrayList<T>::removeRange(const int& startIndex, const int& endIndex)
{
    // 将后边的元素整体向前移动，然后删除空余的尾项
    checkIndex(endIndex);
    int oldLength = listSize;
    std::copy(element + endIndex + 1, element + listSize, element + startIndex);
    for(; listSize > oldLength - endIndex + startIndex - 1; --listSize)
        element[listSize-1].~T(); // 删除最后一个元素（已经被向前移动了一个了）
    
    // Q20(1)
    if(listSize < arrayLength/4)
    {
        int newSize = std::max(arrayLength/2, InitialArrayLength);
        T* temp = new T[newSize];
        changeLength1D(element, arrayLength, newSize);
            arrayLength = newSize;
    }
}

template <class T>
int arrayList<T>::lastIndex(const T& theElement)
{
    for(int i=listSize-1;i>0;i--)
        if(theElement == element[i])
            return i;
    return -1;
}

template <class T>
void arrayList<T>::reverse(const int& startIndex, const int& endIndex)
{
    for(int i=0; i<=(endIndex-startIndex)/2; i++)
    {
        T temp = element[startIndex + i];
        element[startIndex + i] = element[endIndex - i];
        element[endIndex - i] = temp;
    }
}

template <class T>
void arrayList<T>::leftShift(const int& i)
{
    reverse(0, listSize-1);
    std::cout << *this << std::endl;
    reverse(0, listSize - 1- i);
    std::cout << *this << std::endl;
    for(int j=0;j<i;j++)
    {
        // 这里已经有对listSize自身大小的操作了
        pop_back();
    }
}

template <class T>
void arrayList<T>::LeftMove(const int& i)
{
    reverse(0, listSize-1);
    reverse(0, listSize-1-i);
    reverse(listSize-1, listSize-i);
}

template <class T>
void arrayList<T>::half()
{
    int deleteLength = listSize / 2;
    int extraLength = listSize % 2;
    for(int i=0;i<=deleteLength;i++)
        element[i+1]=element[2*i+2];
    for(int i=deleteLength+extraLength;i<listSize;i++)
        element[i].~T();
    listSize -= deleteLength;
}

template <class T>
void arrayList<T>::meld(arrayList<T>& a, arrayList<T>& b)
{
    clear();
    int sameLength = std::min(a.size(), b.size());
    for(int i=0;i<sameLength;i++)
    {
        push_back(a[i]);
        push_back(b[i]);
    }
    if(a.size()<b.size())
    {
        for(int i=a.size(); i< b.size(); i++)
            push_back(b[i]);
    }
    else
    {
        for(int i=b.size(); i< a.size(); i++)
            push_back(a[i]);
    }
    
}

template <class T>
void arrayList<T>::swap(arrayList<T>& theList)
{
    // 需要先重载 = 运算符
    arrayList<T> temp = *this;
    // arrayList<T> *temp = new arrayList<T>(*this); // 这里申请的新地址应该怎么释放
    std::cout << "this" << *this << "   temp:  " << temp << std::endl;
    *this = theList;
    theList = temp;
}

#endif
