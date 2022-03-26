#ifndef ARRAYSTACK_STACK_H
#define ARRAYSTACK_STACK_H
#include <algorithm>

template<class T>
class stack
{
public:
    virtual ~stack() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& top() = 0;
    virtual void pop() const = 0;
    virtual void push(const T& theElement) = 0;
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

#endif //ARRAYSTACK_STACK_H
