#include <iostream>

using namespace std;

template <class T>
bool findX(T a, T* arr, int n, int N)
{
    if(a == arr[n])
        return true;
    else if(n == N)
        return false;
    else
        return findX(a, arr, n+1, N);
}

int main()
{
    int N=7;
    int arr[]={0, 8, 69, 6, 7, 35, 4};
    cout<<findX(36, arr, 0, N) <<endl;
    return 0;
}