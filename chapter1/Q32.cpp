#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// template <class T>
// int count(T *start, T *end, T value)
// {
//     int num=0;
//     for(;start<end;start++)
//     {
//         if(*start==value)
//             num++;
//     }
//     return num;
// }

int main()
{
    char arr[]={'g', 'g', 'h', 'd', 'g', 'e', 'h'};
    cout << count(arr, end(arr), 'h') << endl;
    return 0;
}