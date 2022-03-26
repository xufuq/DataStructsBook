#include <iostream>
#include <vector>
using namespace std;


// 利用内置数组类型进行操作
template <class T>
bool copy(T *start, T *end, T *aim)
{
    for(;start<end; ++start, ++aim)
    {
        *aim = *start;
    }
    return true;
}

int main()
{
    int a[] = {5, 9, 8, 3, 7, 5};
    int b[sizeof(a)/sizeof(*a)];
    cout << copy(begin(a), end(a), begin(b)) << endl;
    cout << b[5] << endl;
    return 0;
}