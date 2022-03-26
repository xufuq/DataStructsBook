#include "arrayList.h"
#include <iostream>
#include "vectorList.h"

int main()
{
    arrayList<int> arrayTest(10);
    for(int i=0;i<20;i++)
        arrayTest.insert(i, i);
    arrayList<int> arrayTest2(arrayTest);
    arrayTest.setSize(15);
    arrayTest.erase(12);
    arrayTest.pop_back();
    arrayTest.push_back(55);
    arrayTest.swap(arrayTest2);
    std::cout << arrayTest <<std::endl;
    std::cout << arrayTest2 <<std::endl;
    // arrayTest[2]=100;
    std::cout << (arrayTest == arrayTest2)<< std::endl << (arrayTest != arrayTest2) << std::endl << (arrayTest < arrayTest2) << std::endl;
    std::cout << arrayTest.set(2, 66) << std::endl << arrayTest[2] << std::endl;
    // arrayTest.clear();
    arrayTest.removeRange(2, 5);
    std::cout << arrayTest <<std::endl;
    // arrayTest.removeRange(0, 0);
    // arrayTest.reverse(0, arrayTest.size()-1);
    // std::cout << arrayTest <<std::endl;
    arrayTest.leftShift(1);
    std::cout << arrayTest <<std::endl;
    arrayTest.half();
    std::cout << arrayTest <<std::endl;
    arrayTest.LeftMove(2);
    std::cout << arrayTest <<std::endl;
    std::cout << arrayTest.lastIndex(17) << std::endl;

    std::cout << arrayTest <<std::endl;
    std::cout << arrayTest2 <<std::endl;
    arrayList<int> arrayTest3(10);
    arrayTest3.meld(arrayTest, arrayTest2);
    std::cout << arrayTest3 <<std::endl;

    arrayList<int>::myIterator it = arrayTest3.begin();

    std::cout << "----------------------分割线---------------------------------" << std::endl;

    vectorList<int> vectorTest1(10),vectorTest2(10);
    for(int i=0; i<10;i++)
    {
        vectorTest1.insert(i, 3*i+5);
        vectorTest2.insert(i, 5*i-3);
    }
    std::cout << vectorTest1 << std::endl;
    std::cout << vectorTest2 << std::endl;
    vectorTest1.half();
    std::cout << vectorTest1 << std::endl;
    vectorList<int> vectorTest3(10);
    vectorTest3.meld(vectorTest1, vectorTest2);
    std::cout << vectorTest3 << std::endl;
    vectorTest3.merge(vectorTest1, vectorTest2);
    std::cout << vectorTest3 << std::endl;
    vectorTest3.split(vectorTest1, vectorTest2);
    std::cout << vectorTest1 << std::endl;
    std::cout << vectorTest2 << std::endl;
    return 0;
}
