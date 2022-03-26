//
// Created by Dell on 2021/6/24.
//

#ifndef CHAPTER13_WINNERTREE_H
#define CHAPTER13_WINNERTREE_H

template<class T>
class winnerTree
{
public:
    virtual ~winnerTree()= default;
    // 从数组中生成赢者树
    virtual void initialize(T *thepalyer, int theNumberOfPlayers) = 0;  // 纯虚函数
    // 返回赢者的索引， 此关键字代表返回值不能被忽略
    [[nodiscard]] virtual int winner() const = 0;
    // 在参赛者thePlayer的分数变化后重赛
    virtual void rePlay(int thePlayer, T newElement) = 0;
};

#endif //CHAPTER13_WINNERTREE_H
