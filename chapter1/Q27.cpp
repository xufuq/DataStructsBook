#include <iostream>
#include <vector>
using namespace std;

template <class T>
T accumulate(typename vector<T>::iterator start, typename vector<T>::iterator end, T initialValue)
{
    for(;start < end; start++)
    {
        initialValue += *start;
    }
    return initialValue;
}

int main()
{
    vector<double> vec={0.1, 6.3, 9.0, 5, 4.8, 3.5};
    double initialValue=0.0;
    double sum = accumulate(vec.begin(), vec.end(), initialValue);
    cout << sum << endl;
    return 0;
}