#include <iostream>
#include <algorithm>


template<class T>
class matrix
{
    template <class U>
    friend std::ostream& operator<<(std::ostream&, const matrix<U>&);
    template <class U>
    friend std::istream& operator>>(std::istream&, const matrix<U>&);
    public:
        matrix(int theRows = 0, int theColumns = 0);
        matrix(const matrix<T>&);
        ~matrix() {delete [] elements;}

        int rows() const {return theRows;}
        int columns() const {return theColumns;}
        T& operator()(int i, int j) const;
        matrix<T>& operator=(const matrix<T>&);
        matrix<T> operator+() const;
        matrix<T> operator+(const matrix<T>&) const;
        matrix<T> operator-() const;
        matrix<T> operator-(const matrix<T>&) const;
        matrix<T> operator*(const matrix<T>&) const;
        matrix<T>& operator+=(const T&);
        matrix<T>& operator-=(const T&);
        matrix<T>& operator*=(const T&);
        matrix<T>& operator/=(const T&);
        matrix<T> reverse();
    private:
        int theRows, theColumns;  // 矩阵的行数和列数
        T *elements;
};


template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
    if(theRows<0 || theColumns<0)
    {
        std::cout << "theRows or theColumns shouldn't be smaller than 0"<<std::endl;
        return;
    }
    if((theRows==0 || theColumns==0) && (theRows!=0 || theColumns!=0))
    {
        std::cout << "Either theRows or theColumns shouldn't be 0"<<std::endl;
        return;
    }

    // 创建矩阵
    this->theRows = theRows;
    this->theColumns = theColumns;
    elements = new T [theRows * theColumns];
    // 将初始化后的矩阵直接化为0
    for(int i=0;i<theRows;i++)
    {
        for(int j=0;j<theColumns;j++)
            elements[i*theColumns+j]=0;
    }
}

// copy constructor
template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
    theRows = m.rows();
    theColumns = m.columns();
    elements = new T [theColumns * theRows];

    // copy the element
    std::copy(m.elements, m.elements+m.rows()*m.columns(), elements);
}

// 赋值运算符
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
    // 不能自己给自己赋值
    if(this != &m)
    {
        delete [] elements;
        theRows = m.rows();
        theColumns = m.columns();
        elements = new T [theColumns * theRows];
        std::copy(m.elements, m.elements+m.rows()*m.columns(), elements);
    }
    return *this;
}

// 矩阵的索引从（1，1）开始.
// 返回的是索引，可以用于修改值.
template<class T>
T& matrix<T>::operator()(int i, int j) const
{
    if(i>theRows || i<1 || j>theColumns || j<1)
    {
        std::cout << "index out of range." << std::endl;
        return elements[0];
    }
    return elements[(i-1)*theColumns + j-1];
}

template<class T>
matrix<T> matrix<T>::operator+() const
{
    return *this;
}

//非自加，返回第三方.
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
    if(theRows != m.theRows || theColumns != m.theColumns)
    {
        std::cout << "The shape of two matrix is not same." << std::endl;
        return *this;
    }
    matrix<T> addMatrix(theRows, theColumns);
    for(int i=0;i<theColumns*theRows;i++)
        addMatrix.elements[i] = elements[i] + m.elements[i];
    return addMatrix;
}

template<class T>
matrix<T> matrix<T>::operator-() const
{
    matrix<T> w(theRows, theColumns);
    for(int i=1;i<=theRows;i++)
    {
        for(int j=1;j<=theColumns;j++)
        {
            w(i,j)=-(*this)(i,j);
        }
    }
    return w;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{
    matrix<T> w(theRows, theColumns);
    for(int i=1;i<=theRows;i++)
    {
        for(int j=1;j<=theColumns;j++)
        {
            w(i,j)=(*this)(i,j) - m(i,j);
        }
    }
    return w;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{
    if(theColumns!=m.theRows)
    {
        std::cout << "The shape of two matrix is not same." << std::endl;
        return *this;
    }

    matrix<T> w(theRows, m.theColumns);
    // 矩阵的索引都从1开始，和数组不同.
    for(int i=1;i<=theRows;i++)
    {
        for(int j=1;j<=m.theColumns;j++)
        {
            for(int k=1;k<=theColumns;k++)
            {
                w(i,j) += (*this)(i,k)*m(k,j);
            }
        }
    }
    return w;
}

template<class T>
matrix<T>& matrix<T>::operator+=(const T& m)
{
    for(int i=1;i<=theRows;i++)
    {
        for(int j=1;j<=theColumns;j++)
        {
            (*this)(i,j) += m;
        }
    }
    return (*this);
}

template<class T>
matrix<T>& matrix<T>::operator-=(const T& m)
{
    for(int i=1;i<=theRows;i++)
    {
        for(int j=1;j<=theColumns;j++)
        {
            (*this)(i,j) -= m;
        }
    }
    return (*this);
}

template<class T>
matrix<T>& matrix<T>::operator*=(const T& m)
{
    for(int i=1;i<=theRows;i++)
    {
        for(int j=1;j<=theColumns;j++)
        {
            (*this)(i,j) *= m;
        }
    }
    return (*this);
}

template<class T>
matrix<T>& matrix<T>::operator/=(const T& m)
{
    if(m!=0)
    {
        for(int i=1;i<=theRows;i++)
        {
            for(int j=1;j<=theColumns;j++)
            {
                (*this)(i,j) /= m;
            }
        }
    }
    return (*this);
}

template<class T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& m)
{
    if(m.theRows!=0)
    {
        for(int i=1;i<=m.theRows;i++)
        {
            for(int j=1;j<=m.theColumns;j++)
                os << m(i,j) <<" ";
            os << std::endl;
        }
    }
    return os;
}

template <class U>
std::istream& operator>>(std::istream& is, const matrix<U>& m)
{
    std::cout << "the rows: " << m.rows() << "  " << "the columns: " << m.columns() << std::endl;
    U num;
    int i=1,j=1;
    while(is >> num)
    {
        m(i,j) = num;
        if(i == m.rows() && j == m.columns())
            break;
        j++;
        if(j == m.columns()+1)
        {
            i++;
            j=1;
        }
    }
    return is;
}

template<class T>
matrix<T> matrix<T>::reverse()
{
    matrix<T> w(theColumns, theRows);
    for(int i=1;i<=theRows;i++)
    {
        for(int j=1;j<=theColumns;j++)
            w(j,i) = (*this)(i,j);
    }
    return w;
}