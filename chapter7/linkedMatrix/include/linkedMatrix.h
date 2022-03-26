#ifndef MAIN_LINKEDMATRIX_H
#define MAIN_LINKEDMATRIX_H
#include "extendedChain.h"
#include "printError.h"

// 这两个结构体要重载一些运算符才能符合extendedChain类的数据要求
template <class T>
struct rowElement
{
    int col;
    T value;

    rowElement() {}
    bool operator==(const rowElement<T>& r) const {return (col == r.col && r.value == value);}
    bool operator!=(const rowElement<T>& r) const {return !((*this)==r);}
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const rowElement<U>& r);
};

template <class U>
std::ostream& operator<<(std::ostream& out, const rowElement<U>& r)
{
    out << "col: " << r.col << " value: " << r.value <<std::endl;
    return out;
}

template <class T>
struct headerElement
{
    int row;
    extendedChain<rowElement<T>> rowChain;

    headerElement() {};
    bool operator==(const headerElement<T>& h) const {return (row == h.row && rowChain == h.rowChain);}
    bool operator!=(const headerElement<T>& h) const {return !((*this)==h);}
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const headerElement<U>& h);
};
template <class U>
std::ostream& operator<<(std::ostream& out, const headerElement<U>& h)
{
    out << "row: " << h.row << " " << h.rowChain << std::endl;
    return out;
}


template <class T>
class linkedMatrix
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const linkedMatrix<U>& m);
public:
    linkedMatrix(int rows, int columns) {totalRows = rows; totalCols = columns;}
    linkedMatrix<T> transpose();
//    Q51(3)
    linkedMatrix<T> add(linkedMatrix<T> &m);
//    Q51(2)
    T get(int i, int j);
    void set(int i, int j, const T& value);
//    Q51(1)
    void insert(int i, int j, const T& value);
//    Q51(4)
    linkedMatrix<T> minus(linkedMatrix<T> &m);
//    Q51(5)
    linkedMatrix<T> multiple(linkedMatrix<T> &m);
    bool isEmpty() const;
private:
    int totalRows, totalCols;
    extendedChain<headerElement<T>> headerChain;
};

template<class T>
T linkedMatrix<T>::get(int i, int j)
{

    if (i > totalRows || i < 1 || j > totalCols || j < 1)
        std::cout <<"The index is out of range!" << std::endl;

    typename extendedChain<headerElement<T>>::myIterator ih = headerChain.begin();
    typename extendedChain<headerElement<T>>::myIterator ihEnd = headerChain.end();
    for (; ih != ihEnd && i >= ih->row; ih++) {
        if (i == ih->row)
        {
            typename extendedChain<rowElement<T>>::myIterator ir = ih->rowChain.begin();
            typename extendedChain<rowElement<T>>::myIterator irEnd = ih->rowChain.end();
            for (; ir != irEnd && j >= ir->col; ir++)
            {
                if (j == ir->col)
                    return ir->value;
            }
        }
    }
    return 0;

}

template<class T>
void linkedMatrix<T>::set(int i, int j, const T &value)
{
    if(i>totalRows||i<1||j>totalCols||j<1)
    {
        std::cout << "The index is out of range!" << std::endl;
        return;
    }
    typename extendedChain<headerElement<T>>::myIterator ih = headerChain.begin();
    typename extendedChain<headerElement<T>>::myIterator ihEnd = headerChain.end();
    for (;ih!=ihEnd && i>=ih->row;ih++)
    {
        if(i == ih->row)
        {
            typename extendedChain<rowElement<T>>::myIterator ir = ih->rowChain.begin();
            typename extendedChain<rowElement<T>>::myIterator irEnd = ih->rowChain.end();
            for(;ir!=irEnd && j>=ir->col;ir++)
            {
                if(j == ir->col)
                {
                    ir->value = value;
                    return;
                }
            }
        }
    }
    std::cout << "The element a(" << i << "," << j << ") should be zero, couldn't set to be " << value << std::endl;
}

