#include <iostream>
#include <algorithm>
#include "arrayList.h"

template <class T>
struct matrixTerm
{
    // data member
    T element;
    unsigned int rowIndex, columnIndex;

    // function
    matrixTerm() {}
    matrixTerm(unsigned int row, unsigned int column, const T& element) 
    {
        this->element=element;
        rowIndex=row;
        columnIndex=column;
    }
    bool operator==(const matrixTerm<T> &m)
    {
        if(element == m.element && rowIndex == m.rowIndex && columnIndex == m.columnIndex)
            return true;
        else
            return false;
    }
};


template <class T>
class sparseMatrix
{
    template <class U>
    friend std::ostream& operator<<(std::ostream &os, sparseMatrix<U> &m);
//    Q42
    template <class U>
    friend std::istream& operator>>(std::istream &is, sparseMatrix<U> &m);
    public:
        sparseMatrix() {}
//        Q43
        sparseMatrix(const sparseMatrix<T>& theMatrix);
        sparseMatrix(int r, int c) {rows = r; columns = c;}
        sparseMatrix<T> transpose();
        sparseMatrix<T> add(sparseMatrix<T> &m);
//        Q41
        T get(int i, int j);
        void set(int i, int j, const T& value);
        void insert(int i, int j, const T& value);
//        Q45
        sparseMatrix<T> multiple(sparseMatrix<T>& theMatrix);
    private:
        int rows, columns; // 矩阵的行数和列数
        // 添加元素通过terms的成员函数实现
        // 非0项数,用ArrayList装下各个单独的矩阵节点结构体,arrayList是连续空间存储
        arrayList<matrixTerm<T>> terms;

};

template <class T>
T sparseMatrix<T>::get(int i, int j)
{
    typename arrayList<matrixTerm<T>>::myIterator it = terms.begin();
    while (it != terms.end())
    {
        if (it->rowIndex == i && it->columnIndex == j)
            return it->element;
        else
            it++;
    }
    return 0;
}

template <class T>
void sparseMatrix<T>::set(int i, int j, const T &value)
{
    typename arrayList<matrixTerm<T>>::myIterator it = terms.begin();
    while (it != terms.end())
    {
        if (it->rowIndex == i && it->columnIndex == j)
        {
            it->element = value;
            return;
        }
        else
            it++;
    }
    if(it == terms.end())
        std::cout << "This element should be 0! " << std::endl;
}

template <class T>
void sparseMatrix<T>::insert(int i, int j, const T &value)
{
    typename arrayList<matrixTerm<T>>::myIterator it = terms.begin();
    matrixTerm<T> item;
    item.rowIndex = i;
    item.columnIndex = j;
    item.element = value;
    int cSize = 0;
    while (it != terms.end())
    {
        if (i*columns+j < it->rowIndex*columns+it->columnIndex)
        {
            terms.insert(cSize, item);
            return;
        }
        else
        {
            cSize++;
            it++;
        }
    }
    // 如果是最后一个就在这里添加
    terms.insert(cSize, item);
}

// 关键是计算转置后的先后顺序
// 统计每一列的数据，然后依次插入就可以了
template <class T>
sparseMatrix<T> sparseMatrix<T>::transpose()
{
    sparseMatrix<T> m;
    m.columns = rows;
    m.rows = columns;
    m.terms.reSet(terms.size());

    // 两个用来计算对应先后位置的数组
    int* colSize = new int[columns+1];
    int* rowNext = new int[columns+1];
    // 搜寻 *this中每一列的项的数目
    for (int i=1;i<=columns;i++)
        colSize[i] = 0;
    for (typename arrayList<matrixTerm<T>>::myIterator it = terms.begin();it != terms.end();it++)
        colSize[it->columnIndex]++; // 对应列数的数量加一

    // 寻找原数组中每一列的数据起始位置，即转置后每一行的起始点（在转置后线性表中的序号）
    rowNext[1] = 0;
    for (int i=2;i<=columns;i++)
        rowNext[i] = rowNext[i-1] + colSize[i-1];

    matrixTerm<T> mTerm;
    for (typename arrayList<matrixTerm<T>>::myIterator it = terms.begin();it != terms.end();it++)
    {
        int j = rowNext[it->columnIndex]++;
        mTerm.columnIndex = it->rowIndex;
        mTerm.rowIndex = it->columnIndex;
        mTerm.element = it->element;
        m.terms.set(j, mTerm);
    }
    return m;
}

