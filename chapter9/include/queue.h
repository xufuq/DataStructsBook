//
// Created by Dell on 2021/4/26.
//

#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

template<class T>
class queue
{
public:
    virtual ~queue();
    virtual bool empty() const =0;
    virtual int size() const = 0;
    virtual T& front() =0; // 头元素的引用
    virtual T& back() = 0; // 尾元素的引用
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};


#endif //DATASTRUCTURES_QUEUE_H
