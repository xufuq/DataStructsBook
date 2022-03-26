//
// Created by Dell on 2021/6/28.
//

#ifndef CHAPTER14_BSTREE_H
#define CHAPTER14_BSTREE_H

#include "dictionary.h"

template<class K, class E>
class bsTree : dictionary<K, E>
{
public:
    virtual void ascend() = 0; // 继承了dic中的很多函数
};


#endif //CHAPTER14_BSTREE_H
