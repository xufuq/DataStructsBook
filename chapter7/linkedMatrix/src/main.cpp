#include <iostream>
#include "linkedMatrix.h"
#include "printError.h"

using namespace std;

int main()
{
    linkedMatrix<int> m0(4,5),m1(5, 4), m2(4,4);
//    m0.insert(2,3,5);
//    m0.insert(1,4,3);
//    m0.insert(2,2,6);
//    m0.insert(2,1,1);
//    cout << m0 << std::endl;
//    m0.set(2,2,100);
//    cout << m0.get(2, 2) << "  " << m0.get(1,1) <<std::endl;
//    m1 = m0.transpose();
//    cout << m1 << std::endl;
//    m2 = m0.add(m1);
//    cout << m2 << std::endl;
//    m2 = m0.minus(m1);
//    cout << m2 << std::endl;
    m0.insert(1, 3, 3);
    m0.insert(1, 4, 6);
    m0.insert(1, 5, 4);
    m0.insert(2, 1, 2);
    m0.insert(2, 2, 5);
    m0.insert(2, 3, 6);
    m0.insert(2, 5, 2);
    m0.insert(3, 1, 2);
    m0.insert(3, 4, 1);
    m0.insert(3, 5, 5);
    m0.insert(4, 1, 7);
    m0.insert(4, 2, 3);
    m0.insert(4, 5, 6);
    m1.insert(1, 1, 4);
    m1.insert(1, 2, 3);
    m1.insert(1, 4, 5);
    m1.insert(2, 1, 7);
    m1.insert(2, 2, 8);
    m1.insert(2, 3, 9);
    m1.insert(3, 1, 6);
    m1.insert(4, 3, 3);
    m1.insert(5, 2, 2);
    m1.insert(5, 4, 4);
    m2 = m0.multiple(m1);
    cout << m2 << std::endl;
    return 0;
}