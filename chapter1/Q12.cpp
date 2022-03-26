#include <iostream>

using namespace std;

template <class T>
void make2dArray(T ** &x, int numberOfrows, int *rowSize)
{
    // 先将x实例化，传入的参数只有一个名字，没有实际位置
    x = new T *[numberOfrows];
    for(int i=0;i<numberOfrows;++i)
        x[i] = new T [rowSize[i]];
}

template<class T>
void delete2dArray(T ** &x, int numberOfrows)
{
    for(int i=0;i<numberOfrows;++i)
        delete [] x[i];
    delete [] x;
    x=NULL;
}

int main()
{
    // 当行维度和列维度都未知时，利用指针的指针进行
    int ** x;
    int rows=5;
    int rowSize[]={3,4,8,6,3};
    make2dArray(x, rows, rowSize);
    x[2][6]=5;
    cout<< x[2][6]<<endl;
    delete2dArray(x, rows);
    return 0;
}