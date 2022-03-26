#include <iostream>

using namespace std;

int F(int n)
{
    if(n%2==0)
        return n/2;
    else
        return F(3*n+1);
}

int main()
{
    cout<<F(9)<<endl;
    return 0;
}