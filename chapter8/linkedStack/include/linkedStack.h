#ifndef LINKEDSTACK_LINKEDSTACK_H
#define LINKEDSTACK_LINKEDSTACK_H
#include "stack.h"
#include <exception>

class Err : public std::exception
{
public:
    Err(std::string ss) {str = ss;}
    virtual const char* what() const throw()
    {
        return str.c_str();
    }
private:
    std::string str;
};

template<class T>
struct chainNode
{
    T element;
    chainNode<T>* next;

    // function
    chainNode() {}
    chainNode(const T& element) {this->element=element;}
    chainNode(const T& element, chainNode<T>* next) {this->element=element;this->next=next;}
};

template<class T>
class linkedStack : public stack<T>
{
    template<class U>
    friend std::ostream &operator<<(std::ostream& os, linkedStack<U>& x);
public:
    linkedStack();
    ~linkedStack();
    bool empty() const { return stackSize == 0;}
    int size() const {return stackSize;}
    T& top();
    void pop();
    void push(const T& theElement);
    void pushNode(chainNode<T>* theNode);
    chainNode<T>* popNode();
private:
    chainNode<T>* stackTop;
    int stackSize;
};

template<class T>
linkedStack<T>::linkedStack()
{
    stackTop = NULL;
    stackSize = 0;
}

template<class T>
linkedStack<T>::~linkedStack()
{
    chainNode<T>* deleteNode;
    while (stackSize-- > 0)
    {
        deleteNode = stackTop;
        stackTop = stackTop->next;
        delete deleteNode;
    }
}

template<class T>
void linkedStack<T>::pop()
{
    if (stackSize != 0)
    {
        chainNode<T>* deleteNode = stackTop;
        stackTop = stackTop->next;
        delete deleteNode;
        stackSize--;
    }
    else
        throw Err("The stack is empty, can't pop!");
}

template<class T>
T &linkedStack<T>::top()
{
    if (stackSize == 0)
        throw Err("The stack is empty, has no top element!");
    return stackTop->element;
}

template<class T>
void linkedStack<T>::push(const T &theElement)
{
    if (stackSize == 0)
    {
        stackTop = new chainNode<T>(theElement, NULL);
        stackSize++;
    }
    else
    {
        stackTop = new chainNode<T>(theElement, stackTop);
        stackSize++;
    }
}

template<class T>
void linkedStack<T>::pushNode(chainNode<T> *theNode)
{
    theNode->next = stackTop;
    stackTop = theNode;
    stackSize++;
}

template<class T>
chainNode<T> *linkedStack<T>::popNode()
{
    if (stackSize == 0)
        throw Err("The stack is empty, can't pop Node!");
    chainNode<T>* popnode = stackTop;
    stackTop = stackTop->next;
    popnode->next = NULL;
    stackSize--;
    return popnode;
}

template<class U>
std::ostream &operator<<(std::ostream &os, linkedStack<U> &x)
{
    for (chainNode<U> *firstNode = x.stackTop;firstNode != NULL;firstNode = firstNode->next)
        os << firstNode->element << "  ";
    return os;
}


#endif //LINKEDSTACK_LINKEDSTACK_H
