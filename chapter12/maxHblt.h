//
// Created by Dell on 2021/6/18.
//

#ifndef CHAPTER12_MAXHBLT_H
#define CHAPTER12_MAXHBLT_H

template<class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;

    binaryTreeNode() {leftChild=rightChild=NULL;}
    explicit binaryTreeNode(const T& theElement){
        element = theElement;
        leftChild=rightChild=NULL;
    }
    binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeft, binaryTreeNode<T>*theRight):element(theElement), leftChild(theLeft), rightChild(theRight) {}
};

template<class T>
class maxHblt
{
public:
    maxHblt(){
        root=NULL;
        treeSize=0;
    }
private:
    void meld(binaryTreeNode<std::pair<int, T>>* &, binaryTreeNode<std::pair<int, T>>* &);
    binaryTreeNode<std::pair<int, T>> *root;
    int treeSize;
};

template<class T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int, T>> *&, binaryTreeNode<std::pair<int, T>> *&) {

}

#endif //CHAPTER12_MAXHBLT_H
