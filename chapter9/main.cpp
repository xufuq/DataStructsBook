#include <iostream>
#include "arrayQueue.h"

int main() {
//    arrayQueue<int> myQueue0(10);
//    std::cin >> myQueue0;

    char *a="Trend";
    char **b=&a;
    *b="commercial";
    char *c=++a;
    a="talents";
    std::cout << *++c << std::endl;

    return 0;
}
