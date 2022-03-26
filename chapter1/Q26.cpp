#include <iostream>
using namespace std;

void G(int n)
{
    if(n == 1)
    {
        cout << 1;
    }
    else
    {
        G(n-1);
        cout << n;
        G(n-1);
    }
}

int main()
{
    G(5);
    return 0;
}
