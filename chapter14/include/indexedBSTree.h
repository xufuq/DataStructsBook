//
// Created by Dell on 2021/6/28.
//

#ifndef CHAPTER14_INDEXEDBSTREE_H
#define CHAPTER14_INDEXEDBSTREE_H

#include "bsTree.h"

template<class K, class E>
class indexedBSTree : bsTree<K, E>
{
public:
    // 这两个单独的函数都是根据所以进行操作
    virtual std::pair<const K, E>* get(int) const = 0;
    virtual void delete(int ) = 0;
private:
    int leftSize;
};

#endif //CHAPTER14_INDEXEDBSTREE_H