template<class T>
void linkedMatrix<T>::insert(int i, int j, const T &value)
{
    int headerCount = 0, rowCount = 0;
    if(i>totalRows||i<1||j>totalCols||j<1)
    {
        std::cout << "The index is out of range!" <<std::endl;
        return;
    }
    else if(value==0)
    {
        std::cout << "The insert value should be zero!" << std::endl;
        return;
    }
    typename extendedChain<headerElement<T>>::myIterator ih = headerChain.begin(), ihHeader = ih;
    typename extendedChain<headerElement<T>>::myIterator ihEnd = headerChain.end();
    for (;ih!=ihEnd && i>=ih->row;ih++)
    {
        headerCount++;
        rowCount=0;
        if(i == ih->row) // 当前元素所在行不为空
        {
            typename extendedChain<rowElement<T>>::myIterator ir = ih->rowChain.begin(), irHeader = ir;
            typename extendedChain<rowElement<T>>::myIterator irEnd = ih->rowChain.end();
            for(;ir!=irEnd && j>=ir->col;ir++)
            {
                rowCount++;
                if(j == ir->col) // 插入的元素已经存在
                {
                    std::cout << "The element already exist, can't be insert!" << std::endl;
                    return;
                }
            }
            rowElement<T> rowItem;
            rowItem.col = j; rowItem.value = value;
            ih->rowChain.insert(rowCount, rowItem);
            return;
        }
    }
    rowElement<T> rowItem;
    headerElement<T> headerItem;
    rowItem.col = j;rowItem.value = value;
    headerItem.row = i;
    headerItem.rowChain.push_back(rowItem);
    headerChain.insert(headerCount, headerItem);
}

template<class T>
bool linkedMatrix<T>::isEmpty() const
{
    if(headerChain.size() == 0)
        return true;
    else
        return false;
}

template <class U>
std::ostream& operator<<(std::ostream& os, const linkedMatrix<U>& m)
{
    typename extendedChain<headerElement<U>>::myIterator ih = m.headerChain.begin(), ihHeader = ih;
    typename extendedChain<headerElement<U>>::myIterator ihEnd = m.headerChain.end();
    for (;ih!=ihEnd;ih++)
    {
        typename extendedChain<rowElement<U>>::myIterator ir = ih->rowChain.begin(), irHeader = ir;
        typename extendedChain<rowElement<U>>::myIterator irEnd = ih->rowChain.end();
        for(;ir!=irEnd;ir++)
            os << "a(" << ih->row << "," << ir->col << ") = " << ir->value << std::endl;
    }
    if (m.isEmpty())
        os << "All element is zero" << std::endl;
    return os;
}

template<class T>
linkedMatrix<T> linkedMatrix<T>::transpose()
{
    linkedMatrix<T> mItem(totalCols, totalRows);
    typename extendedChain<headerElement<T>>::myIterator ih = headerChain.begin();
    typename extendedChain<headerElement<T>>::myIterator ihEnd = headerChain.end();

    // 包含行列表的数组
    extendedChain<rowElement<T>> *bin;
    bin = new extendedChain<rowElement<T>> [totalCols+1];
    for (;ih!=ihEnd;ih++)
    {
        typename extendedChain<rowElement<T>>::myIterator ir = ih->rowChain.begin();
        typename extendedChain<rowElement<T>>::myIterator irEnd = ih->rowChain.end();
        rowElement<T> x;
        x.col = ih->row;
        for (;ir!=irEnd;ir++)
        {
            x.value = ir->value;
            bin[ir->col].push_back(x);
        }
    }

    headerElement<T> h;
    for(int i=1;i<totalCols+1;i++)
    {
        if(!bin[i].empty())
        {
            h.row = i;
            h.rowChain = bin[i];
            mItem.headerChain.push_back(h);
        }
    }
    delete [] bin;
    return mItem;
}

