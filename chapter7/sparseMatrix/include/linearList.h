#ifndef LINEARLIST_H
#define LINEARLIST_H

#include <iostream>


// 只有一系列待实现的方法，没有数据成员
template<class T>
class linearList
{
public:
    virtual ~linearList(){}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    // 返回索引对应的元素的引用
    virtual T& get(int theIndex) const = 0;
    // 删除对应索引的元素
    virtual void erase(int theIndex) = 0;
    // 在对应位置插入元素
    virtual void insert(int theIndex, const T& theElement) = 0;
};

template <class T>
void changeLength1D(T* &a, int oldLength, int newLength)
{
    if(newLength < 0)
    {
        std::cout << "The new Length must bigger than 0"<<std::endl;
        return;
    }
    // 生成一个新的数组指针
    T* temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a+number, temp);
    delete [] a;
    a = temp;
}

// Q3, 改变二位数组的长度
// x是二位数组的指针引用，row为-1时改变第一个维度的长度(行数)，为正值时改变第二个维度的长度(单独一行的长度)
template <class T>
void changeLength2D(T** &x,int row, int oldLength, int newLength)
{
    if(newLength < 0)
    {
        std::cout << "The new Length must bigger than 0"<<std::endl;
        return;
    }
    if(row == -1)
    {
        T** temp = new T* [newLength];
        int number = std::min(oldLength, newLength);
        std::copy(x, x + number, temp);
        for(int i=0;i<oldLength;i++)
            delete [] x[i];
        delete [] x;
        x = temp;
    }
    else
    {
        T* temp = new T[newLength];
        int number = std::min(oldLength, newLength);
        std::copy(x[row], x[row]+number, temp);
        delete [] x[row];
        x[row] = temp;
    }
    
}


#endif