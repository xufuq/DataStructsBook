#include <iostream>
using namespace std;

int t1(int n)
{
    if(n == 0)
    {
        return 2;
    }
    else
    {
        return 2 + t1(n - 1);
    }
    
}

int t5(int n)
{
    if(n == 0)
        return 1;
    else
    {
        return 3*t5(n-1);
    }
    
}

int main()
{
    cout<<t1(5)<<endl;
    cout<<t5(5)<<endl;
    return 0;
}