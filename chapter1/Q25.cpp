#include <iostream>
using namespace std;

// k是每个循环的起始位置，N是数组总长度
void getSubset(int *arr, int k, int N)
{
    if(k == N)
    {
        for(int j=0;j<N;j++)
        {
            cout << arr[j];
        }
        cout << endl;
        return;
    }

    if(k < N)
    {
        arr[k] = 0;
        getSubset(arr, k+1, N);
        arr[k] = 1;
        getSubset(arr, k+1, N);
    }
}

int main()
{
    int arr[]={0,0,0};
    int N = 3;
    getSubset(arr, 0, N);
    return 0;
}