template <class T>
sparseMatrix<T> sparseMatrix<T>::add(sparseMatrix<T> &m)
{
    sparseMatrix<T> matrixItem;
    if (rows != m.rows || columns != m.columns)
    {
        std::cout << "the shape of two matrix is different! " << std::endl;
        return matrixItem;
    }

    matrixItem.rows = rows;
    matrixItem.columns = columns;

    int cSize = 0;
    typename arrayList<matrixTerm<T>>::myIterator thisIterator = terms.begin();
    typename arrayList<matrixTerm<T>>::myIterator thisEnd = terms.end();
    typename arrayList<matrixTerm<T>>::myIterator mIterator = m.terms.begin();
    typename arrayList<matrixTerm<T>>::myIterator mEnd = m.terms.end();

    // 当有一个到达End时就必须退出了，因为他没有数据了，没法进行接下来的判断
    while (thisIterator != thisEnd && mIterator != mEnd)
    {
        int thisIndex = thisIterator->rowIndex * columns + thisIterator->columnIndex;
        int mIndex = mIterator->rowIndex * columns + mIterator->columnIndex;
        if (thisIndex < mIndex)
        {
            matrixItem.terms.insert(cSize, *thisIterator);
            cSize++;
            thisIterator++;
        }
        else if (thisIndex == mIndex)
        {
            // 仅当相加和不为零时才加入到线性表中
            if (thisIterator->element + mIterator->element != 0)
            {
                matrixTerm<T> mTerm;
                mTerm.rowIndex = thisIterator->rowIndex;
                mTerm.columnIndex = thisIterator->columnIndex;
                mTerm.element = thisIterator->element + mIterator->element;
                matrixItem.terms.insert(cSize, mTerm);
            }
            cSize++;
            thisIterator++;
            mIterator++;
        }
        else
        {
            matrixItem.terms.insert(cSize, *mIterator);
            cSize++;
            mIterator++;
        }
    }
    for(;thisIterator != thisEnd; thisIterator++)
        matrixItem.terms.insert(cSize++, *thisIterator);
    for(;mIterator != mEnd; mIterator++)
        matrixItem.terms.insert(cSize++, *mIterator);
    return matrixItem;
}

template <class T>
std::ostream& operator<<(std::ostream &os, sparseMatrix<T> &m)
{
    os << "rows = " << m.rows << " columns = " << m.columns << std::endl;
    os << "nonzero terms = " << m.terms.size() << std::endl;
    // 将非零元素逐个输出
    for (typename arrayList<matrixTerm<T>>::myIterator it = m.terms.begin();it != m.terms.end();it++)
        os << "a(" << it->rowIndex << "," << it->columnIndex << ") = " << it->element << std::endl;
    return os;
}

template <class T>
std::istream& operator>>(std::istream &is, sparseMatrix<T> &m)
{
    int numberOfTerms;
    std::cout << "Enter number of rows, columns, and number of terms. " << std::endl;
    is >> m.rows >> m.columns >> numberOfTerms;

    // 重新设置m.terms 的大小，用以重新填充数据
    matrixTerm<T> mTerm;
    std::cout << "Please input from left to right, from up to down." << std::endl;
    for(int i=0; i<numberOfTerms;)
    {
        std::cout << "Enter row, colunm and value of term " << i+1 << std::endl;
        is >> mTerm.rowIndex >> mTerm.columnIndex >> mTerm.element;
        if (mTerm.rowIndex>m.rows||mTerm.rowIndex<1||mTerm.columnIndex>m.columns||mTerm.columnIndex<1)
        {
            std::cout << "The Index is out of range!" << std::endl;
            continue;
        }
        else if(mTerm.element == 0)
        {
            std::cout << "The element = 0, shouldn't be insert in the matrix!" << std::endl;
            continue;
        }
        m.terms.insert(i, mTerm);
        i++;
    }
    return is;
}

template<class T>
sparseMatrix<T>::sparseMatrix(const sparseMatrix<T> &theMatrix)
{
    rows = theMatrix.rows;
    columns = theMatrix.columns;
    terms = theMatrix.terms;
}

template<class T>
sparseMatrix<T> sparseMatrix<T>::multiple(sparseMatrix<T> &theMatrix)
{
    sparseMatrix<T> mItem(rows, theMatrix.columns), transMatrix = theMatrix.transpose(); // 转置后相乘更方便
    typename arrayList<matrixTerm<T>>::myIterator it = terms.begin();
    typename arrayList<matrixTerm<T>>::myIterator itEnd = terms.end();
    typename arrayList<matrixTerm<T>>::myIterator mt = transMatrix.terms.begin(), mtNow = mt;
    typename arrayList<matrixTerm<T>>::myIterator mtEnd = transMatrix.terms.end();

    // 将两个矩阵的每一行都分别描述
    arrayList<matrixTerm<T>> *thisBullet, *transBullet;
    thisBullet = new arrayList<matrixTerm<T>> [rows+1];
    transBullet = new arrayList<matrixTerm<T>> [transMatrix.rows+1];
    for (;it!=itEnd;it++)
        thisBullet[it->rowIndex].push_back(*it);
    for (;mt!=mtEnd;mt++)
        transBullet[mt->rowIndex].push_back(*mt);
    for (int i=1;i<rows+1;i++) // 遍历左乘矩阵的每一行
    {
        for (int j=1;j<transMatrix.rows+1;j++) // 遍历右乘矩阵的每一列
        {
            T sum = 0;
            typename arrayList<matrixTerm<T>>::myIterator thisH = thisBullet[i].begin();
            typename arrayList<matrixTerm<T>>::myIterator thisEnd = thisBullet[i].end();
            typename arrayList<matrixTerm<T>>::myIterator transH = transBullet[j].begin();
            typename arrayList<matrixTerm<T>>::myIterator transEnd = transBullet[j].end();
            while (thisH != thisEnd && transH != transEnd)
            {
                if (thisH->columnIndex == transH->columnIndex)
                {
                    sum = sum + thisH->element * transH->element;
                    thisH++;transH++;
                }
                else if (thisH->columnIndex < transH->columnIndex)
                    thisH++;
                else
                    transH++;
            }
            mItem.insert(i,j,sum);
        }
    }
    return mItem;
}