template<class T>
linkedMatrix<T> linkedMatrix<T>::add(linkedMatrix<T> &m)
{
    if (totalRows!=m.totalRows || totalCols!=m.totalCols)
    {
        std::cout << "The shape of two matrixex is different!" << std::endl;
        return linkedMatrix<T>(0,0);
    }
    linkedMatrix<T> mItem(totalRows, totalCols);
    typename extendedChain<headerElement<T>>::myIterator ih = headerChain.begin();
    typename extendedChain<headerElement<T>>::myIterator ihEnd = headerChain.end();
    typename extendedChain<headerElement<T>>::myIterator mh = m.headerChain.begin();
    typename extendedChain<headerElement<T>>::myIterator mhEnd = m.headerChain.end();

    while (ih != ihEnd && mh != mhEnd)
    {
        headerElement<T> headerItem;
        int ir = ih->row, mr = mh->row;
        extendedChain<rowElement<T>> iChain = ih->rowChain, mChain = mh->rowChain;
        typename extendedChain<rowElement<T>>::myIterator iRowH = iChain.begin();
        typename extendedChain<rowElement<T>>::myIterator iRowHEnd = iChain.end();
        typename extendedChain<rowElement<T>>::myIterator mRowH = mChain.begin();
        typename extendedChain<rowElement<T>>::myIterator mRowHEnd = mChain.end();
        if (ir < mr)
        {
            headerItem.row = ir;
            for (;iRowH!=iRowHEnd;iRowH++)
                headerItem.rowChain.push_back(*iRowH);
            ih++;
        }
        else if(ir > mr)
        {
            headerItem.row = mr;
            for (;mRowH!=mRowHEnd;mRowH++)
                headerItem.rowChain.push_back(*mRowH);
            mh++;
        }
        else // 同一行
        {
            rowElement<T> rowItem;
            headerItem.row = ir;
            while (iRowH!=iRowHEnd && mRowH!=mRowHEnd)
            {

                int ic = iRowH->col, mc = mRowH->col;
                if (ic < mc)
                {
                    rowItem.col = ic;
                    rowItem.value = iRowH->value;
                    iRowH++;
                }
                else if(ic > mc)
                {
                    rowItem.col = mc;
                    rowItem.value = mRowH->value;
                    mRowH++;
                }
                else
                {
                    rowItem.col = ic;
                    rowItem.value = iRowH->value + mRowH->value;
                    iRowH++, mRowH++;
                }
                headerItem.rowChain.push_back(rowItem);
            }
            for (;iRowH!=iRowHEnd;iRowH++)
            {
                rowItem.col = iRowH->col;
                rowItem.value = iRowH->value;
                headerItem.rowChain.push_back(rowItem);
            }
            for(;mRowH!=mRowHEnd;mRowH++)
            {
                rowItem.col = mRowH->col;
                rowItem.value = mRowH->value;
                headerItem.rowChain.push_back(rowItem);
            }
            ih++,mh++;
        }
        mItem.headerChain.push_back(headerItem);
    }
    for (;ih!=ihEnd;ih++)
    {
        extendedChain<rowElement<T>> iChain = ih->rowChain;
        typename extendedChain<rowElement<T>>::myIterator iRowH = iChain.begin();
        typename extendedChain<rowElement<T>>::myIterator iRowHEnd = iChain.end();
        headerElement<T> headerItem;
        headerItem.row = ih->row;
        for (;iRowH!=iRowHEnd;iRowH++)
            headerItem.rowChain.push_back(*iRowH);
        mItem.headerChain.push_back(headerItem);
    }
    for (;mh!=mhEnd;mh++)
    {
        extendedChain<rowElement<T>> mChain = mh->rowChain;
        typename extendedChain<rowElement<T>>::myIterator mRowH = mChain.begin();
        typename extendedChain<rowElement<T>>::myIterator mRowHEnd = mChain.end();
        headerElement<T> headerItem;
        headerItem.row = mh->row;
        for (;mRowH!=mRowHEnd;mRowH++)
            headerItem.rowChain.push_back(*mRowH);
        mItem.headerChain.push_back((headerItem));
    }
    return mItem;
}

