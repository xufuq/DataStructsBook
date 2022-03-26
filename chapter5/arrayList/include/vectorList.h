#include <vector>
#include "linearList.h"
#include <algorithm>
// #include <iterator>

template <class T>
class vectorList : public linearList<T>
{
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const vectorList<U>& x);
public:
    vectorList(int initialCapacity = 10);
    vectorList(const vectorList<T>&);
    ~vectorList() {delete element;}

    bool empty() const {return element->empty();} // 调用STL库的方法
    int size() const {return (int) element->size();}  // STL
    T& get(int theIndex) const override;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream &out) const;
    int capacity() const {return (int) element->capacity();}  // 返回实际开拓的内存的大小
    void clear() {element->clear();}
    void push_back(const T& a) {element->push_back(a);}

    typedef typename std::vector<T>::iterator iterator;
    iterator begin() {return element->begin();}
    iterator end() {return element->end();}

    void half();
    void meld(vectorList<T>& a, vectorList<T>& b);
    void merge(vectorList<T>& a, vectorList<T>& b);
    void split(vectorList<T>& a, vectorList<T>& b);

protected:
    void checkIndex(int theIndex) const;
    std::vector<T>* element; // 现在只有一个名字，真正的内存空间需要通过new去创建
    int InitialCapacity;
};

template <class T>
vectorList<T>::vectorList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        // throw s.str();
    }
    InitialCapacity = initialCapacity;
    element = new std::vector<T>; // 创建容量为0的vector
    element->reserve(InitialCapacity);
    // 内存空间由STL的vector自动管理，不用在担心内存释放和分配的问题
}

template <class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{
    element = new std::vector<T>(*theList.element);
    InitialCapacity = theList.capacity();
}

template <class T>
void vectorList<T>::output(std::ostream &out) const
{
    std::copy(element->begin(), element->end(), std::ostream_iterator<T>(out, "  "));
}

template <class T>
std::ostream& operator<<(std::ostream& out, const vectorList<T>& x)
{
    x.output(out);
    return out;
}

template <class T>
T& vectorList<T>::get(int theIndex) const
{
    return *(element->begin()+theIndex);
}

template <class T>
int vectorList<T>::indexOf(const T& theElement) const
{
    iterator ElementPoint = std::find(element->begin(), element->end(),theElement);
    if(ElementPoint!=element->end())
        return (int)(ElementPoint - element->begin());
    else
        return -1;
}

template <class T>
void vectorList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    element->erase(element->begin()+theIndex);
}

template <class T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{
    checkIndex(theIndex);
    element->insert(element->begin() + theIndex, theElement);
}

template <class T>
void vectorList<T>::checkIndex(int theIndex) const
{
    if(theIndex < 0 || theIndex >= element->capacity())
    {
        std::ostringstream s;
        s << "index= "<< theIndex << " size = " << size();
        // throw s.str();
    }
}

template <class T>
void vectorList<T>::half()
{
    int extraSize = size()%2;
    for(iterator p=end()-1-extraSize;p>begin();p-=2)
        element->erase(p);
}

template <class T>
void vectorList<T>::meld(vectorList<T>& a, vectorList<T>& b)
{
    element->clear();
    iterator aPoint = a.begin(), bPoint = b.begin();
    for(;aPoint<a.end();aPoint++)
    {
        element->push_back(*aPoint);
        if(bPoint < b.end())
        {
            element->push_back(*bPoint);
            bPoint++;
        }
    }
    for(;bPoint<b.end();bPoint++)
        element->push_back(*bPoint);
}

template <class T>
void vectorList<T>::merge(vectorList<T>& a, vectorList<T>& b)
{
    int aCount=0, bCount=0;
    iterator aPoint = a.begin(), bPoint = b.begin();
    element->clear();
    for(int i=0;i<a.size()+b.size();i++)
    {
        if(aPoint==a.end())
        {
            element->push_back(*bPoint);
            bPoint++;
        }
        else if(bPoint == b.end())
        {
            element->push_back(*aPoint);
            aPoint++;
        }
        else if(*aPoint<*bPoint)
        {
            element->push_back(*aPoint);
            aPoint++;
        }
        else
        {
            element->push_back(*bPoint);
            bPoint++;
        }
    }
}

template <class T>
void vectorList<T>::split(vectorList<T>& a, vectorList<T>& b)
{
    a.clear(), b.clear();
    for(iterator i=begin();i<end();)
    {
        a.push_back(*i++);
        if(i == end()) break;
        b.push_back(*i++);
    }
}