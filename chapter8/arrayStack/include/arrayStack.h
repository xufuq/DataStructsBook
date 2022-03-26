#ifndef ARRAYSTACK_ARRAYSTACK_H
#define ARRAYSTACK_ARRAYSTACK_H
#include "stack.h"
#include <exception>
#include <string>

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
class arrayStack
{
    template<class U>
    friend std::ostream & operator << (std::ostream &os, arrayStack<U> &stack);
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() {delete [] stack; }
    bool empty() const { return stackTop == -1;}
    int size() const {return stackTop+1;}
    T& top();
    void pop()
    {
        if (stackTop == -1)
            return;
        stack[stackTop--].~T();
    }
    void push(const T& theElement);
    void input();
    void devide(arrayStack<T> &firstStack, arrayStack<T> &secondStack);
    void meld(arrayStack<T> &secondStack);
private:
    int stackTop;
    int arrayLength;
    T* stack;
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::cout << "the Initial capacity is " << initialCapacity << std::endl;
        return;
    }
    arrayLength = initialCapacity;
    stack = new T[initialCapacity];
    stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T &theElement)
{
    if (stackTop == arrayLength - 1)
    {
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength = 2 * arrayLength;
    }
    // 栈顶插入
    stack[++stackTop] = theElement;
}

template<class T>
void arrayStack<T>::input()
{
    // input the element
    T element;
    std::cout << "Input the data!" << std::endl;
    std::cout << "Ctrl+D stop the input!" << std::endl;
    while (std::cin >> element)
    {
        push(element);
    }
}

template<class T>
T &arrayStack<T>::top()
{
    if (stackTop == -1)
        throw Err("There is no data in stack!");
    return stack[stackTop];
}

template<class T>
void arrayStack<T>::devide(arrayStack<T> &firstStack, arrayStack<T> &secondStack)
{
    if (empty())
    {
        std::cerr << "The stack is empty, can't be devided!" << std::endl;
        return;
    }
    int middleLength = (stackTop+1)/2;
    if (firstStack.arrayLength < middleLength)
        changeLength1D(firstStack.stack, firstStack.arrayLength, middleLength);
    if (secondStack.arrayLength < middleLength)
        changeLength1D(secondStack.stack, secondStack.arrayLength, middleLength);
    std::copy(stack, stack+middleLength+1, firstStack.stack);
    firstStack.stackTop = middleLength - 1;
    secondStack.stackTop = stackTop - middleLength;
    std::copy(stack+middleLength, stack + stackTop + 1, secondStack.stack);
}

template<class U>
std::ostream &operator<<(std::ostream &os, arrayStack<U> &stack)
{
    for (int i=0; i <= stack.stackTop; i++)
        os << stack.stack[i] << " ";
    return os;
}

template<class T>
void arrayStack<T>::meld(arrayStack<T> &secondStack)
{
    int newTop = stackTop + secondStack.stackTop + 2;
    if (newTop > arrayLength)
    {
        changeLength1D(stack, stackTop, newTop);
        arrayLength = newTop;
    }
    std::copy(secondStack.stack, secondStack.stack + secondStack.stackTop + 1, stack + stackTop + 1);
    stackTop = newTop - 1;
}


#endif //ARRAYSTACK_ARRAYSTACK_H
