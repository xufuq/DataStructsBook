#include <iostream>

using namespace std;

int F(int n)
{
    if (n==0)
        return 0;
    else if(n==1)
        return 1;
    else
        return F(n-1) + F(n-2);
}

int main()
{
    cout<<F(10)<<endl;
    return 0;
}