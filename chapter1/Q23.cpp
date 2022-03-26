#include <iostream>

using namespace std;

int gcd(int x, int y)
{
    if(y==0)
        return x;
    else
    {
        return gcd(y, x % y);
    }
        
}

int main()
{
    cout<<gcd(112, 42)<<endl;
    return 0;
}