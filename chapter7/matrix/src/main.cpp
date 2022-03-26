#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    matrix<int> m0(3,4);
    matrix<int> m1(4,5);
    for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=4;j++)
            m0(i,j) = 4*(i-1) + j-1;
    }
    for(int i=1;i<=4;i++)
    {
        for(int j=1;j<=5;j++)
            m1(i,j) = 5*(i-1) + j-1;
    }
    cout<<m0<<m1;
    matrix<int> m2;
    m2 = m0*m1;
    m0 += 1;
    cout << "m2: " << m2 << "m0: " << m0;
    matrix<int> m3 = m0.reverse();
    cout << "m3: " << m3;
    cin >> m1;
    cout << "m1: " << m1;
    return 0;
}