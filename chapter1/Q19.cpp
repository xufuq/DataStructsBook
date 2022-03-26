#include <iostream>

using namespace std;

int multi(int n)
{
    if(n<2)
        return 1;
    else
        return n * multi(n-1);
}

int main()
{
    int result = multi(10);
    cout<<result<<endl;
    return 0;
}