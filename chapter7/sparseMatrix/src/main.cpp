#include <iostream>
#include "sparseMatrix.h"

using namespace std;

int main()
{
    sparseMatrix<float> m1, m2, m3;
    cin >> m1 >> m2;
    cout << "m1: " << endl << m1 << "m2: " << endl << m2 << endl;
//    m3 = m1.add(m2);
//    cout << "m3: " << endl << m3 << endl;
//    m1 = m1.transpose();
//    cout << "m1: " << endl << m1 << endl;
    m3 = m1.multiple(m2);
    cout << "m3: " << endl << m3 << endl;
    return 0;
}