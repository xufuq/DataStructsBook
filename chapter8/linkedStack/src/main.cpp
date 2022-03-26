#include <iostream>
#include "linkedStack.h"

using namespace std;

template<class T>
void moveTower(int n, linkedStack<T>& x, linkedStack<T>& y, linkedStack<T>& z)
{
    if (n > 0)
    {
        moveTower(n-1,x,z,y);
        T d = x.top();
        x.pop();
        y.push(d);
//        cout << n << "  ";
        moveTower(n-1,z,y,x);
    }
}

template<class T>
void towersOfHanoi(int n, linkedStack<T>& x, linkedStack<T>& y, linkedStack<T>& z)
{
    for (int i=n;i>0;i--)
        x.push(i);
    cout << x << endl;
    moveTower(n, x, y, z);
    cout << y << endl;
}

int main()
{
    linkedStack<int> stack0, stack1, stack2, stack3;
    try
    {
//        stack0.pop();
        stack0.push(2);
        stack0.push(3);
        stack0.push(5);
        stack0.push(100);
        stack0.push(78);
        cout << stack0.top() << endl;
        stack0.pop();
        cout << stack0.top() << endl;
        chainNode<int>* popnode = stack0.popNode();
        cout << popnode->element << endl;
        cout << stack0.top() << endl;
        towersOfHanoi(25, stack1, stack2, stack3);
    }
    catch (Err &err)
    {
        cerr << err.what() << endl;
    }
    cout << "test" << endl;
    return 0;
}