template<class T>
linkedMatrix<T> linkedMatrix<T>::minus(linkedMatrix<T> &m)
{
    if (totalRows!=m.totalRows || totalCols!=m.totalCols)
    {
        std::cout << "The shape of two matrixex is different!" << std::endl;
        return linkedMatrix<T>(0,0);
    }
    linkedMatrix<T> mItem(totalRows, totalCols);
    rowElement<T> rowItem;
    typename extendedChain<headerElement<T>>::myIterator ih = headerChain.begin();
    typename extendedChain<headerElement<T>>::myIterator ihEnd = headerChain.end();
    typename extendedChain<headerElement<T>>::myIterator mh = m.headerChain.begin();
    typename extendedChain<headerElement<T>>::myIterator mhEnd = m.headerChain.end();

    while (ih != ihEnd && mh != mhEnd)
    {
        headerElement<T> headerItem;
        int ir = ih->row, mr = mh->row;
        extendedChain<rowElement<T>> iChain = ih->rowChain, mChain = mh->rowChain;
        typename extendedChain<rowElement<T>>::myIterator iRowH = iChain.begin();
        typename extendedChain<rowElement<T>>::myIterator iRowHEnd = iChain.end();
        typename extendedChain<rowElement<T>>::myIterator mRowH = mChain.begin();
        typename extendedChain<rowElement<T>>::myIterator mRowHEnd = mChain.end();
        if (ir < mr)
        {
            headerItem.row = ir;
            for (;iRowH!=iRowHEnd;iRowH++)
                headerItem.rowChain.push_back(*iRowH);
            ih++;
        }
        else if(ir > mr)
        {
            headerItem.row = mr;
            for (;mRowH!=mRowHEnd;mRowH++)
            {
                rowItem.col = mRowH->col;
                rowItem.value = -mRowH->value;
                headerItem.rowChain.push_back(rowItem);
            }
            mh++;
        }
        else // 同一行
        {
//            rowElement<T> rowItem;
            headerItem.row = ir;
            while (iRowH!=iRowHEnd && mRowH!=mRowHEnd)
            {

                int ic = iRowH->col, mc = mRowH->col;
                if (ic < mc)
                {
                    rowItem.col = ic;
                    rowItem.value = iRowH->value;
                    iRowH++;
                }
                else if(ic > mc)
                {
                    rowItem.col = mc;
                    rowItem.value = -mRowH->value;
                    mRowH++;
                }
                else
                {
                    rowItem.col = ic;
                    rowItem.value = iRowH->value - mRowH->value;
                    iRowH++, mRowH++;
                }
                headerItem.rowChain.push_back(rowItem);
            }
            for (;iRowH!=iRowHEnd;iRowH++)
            {
                rowItem.col = iRowH->col;
                rowItem.value = iRowH->value;
                headerItem.rowChain.push_back(rowItem);
            }
            for(;mRowH!=mRowHEnd;mRowH++)
            {
                rowItem.col = mRowH->col;
                rowItem.value = -mRowH->value;
                headerItem.rowChain.push_back(rowItem);
            }
            ih++,mh++;
        }
        mItem.headerChain.push_back(headerItem);
    }
    for (;ih!=ihEnd;ih++)
    {
        extendedChain<rowElement<T>> iChain = ih->rowChain;
        typename extendedChain<rowElement<T>>::myIterator iRowH = iChain.begin();
        typename extendedChain<rowElement<T>>::myIterator iRowHEnd = iChain.end();
        headerElement<T> headerItem;
        headerItem.row = ih->row;
        for (;iRowH!=iRowHEnd;iRowH++)
            headerItem.rowChain.push_back(*iRowH);
        mItem.headerChain.push_back(headerItem);
    }
    for (;mh!=mhEnd;mh++)
    {
        extendedChain<rowElement<T>> mChain = mh->rowChain;
        typename extendedChain<rowElement<T>>::myIterator mRowH = mChain.begin();
        typename extendedChain<rowElement<T>>::myIterator mRowHEnd = mChain.end();
        headerElement<T> headerItem;
        headerItem.row = mh->row;
        for (;mRowH!=mRowHEnd;mRowH++)
        {
            rowItem.col = mRowH->col;
            rowItem.value = -mRowH->value;
            headerItem.rowChain.push_back(rowItem);
        }
        mItem.headerChain.push_back((headerItem));
    }
    return mItem;
}

template<class T>
linkedMatrix<T> linkedMatrix<T>::multiple(linkedMatrix<T> &m)
{
    if (totalCols!=m.totalRows)
    {
        std::cout << "THe column of first matrix and row of second matrix are different!" << std::endl;
        return linkedMatrix<T>(0, 0);
    }
    linkedMatrix<T> mItem(totalRows, m.totalCols), transMatrix(m.totalCols, m.totalRows);
    transMatrix = m.transpose();
    if (isEmpty() || m.isEmpty()) // 如果有一个矩阵全为0，可以直接返回
        return mItem;
    // 转置之后可以很方便的访问原来的第二个矩阵的列，即转置后第二个矩阵的行
    typename extendedChain<headerElement<T>>::myIterator ih = headerChain.begin();
    typename extendedChain<headerElement<T>>::myIterator ihEnd = headerChain.end();
    while (ih!=ihEnd)
    {
        int Ir=0,Ic=0;
        typename extendedChain<headerElement<T>>::myIterator mh = transMatrix.headerChain.begin();
        typename extendedChain<headerElement<T>>::myIterator mhEnd = transMatrix.headerChain.end();
        while (mh!=mhEnd)
        {
            Ir = ih->row, Ic = mh->row;
            T sum=0;
            typename extendedChain<rowElement<T>>::myIterator iRowH = ih->rowChain.begin();
            typename extendedChain<rowElement<T>>::myIterator iRowEnd = ih->rowChain.end();
            typename extendedChain<rowElement<T>>::myIterator mRowH = mh->rowChain.begin();
            typename extendedChain<rowElement<T>>::myIterator mRowEnd = mh->rowChain.end();
            while (iRowH!=iRowEnd && mRowH!=mRowEnd)
            {
                if (iRowH->col == mRowH->col)
                {
                    sum = sum + iRowH->value * mRowH->value;
                    iRowH++;mRowH++;
                }
                else if (iRowH->col < mRowH->col)
                    iRowH++;
                else
                    mRowH++;
            }
            mh++;
            mItem.insert(Ir, Ic, sum);
        }
        ih++;
    }
    return mItem;
}



#endif //MAIN_LINKEDMATRIX_H
