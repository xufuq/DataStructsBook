#include <iostream>
#include "code.h"

int main() {
    vector<vector<int>> sourceMat, targetMat;
    splitFromMatrix(sourceMat, targetMat, pair<int, int>(0,0), pair<int, int>(1,1));
    return 0;
}
