//
// Created by Dell on 2021/7/20.
//

#ifndef CHAPTER18_CODE_H
#define CHAPTER18_CODE_H

#include "vector" // 利用二维vector表示矩阵
using namespace std;

// 这四个是内部调用函数，四个矩阵分别计算的原因是防止有不是2的整数倍的n出现
void splitFromMatrix(const vector<vector<int>> &sourceMat, vector<vector<int>> &targetMat, pair<int, int> startPoint, pair<int, int> endPoint);
void meldToMatrix(const vector<vector<int>> &sourceMat, vector<vector<int>> &targetMat, pair<int, int> startPoint, pair<int, int> endPoint);
vector<vector<int>> addMatrix(const vector<vector<int>> &sourceMatA, const vector<vector<int>> &sourceMatB);
vector<vector<int>> addMatrix(const vector<vector<int>> &sourceMatA, const vector<vector<int>> &sourceMatB);

vector<vector<int>> multiMat(const vector<vector<int>> &sourceMatA, const vector<vector<int>> &sourceMatB);

#endif //CHAPTER18_CODE_H
