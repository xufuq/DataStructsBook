#include <iostream>
#include "arrayStack.h"

using namespace  std;

int main()
{
    arrayStack<int> stack0(20), stack1(20), stack2(20);
    stack0.input();
    try
    {
        cout << stack0.top() << std::endl;
        stack0.devide(stack1, stack2);
        cout << stack1 << endl << stack2 << endl;
        stack1.meld(stack2);
        cout << stack1 << endl;
    }
    catch (Err &err)
    {
        std::cerr << err.what() << endl;
    }
    return 0;
}
