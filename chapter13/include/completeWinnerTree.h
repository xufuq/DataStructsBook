//
// Created by Dell on 2021/6/24.
//

#ifndef CHAPTER13_COMPLETEWINNERTREE_H
#define CHAPTER13_COMPLETEWINNERTREE_H

#include "winnerTree.h"
#include <cmath>
#include "iostream"
#include "vector"

template<class T>
class completeWinnerTree : public winnerTree<T>
{
public:
    ~completeWinnerTree() = default;
    completeWinnerTree()= default;
    void initialize(T *thePlayer, int theNumberOfPlayers);
    [[nodiscard]] int winner() const;
    void rePlay(int thePlayer, T newElement);
    // 返回其序号
    void getSort(int* &mySort);
    void initWithRecursion(T *thePlayers, int theNumberOfPlayers); // 调用私有递归函数
private:
    int Recursion(int leftNode, int RightNode); // 输入的是子节点的序号

    int *tree{};
    T *Player;
    int s{}; // 求2的n次幂
    int lowInnerExt{}; // 最底层内部节点个数
    int lowOuterExt{};  // 最底层外部节点个数
    int offset{};
    int NumberOfPlayers{};
};

// 实现最小赢者树
template<class T>
void completeWinnerTree<T>::initialize(T *thePlayers, int theNumberOfPlayers) {
    // 从左到右遍历右孩子
    // sizeof只能对静态分配的内存球大小
    tree = new int[theNumberOfPlayers]; // 内部节点二叉树数组表示
    NumberOfPlayers = theNumberOfPlayers;
    s = 1 << int(log2(theNumberOfPlayers - 1)); // 求2的n次幂
    lowInnerExt = (theNumberOfPlayers - s); // 最底层内部节点个数
    lowOuterExt = 2 * lowInnerExt;  // 最底层外部节点个数
    offset = 2 * s - 1;
    Player = new T[theNumberOfPlayers + 1];
    std::copy(thePlayers, thePlayers + theNumberOfPlayers + 1, Player);
    for (int i = 2; i <= theNumberOfPlayers;) { // 当外部节点访问结束，遍历也就结束了
        // 需要一直判断当前内部节点是否是右孩子，右孩子的序号都是奇数，对应做孩子是序号减一
        int currentId = i;
        int pTree = 0;
        if (i <= lowOuterExt){
            pTree = (i+offset)/2;
            if (i < lowOuterExt || lowInnerExt%2==0) // 依然在外部节点最底层或者内部节点最底层是偶数
                i += 2;
            else // 是奇数
                ++i;
        } else{ // 倒数第二层外部节点
            pTree = (i - lowOuterExt + theNumberOfPlayers - 1) / 2;
            i += 2;
        }
        if (currentId == lowOuterExt+1){ // 一个外部节点和一个内部节点对比的情况
            tree[pTree] = thePlayers[currentId] < thePlayers[tree[(lowOuterExt+offset)/2]] ? currentId : tree[(lowOuterExt+offset)/2];
        } else // 外部节点对比
            tree[pTree] = thePlayers[currentId] < thePlayers[currentId-1] ? currentId : currentId-1;

        while (pTree%2 && pTree!=1) { // 有余数，右孩子
            tree[pTree/2] = thePlayers[tree[pTree]] < thePlayers[tree[pTree - 1]] ? tree[pTree] : tree[pTree-1];
            pTree /= 2;
        }
    }
}

template<class T>
int completeWinnerTree<T>::winner() const {
    return tree[1];
}

template<class T>
void completeWinnerTree<T>::rePlay(int thePlayer, T newElement) {
    Player[thePlayer] = newElement;
    int pTree = 0;
    // 找到父节点, 以及一起比赛的外部节点
    if (thePlayer <= lowOuterExt)
        pTree = (thePlayer+offset)/2;
    else  // 倒数第二层外部节点
        pTree = (thePlayer - lowOuterExt + NumberOfPlayers - 1) / 2;

    if (tree[pTree] != thePlayer && Player[tree[pTree]] < thePlayer)  // 之前赢者不是改变的节点, 不会改变当前结果
        return;
    else{ // 可能改变当前结果,要重新比赛
        int anotherPlayer;
        if (lowInnerExt%2!=0 && thePlayer == lowOuterExt + 1)
            anotherPlayer = tree[(lowOuterExt+offset)/2];
        else{
            if(thePlayer%2==0)
                anotherPlayer = thePlayer - 1;
            else
                anotherPlayer = thePlayer + 1;
        }
        tree[pTree] = Player[thePlayer] < Player[anotherPlayer] ? thePlayer : anotherPlayer;
        while (pTree!=1) { // 有余数，右孩子
            if (pTree%2) { // 有余数，右节点
                tree[pTree / 2] = Player[tree[pTree]] < Player[tree[pTree-1]] ? tree[pTree] : tree[pTree-1];
                pTree /= 2;
            } else { // 左节点
                if (pTree == NumberOfPlayers - 1) // 对应右节点是外部节点
                    tree[pTree / 2] = Player[tree[pTree]] < Player[lowOuterExt + 1] ? tree[pTree] : lowOuterExt + 1;
                else // 对应内部节点
                    tree[pTree / 2] = Player[tree[pTree]] < Player[tree[pTree + 1]] ? tree[pTree] : tree[pTree + 1];
                pTree /= 2;
            }
        }
    }
}

template<class T>
void completeWinnerTree<T>::getSort(int *&mySort) {
    mySort = new int[sizeof(Player)];  // 多了一个0元素
    T *backUp = new T[sizeof(Player)];
    std::copy(Player, Player + sizeof(Player), backUp);
    for (int i = 1; i <= NumberOfPlayers; ++i) {
        int num = winner();
        mySort[i] = num;
        Player[num] = INT16_MAX;
        rePlay(num, INT16_MAX);
    }
    initialize(backUp, sizeof(backUp));
}

