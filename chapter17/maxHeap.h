//
// Created by Dell on 2021/6/18.
//

#ifndef CHAPTER12_MAXHEAP_H
#define CHAPTER12_MAXHEAP_H

#include "iostream"

template <class T>
void changeLength1D(T* &a, int oldLength, int newLength)
{
    if(newLength < 0)
    {
        std::cout << "The new Length must bigger than 0"<<std::endl;
        return;
    }
    // 生成一个新的数组指针
    T* temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a+number, temp);
    delete [] a;
    a = temp;
}


template<class T>
class maxHeap
{
public:
    template<class U>
    friend std::ostream& operator << (std::ostream& os, maxHeap<U>&);
    maxHeap(){
        heap=0;
        arrayLength=10;
        heap=new T[arrayLength];
    }
    [[nodiscard]] bool empty() const;
    [[nodiscard]] int size() const;
    T top() const;
    void pop();
    void push(const T& theElement);
    void initialize(T* theHeap, int theSize);
    T& getElement(int index) const; // 用于调试
    // Q11
    maxHeap(maxHeap<T>&);
    // Q12n
    void changeMax(T theElement);
    // Q13
    void remove(int i);

private:
    T* heap;
    int arrayLength{}, heapSize{}; //heapSize最少要比arrayLength小1，因为heap[0]不用

};

template<class T>
bool maxHeap<T>::empty() const {
    return heapSize <= 0;
}

template<class T>
int maxHeap<T>::size() const {
    return heapSize;
}

template<class T>
T maxHeap<T>::top() const {
    if (!empty())
        return heap[1];
    else
        return nullptr;
}

template<class T>
void maxHeap<T>::pop() {
    if (empty())
        std::cout << "the heap is empty!" << std::endl;
    else{
        heap[1].~T(); // 删除最大元素。因为已经是有序排列了
        T lastElement = heap[heapSize--]; // 已经变成了目标长度，只需要在给最后一个元素找一个位置
        // 从根开始寻找合适的位置放置
        int currentIndex = 1, childIndex = 2; // 根节点的第一个子节点序号为2

        // 当前判断的是childIndex的值，函数中需要替换的是当前父节点的值
        // 因为在pop之前是已经有了一定顺序的，所以可以从根节点这样做
        while (childIndex <= heapSize){ // 当前遍历的子节点没有超出数据范围
            if (childIndex < heapSize && heap[childIndex] < heap[childIndex+1]) // 找到当前两个子节点中较大的进行判断
                ++childIndex;
            if (lastElement > heap[childIndex]) // 当前就是合适的位置
                break;

            // 当前位置不合适，继续向叶节点寻找
            heap[currentIndex] = heap[childIndex];
            currentIndex = childIndex;
            childIndex *= 2; // 如果*2之后大于heapsize，则证明当前叶子节点没有再下一层的节点，所以直接放在这里就可以
        }
        heap[currentIndex] = lastElement;
    }
}

template<class T>
void maxHeap<T>::push(const T &theElement) {
    if (heapSize==arrayLength-1){ //当前数组已满
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    int currentIndex = ++heapSize; //从最后一个往回追溯，看插到那里合适
    while (currentIndex != 1 && heap[currentIndex/2] < theElement){ // 当前父节点小于插入值， 将当前插入值逐层向上
        heap[currentIndex] = heap[currentIndex / 2];
        currentIndex /= 2;
    }
    heap[currentIndex] = theElement; // 将当前插入元素放到合适的地方
}

// 从最后一个有子节点的节点开始寻找，因为开始时数组是乱序，不能像pop那样从根节点开始
template<class T>
void maxHeap<T>::initialize(T *theHeap, int theSize) {
    delete [] heap;
    heap = theHeap;
    heapSize = theSize;
    arrayLength = theSize+1;

    for (int root = heapSize/2; root >= 1; --root) {
        T rootElement = heap[root];

        int childIndex = root * 2; // 左子节点，如果有右子节点的话
        // 这个循环会为当前的 rootElement 在当前分支下找一个合适的位置插入， 参考pop
        // 逐级向上，分治处理， 这里很重要
        while (childIndex <= heapSize){ // 在范围内
            if (childIndex < heapSize && heap[childIndex] < heap[childIndex+1])
                ++childIndex;
            if (rootElement >= heap[childIndex]) // 可以直接当做现在的父节点
                break;
            // 如果不行的话就把子节点和 rootElement 替换一下
            heap[childIndex/2] = heap[childIndex];
            childIndex *= 2;
        }
        heap[childIndex/2] = rootElement;
    }
}

template<class U>
std::ostream &operator<<(std::ostream &os, maxHeap<U>& heap) {
    for (int i = 1; i <= heap.size(); ++i) {
        os << heap.getElement(i) << " ";
    }
    return os;
}

template<class T>
T &maxHeap<T>::getElement(int index) const {
    return heap[index];
}

template<class T>
maxHeap<T>::maxHeap(maxHeap<T> &theHeap) {
    heapSize = theHeap.size();
    arrayLength = heapSize+1;
    heap = new T[arrayLength];
    std::copy(theHeap.heap, theHeap.heap + arrayLength, heap);
}

template<class T>
void maxHeap<T>::changeMax(T theElement) {
    if (empty())
        std::cout << "the heap is empty!" << std::endl;
    else{
        heap[1].~T(); // 删除最大元素。因为已经是有序排列了
        // 从根开始寻找合适的位置放置
        int currentIndex = 1, childIndex = 2; // 根节点的第一个子节点序号为2

        // 当前判断的是childIndex的值，函数中需要替换的是当前父节点的值
        // 因为在pop之前是已经有了一定顺序的，所以可以从根节点这样做
        while (childIndex <= heapSize){ // 当前遍历的子节点没有超出数据范围
            if (childIndex < heapSize && heap[childIndex] < heap[childIndex+1]) // 找到当前两个子节点中较大的进行判断
                ++childIndex;
            if (theElement > heap[childIndex]) // 当前就是合适的位置
                break;

            // 当前位置不合适，继续向叶节点寻找
            heap[currentIndex] = heap[childIndex];
            currentIndex = childIndex;
            childIndex *= 2; // 如果*2之后大于heapsize，则证明当前叶子节点没有再下一层的节点，所以直接放在这里就可以
        }
        heap[currentIndex] = theElement;
    }
}

template<class T>
void maxHeap<T>::remove(int i) {
    if (i>size()){
        std::cout << "out of Range!" << std::endl;
        return;
    }
    heap[i].~T();
    T lastElement = heap[heapSize--];
    int currentIndex = i, childIndex = currentIndex*2;
    while (childIndex<=heapSize){
        if (childIndex<heapSize && heap[childIndex] < heap[childIndex+1])
            ++childIndex;
        if (lastElement > heap[childIndex])
            break;

        heap[currentIndex] = heap[childIndex];
        currentIndex = childIndex;
        childIndex *= 2;
    }
    heap[currentIndex] = lastElement;
}


#endif //CHAPTER12_MAXHEAP_H
