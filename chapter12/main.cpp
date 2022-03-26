#include <iostream>
#include "maxHeap.h"
#include "maxHblt.h"

using namespace std;

int main() {
    int heapArray[] = {-1,3,5,6,7,20,8,2,9,12,15,30,17};
    maxHeap<int> myMaxHeap;
    myMaxHeap.initialize(heapArray, 12);
    cout << myMaxHeap << endl;
    myMaxHeap.remove(3);
    cout << myMaxHeap << endl;
//    myMaxHeap.changeMax(1);
//    cout << myMaxHeap << endl;
//    myMaxHeap.pop();
//    cout << myMaxHeap << endl;
//    maxHeap<int> myMaxHeap2(myMaxHeap);
//    cout << myMaxHeap2 << endl;

    return 0;
}
