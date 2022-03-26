//
// Created by Dell on 2021/6/7.
//
#include "dictionary.h"
#include <utility>
#include "iostream"
#include "algorithm"


#ifndef TEST_SORTEDARRAYLIST_H
#define TEST_SORTEDARRAYLIST_H


template<class K, class E>
class sortedArrayList : public dictionary<K, E>
{
    template<class M, class N>
    friend std::ostream &operator<<(std::ostream &os, sortedArrayList<M, N>&);
public:
    explicit sortedArrayList(int initialLength = 10);
    bool empty() const;
    int size() const;
    std::pair<const K, E>* find(const K&) const;
    void erase(const K&);
    void insert(const std::pair<const K, E>& );

private:
//    std::pair<const K, E>* element;
    std::pair<K, E>* element; // 这里不能用const，否则后边会修改不了顺序，不能插入
    int mapSize, arrayLength;
};

template<class K, class E>
sortedArrayList<K, E>::sortedArrayList(int initialLength) {
    arrayLength=initialLength;
    element = new std::pair<K, E>[arrayLength];
    mapSize=0;
}

template<class K, class E>
bool sortedArrayList<K, E>::empty() const {
    return mapSize==0;
}

template<class K, class E>
int sortedArrayList<K, E>::size() const {
    return mapSize;
}

template<class K, class E>
std::pair<const K, E>* sortedArrayList<K, E>::find(const K& key) const {
    int i=0;
    for (i=0;i<mapSize;++i){
        if((element+i)->first >= key)
            break;
    }
    if(!empty() && (element+i)->first == key)
        return (std::pair<const K, E>*)element+i; // 这里进行类型转换
    return NULL;
}

template<class K, class E>
void sortedArrayList<K, E>::insert(const std::pair<const K, E>& thePair){
    if (mapSize==arrayLength){ // 检查长度
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength*=2;
    }
    int i=0;
    for (i=0;i<mapSize;++i){
        if((element+i)->first >= thePair.first)
            break;
    }

    if (mapSize !=0 && (element+i)->first == thePair.first){ // 大小不等于零保证原来就存在元素
        (element+i)->second = thePair.second;
        return;
    }

    // 全体向后移一个位置
    if (i<mapSize)
        std::copy_backward(element+i, element+mapSize, element+mapSize+1); //这里从后边拷贝赋值，是因为共享内存
    *(element+i) = thePair;
    ++mapSize;
}

template<class K, class E>
void sortedArrayList<K, E>::erase(const K& theKey){
    int i=0;
    for (i=0;i<mapSize;++i){
        if((element+i)->first >= theKey)
            break;
    }
    if ((element+i)->first == theKey){
        std::copy(element+i+1, element+mapSize, element+i); // 主义前后两个赋值函数的区别
//        delete (element+mapSize); // 这里怎么释放内存
        --mapSize;
    }
}

template<class K, class E>
std::ostream &operator<<(std::ostream &os, sortedArrayList<K, E> &map) {
    for (int i = 0; i < map.size(); ++i)
        os << (map.element+i)->first << "   " << (map.element+i)->second << std::endl;
    return os;
}

#endif //TEST_SORTEDARRAYLIST_H