template<class T>
void completeWinnerTree<T>::initWithRecursion(T *thePlayers, int theNumberOfPlayers) {
    tree = new int[theNumberOfPlayers]; // 内部节点二叉树数组表示
    NumberOfPlayers = theNumberOfPlayers;
    s = 1 << int(log2(theNumberOfPlayers - 1)); // 求2的n次幂
    lowInnerExt = (theNumberOfPlayers - s); // 最底层内部节点个数
    lowOuterExt = 2 * lowInnerExt;  // 最底层外部节点个数
    offset = 2 * s - 1;
    Player = new T[theNumberOfPlayers + 1];
    std::copy(thePlayers, thePlayers + theNumberOfPlayers + 1, Player);
    tree[1] = Recursion(2, 3);

    for (int i = 1; i < theNumberOfPlayers; ++i) {
        std::cout << tree[i] << " ";
    }
}


// 递归实现
// 几种情况分别分析要处理好
// 实现方式一，判断递归中的子节点的子节点是否为内部节点
template<class T>
//int completeWinnerTree<T>::Recursion(int leftNode, int rightNode) {
//    int lLeft, lRight, rLeft, rRight;
//    if (2*leftNode + 1 < NumberOfPlayers){ // 子节点全是内部节点
//        lLeft = 2*leftNode, lRight = lLeft+1; // 在tree中的序号
//        tree[leftNode] = Recursion(lLeft, lRight); // 递归在这里体现
//    } else if (leftNode >= s && leftNode < NumberOfPlayers) { // 最底层节点
//        lLeft = 2*(leftNode-s)+1, lRight=lLeft+1;
//        tree[leftNode] = Player[lLeft] < Player[lRight] ? lLeft : lRight;
//    } else if (leftNode < s && 2 * leftNode > NumberOfPlayers-1){ // leftnode是倒数第二层节点，全是外部节点
//        lLeft = 2*leftNode - (NumberOfPlayers-1) + lowOuterExt; // 2* leftNode - 内部节点数 + 外部最底层节点数
//        lRight = lLeft + 1;
//        tree[leftNode] = Player[lLeft] < Player[lRight] ? lLeft : lRight;
//    } else { // 左边内部节点， 右边外部节点, 这里说的是leftNOde的子节点
//        tree[NumberOfPlayers - 1] = Player[lowOuterExt - 1] < Player[lowOuterExt] ? lowOuterExt - 1 : lowOuterExt;
//        lLeft = tree[NumberOfPlayers - 1], lRight = lowOuterExt + 1;
//        tree[leftNode] = Player[lLeft] < Player[lRight] ? lLeft : lRight;
//    }
//
//    if (2*rightNode + 1 < NumberOfPlayers){ // 全是内部节点
//        rLeft = 2*rightNode, rRight = rLeft+1; // 在tree中的序号
//        tree[rightNode] = Recursion(rLeft, rRight); // 递归在这里体现
//    } else if (rightNode >= s && rightNode < NumberOfPlayers) { // 最底层节点
//        rLeft = 2*(rightNode-s)+1, rRight=rLeft+1;
//        tree[rightNode] = Player[rLeft] < Player[rRight] ? rLeft : rRight;
//    } else if (rightNode < s && 2 * rightNode > NumberOfPlayers-1) { // leftnode是倒数第二层节点，全是外部节点
//        rLeft = 2*rightNode - (NumberOfPlayers-1) + lowOuterExt; // 2* leftNode - 内部节点数 + 外部最底层节点数
//        rRight = rLeft + 1;
//        tree[rightNode] = Player[rLeft] < Player[rRight] ? rLeft : rRight;
//    } else { // 左边内部节点， 右边外部节点, 这里说的是leftNOde的子节点
//        tree[NumberOfPlayers - 1] = Player[lowOuterExt - 1] < Player[lowOuterExt] ? lowOuterExt - 1 : lowOuterExt;
//        rLeft = tree[NumberOfPlayers - 1], rRight = lowOuterExt + 1;
//        tree[rightNode] = Player[rLeft] < Player[rRight] ? rLeft : rRight;
//    }
//
//    return Player[tree[leftNode]] < Player[tree[rightNode]] ? tree[leftNode] : tree[rightNode];
//}

// 实现方法二
// 判断当前字节点是否有效,实现方法更简洁
int completeWinnerTree<T>::Recursion(int leftNode, int rightNode) {
    int left, right;
    if (leftNode < NumberOfPlayers) // 有效内部节点,其他条件下全是外部节点
        left = tree[leftNode] = Recursion(2 * leftNode, 2 * leftNode + 1);
    else if (leftNode > NumberOfPlayers-1 && leftNode < 2 * s) // 倒数第二层外部节点
        left = leftNode-(NumberOfPlayers-1)+lowOuterExt;
    else // 最底层外部节点
        left = ((leftNode/2)-s)*2+1;

    if (rightNode < NumberOfPlayers) // 有效内部节点,其他条件下全是外部节点
        right = tree[rightNode] = Recursion(2 * rightNode, 2 * rightNode + 1);
    else if (rightNode > NumberOfPlayers-1 && rightNode < 2 * s) // 倒数第二层外部节点
        right = rightNode-(NumberOfPlayers-1)+lowOuterExt;
    else // 最底层外部节点,其对应左节点也必是最底层节点
        right = left+1;

    return Player[left] < Player[right] ? left : right;
}


#endif //CHAPTER13_COMPLETEWINNERTREE_H
