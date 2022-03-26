#include <iostream>
#include <vector>
using namespace std;

template <class T>
T accumulate(typename vector<T>::iterator start, typename vector<T>::iterator end, T initialValue, T (*pf)(T &a, T &b))
{
    for(;start < end; ++start)
    {
        initialValue = pf(initialValue, *start);
    }
    return initialValue;
}

template <class T>
T multi(T &a, T &b)
{
    return a * b;
}

template <class T>
T add(T &a, T &b)
{
    return a + b;
}

int main()
{
    vector<double> vec={0.1, 6.3, 9.0, 5, 4.8, 3.5};
    double initialValue=1.0;
    double sum = accumulate(vec.begin(), vec.end(), initialValue, multi);
    cout << sum << endl;

    sum = accumulate(vec.begin(), vec.end(), initialValue, add);
    cout << sum << endl;
    return 0;
}