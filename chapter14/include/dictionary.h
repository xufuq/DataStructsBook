//
// Created by Dell on 2021/6/7.
//
#include <utility>
#include "iostream"


#ifndef TEST_DICTIONARY_H
#define TEST_DICTIONARY_H

template<class K, class E>
class dictionary
{
public:
    virtual ~dictionary() = default;;
    virtual bool empty() const = 0;//
    virtual int size() const = 0;
    virtual std::pair<const K, E>* find(const K&) const = 0; // 关键字不能被改变
    virtual void erase(const K&) = 0;
    virtual void insert(const std::pair<const K, E>&) = 0;
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

#endif //TEST_DICTIONARY_H
