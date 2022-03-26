#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>
using namespace std;

char str[]={'k', 'a', 'g', 'n', 'f', 'b','w','h'};
// int str[] = {5, 9, 8, 3, 7, 5};
template <class T>
void permutations(T list[], int &k, int m)
{
    sort(list, list + m);
    do
    {
        copy(list, list + m, ostream_iterator<T>(cout, ""));
        cout<<endl;
        k++;
    } while (next_permutation(list, list + m));;
}

int main()
{
    int num=0;
    permutations(str, num, 8);
    cout << num<<endl;
    return 0;    
}