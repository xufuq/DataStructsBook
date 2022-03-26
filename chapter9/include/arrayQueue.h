//
// Created by Dell on 2021/4/26.
//

#ifndef CHAPTER9_ARRAYQUEUE_H
#define CHAPTER9_ARRAYQUEUE_H
#include "queue.h"
#include <iostream>
#include <unordered_map>
#include <hash_map>

template<class T>
class arrayQueue : public queue<T>
{
    friend std::istream& operator>> (std::istream &is, arrayQueue<T>& myQueue);
    friend std::ostream& operator<< (std::ostream &os, const arrayQueue<T>& myQueue);
public:
    arrayQueue(int initLength);
    ~arrayQueue();
    bool empty() const { return queueFont==queueBack;}
    int size() const {
        int length=queueBack-queueFont;
        if (length<0)
            return length+arrayLength;
        return length;
    }
    T& front(){return queue[queueFont];}
    T& back(){return queue[queueBack];}
    void pop();
    void push(const T& theElement);
    void doubleLength();
private:
    int queueFont, queueBack, arrayLength;
    T* queue;
};

template<class T>
void arrayQueue<T>::push(const T& theElement) {
    int length=queueBack-queueFont;
    if (length<0)
        length+=arrayLength;
    if(length==arrayLength-1) // 如果长度超标，就延长
        doubleLength();
    ++queueBack;
    queueBack=queueBack%arrayLength;
    queue[queueBack]=theElement;
}

template<class T>
void arrayQueue<T>::pop() {
    if (empty())
        std::cout << " the queue is empty!" << std::endl;
    else{
        queueFont=(queueFont+1)%arrayLength;
        queue[queueFont].~T();
    }
}

template<class T>
void arrayQueue<T>::doubleLength() {
    T* newQueue = new T[2 * arrayLength];
    int start = (queueFont+1)%arrayLength; // 第一个元素的位置
    if(start<2) // queueBack还没有重新回到0
        std::copy(queue + start, queue + arrayLength, newQueue);
    else{
        std::copy(queue + start, queue + arrayLength, newQueue);
        std::copy(queue, queue + queueBack+1, newQueue + arrayLength-start);
    }
    queueFont=2*arrayLength-1;
    queueBack=arrayLength-2;
    arrayLength*=2;
    delete [] queue;
    queue=newQueue;
}

template<class T>
arrayQueue<T>::arrayQueue(int initLength) {
    arrayLength=initLength;
    queueFont=arrayLength-1;
    queueBack=queueFont;
    queue=new T[arrayLength];
}

template<class T>
std::istream &operator>>(std::istream &is, arrayQueue<T> &myQueue) {
    T element;
    while (is >> element)
        myQueue.push(element);
    return is;
}

template<class T>
arrayQueue<T>::~arrayQueue() {
    delete[] queue;
}

template<class T>
std::ostream &operator<<(std::ostream &os, const arrayQueue<T> &myQueue) {
    for(int queueCurrent=myQueue.queueFont;queueCurrent!=myQueue.queueBack;){
        ++queueCurrent;
        queueCurrent%=myQueue.arrayLength;
        os << myQueue.queue[queueCurrent];
    }
    return os;
}

#endif //CHAPTER9_ARRAYQUEUE_H
