//
// Created by Dell on 2021/7/20.
//

#include "code.h"
#include "iostream"

void splitFromMatrix(const vector<vector<int>> &sourceMat, vector<vector<int>> &targetMat, pair<int, int> startPoint, pair<int, int> endPoint){
    if (startPoint.first>endPoint.first || startPoint.second>endPoint.second || endPoint.first>sourceMat.size() || endPoint.second>sourceMat[0].size()){
        cout << "the index is incorrect!" << endl;
        return;
    }
    targetMat=vector<vector<int>>(endPoint.first-startPoint.first, vector<int>(endPoint.second-startPoint.second));
    for(int i=startPoint.first;i<endPoint.first;++i)
        copy(sourceMat[i].begin()+startPoint.second, sourceMat[i].begin()+endPoint.second, targetMat[i-startPoint.first].begin());
}



void meldToMatrix(const vector<vector<int>> &sourceMat, vector<vector<int>> &targetMat, pair<int, int> startPoint){
    if (startPoint.first>targetMat.size() || startPoint.second>targetMat[0].size()){
        cout << "the index is incorrect!" << endl;
        return;
    }
    int i=0;
    for(auto sourceRow:sourceMat){
        copy(sourceRow.begin(), sourceRow.end(), targetMat[i+startPoint.first].begin());
        ++i;
    }
}

vector<vector<int>> multiMat(const vector<vector<int>> &sourceMatA, const vector<vector<int>> &sourceMatB){
    if (sourceMatA.size()>8){
        vector<vector<int>> sourceMatA11, sourceMatA12, sourceMatA21, sourceMatA22,
                            sourceMatB11, sourceMatB12, sourceMatB21, sourceMatB22;
        int matSize = sourceMatA.size(), halfMatSize = matSize/2;
        splitFromMatrix(sourceMatA, sourceMatA11, pair<int, int>(0,0), pair<int, int>(halfMatSize, halfMatSize));
        splitFromMatrix(sourceMatA, sourceMatA12, pair<int, int>(0,halfMatSize), pair<int, int>(halfMatSize, matSize));
        splitFromMatrix(sourceMatA, sourceMatA21, pair<int, int>(halfMatSize,0), pair<int, int>(matSize, halfMatSize));
        splitFromMatrix(sourceMatA, sourceMatA22, pair<int, int>(halfMatSize,halfMatSize), pair<int, int>(matSize, matSize));

        splitFromMatrix(sourceMatB, sourceMatB11, pair<int, int>(0,0), pair<int, int>(halfMatSize, halfMatSize));
        splitFromMatrix(sourceMatB, sourceMatB12, pair<int, int>(0,halfMatSize), pair<int, int>(halfMatSize, matSize));
        splitFromMatrix(sourceMatB, sourceMatB21, pair<int, int>(halfMatSize,0), pair<int, int>(matSize, halfMatSize));
        splitFromMatrix(sourceMatB, sourceMatB22, pair<int, int>(halfMatSize,halfMatSize), pair<int, int>(matSize, matSize));

        vector<vector<int>> D = multiMat(sourceMatA11, sourceMatB12-sourceMatB22);
    } else{

    }
}