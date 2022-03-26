//
// Created by Dell on 2021/6/9.
//

#ifndef CHAPTER11_BINARYTREENODE_H
#define CHAPTER11_BINARYTREENODE_H

#include "string"
#include "stack"
#include "queue"
#include "vector"
#include "queue"

//using namespace std;

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

/*
// 输出测试
//template<class T>
//void visit(binaryTreeNode<T>* x)
//{
//    std::cout << x->element << " ";
//}
//
//template<class T>
//void inOrder(binaryTreeNode<T>* x)
//{
//    if(x!=NULL){
//        inOrder(x->leftChild);
//        visit(x);
//        inOrder(x->rightChild);
//    }
//}
//
//// Q25(1)
//template<class T>
//void postCopyTreeNode(binaryTreeNode<T>* sourceNode, binaryTreeNode<T>* targetNode)
//{
//    if (sourceNode!=NULL){
//        if (sourceNode->leftChild!=NULL) {
//            targetNode->leftChild = new binaryTreeNode<T>();
//            preCopyTreeNode(sourceNode->leftChild, targetNode->leftChild);
//        }
//        if (sourceNode->rightChild!=NULL) {
//            targetNode->rightChild = new binaryTreeNode<T>();
//            preCopyTreeNode(sourceNode->rightChild, targetNode->rightChild);
//        }
//        targetNode->element = sourceNode->element;
//    }
//}
//
//// Q25(2)
//template<class T>
//void preCopyTreeNode(binaryTreeNode<T>* sourceNode, binaryTreeNode<T>* targetNode)
//{
//    if (sourceNode!=NULL){
//        targetNode->element = sourceNode->element;
//        if (sourceNode->leftChild!=NULL) {
//            targetNode->leftChild = new binaryTreeNode<T>();
//            preCopyTreeNode(sourceNode->leftChild, targetNode->leftChild);
//        }
//        if (sourceNode->rightChild!=NULL) {
//            targetNode->rightChild = new binaryTreeNode<T>();
//            preCopyTreeNode(sourceNode->rightChild, targetNode->rightChild);
//        }
//    }
//}
//
//// Q26 后序的方法，这里应该可以把两个程序优化成一个，
//template<class T>
//void calculateGetNum(binaryTreeNode<T>* sourceNode, std::stack<int>& numStack)
//{
//    if (sourceNode!=NULL){
//        calculateGetNum(sourceNode->leftChild, numStack);
//        calculateGetNum(sourceNode->rightChild, numStack);
//
//        int num1, num2;
//        if (sourceNode->element != "+" && sourceNode->element != "-" && sourceNode->element != "*" && sourceNode->element != "/"){
//            num1 = atoi(sourceNode->element.c_str());
//            numStack.push(num1);
//        } else{
//            num1 = numStack.top();
//            numStack.pop();
//            num2 = numStack.top();
//            numStack.pop();
//            if(sourceNode->element== "+")
//                numStack.push(num2 + num1);
//            else if(sourceNode->element == "-")
//                numStack.push(num2 - num1);
//            else if(sourceNode->element== "*")
//                numStack.push(num2 * num1);
//            else if(sourceNode->element == "/")
//                numStack.push(num2 / num1);
//        }
//    }
//}
//template<class T>
//int calculateNum(binaryTreeNode<T>* sourceNode)
//{
//    std::stack<int> numStack;
//    calculateGetNum(sourceNode, numStack);
//    return numStack.top();
//}
//
//// Q27 依然是递归
//template<class T>
//int getDepth(binaryTreeNode<T>* sourceNode){
//    if (sourceNode!=NULL){
//        int numLeft = getDepth(sourceNode->leftChild);
//        int numRight = getDepth(sourceNode->rightChild);
//        return numLeft > numRight ? numLeft+1 : numRight+1;
//    }
//    return 0;
//}
//
//// Q28 计算节点个数
//template<class T>
//int getNodeCount(binaryTreeNode<T>* sourceNode){
//    if (sourceNode!=NULL){
//        int numLeft = getNodeCount(sourceNode->leftChild);
//        int numRight = getNodeCount(sourceNode->rightChild);
//        return numLeft + numRight + 1;
//    }
//    return 0;
//}
//
//// Q29 节点最多的层数
//template<class T>
//int nodeMostLayer(binaryTreeNode<T>* sourceNode){
//    std::queue<binaryTreeNode<T>* > q;
//    int totalLayer = getDepth(sourceNode);
//    int *layerCounts = new int[totalLayer+1]{0}; // 没有第0层，全部初始化为0
//
//    if (sourceNode==NULL) return 0;
//    else layerCounts[1]=1; // 根节点一定是1个
//
//    int mostLayer=0, mostLayerCount=0, currentLayer=1;
//    binaryTreeNode<T> *currentNode = sourceNode;
//    while (currentNode != NULL){
//        if (currentNode->leftChild != NULL){
//            q.push(currentNode->leftChild);
//            ++layerCounts[currentLayer+1]; // 更新下一层的个数
//        }
//        if (currentNode->rightChild != NULL){
//            q.push(currentNode->rightChild);
//            ++layerCounts[currentLayer+1];
//        }
//        if (!q.empty()){
//            currentNode = q.front();
//            q.pop();
//        } else
//            currentNode = NULL;
//        --layerCounts[currentLayer]; // 这里已经减1了，所以下边要加1
//        if (layerCounts[currentLayer]==0) // 当前层遍历完成
//            ++currentLayer; // 切换到下一层
//        else if (layerCounts[currentLayer] > mostLayerCount){ // 还在当前层
//            mostLayerCount = layerCounts[currentLayer] + 1;
//            mostLayer = currentLayer;
//        }
//    }
//    std::cout << "layer: " << mostLayer << " count: " << mostLayerCount << std::endl;
//    return mostLayer;
//}
//
//// Q30 将二叉树保存到栈中
//template<class T>
//void inVec(binaryTreeNode<T>* sourceNode, std::vector<T>& myVec){
//    if(sourceNode!=NULL){
//        inVec(sourceNode->leftChild, myVec);
//        myVec.push_back(sourceNode->element);
//        inVec(sourceNode->rightChild, myVec);
//    }
//}
//
//// Q31 将二叉树保存到栈中,因为使用了栈，所以输出顺序和入栈顺序相反
//template<class T>
//void preVec(binaryTreeNode<T>* sourceNode, std::vector<T>& myVec){
//    if(sourceNode!=NULL){
//        myVec.push_back(sourceNode->element);
//        preVec(sourceNode->leftChild, myVec);
//        preVec(sourceNode->rightChild, myVec);
//    }
//}
//
//// Q32 将二叉树保存到栈中
//template<class T>
//void postVec(binaryTreeNode<T>* sourceNode, std::vector<T>& myVec){
//    if(sourceNode!=NULL){
//        postVec(sourceNode->leftChild, myVec);
//        postVec(sourceNode->rightChild, myVec);
//        myVec.push_back(sourceNode->element);
//    }
//}
//
//// Q33需要用递归实现，且需要保证各个节点的数据各不相同，否则获取的二叉树不唯一
//// 需要重新导入二叉树数据
//
//
////template<class T>
////void Q33Recursion(binaryTreeNode<T>* targetNode, vector<T>& inVec, stack<T>& preStack,int parentIndex, int grandParentIndex)
////{
////    if (!preStack.empty()){
////        T curElement = preStack.top();
////
////        int currentIndex = 0;
////        for(auto t : inVec){
////            if (t == curElement)
////                break;
////            else
////                ++currentIndex;
////        }
////        if (currentIndex<parentIndex){ // 在当前分支下
////            targetNode->leftChild = new binaryTreeNode<T>(curElement);
////            preStack.pop();
////            Q33Recursion(targetNode->leftChild, inVec, preStack, currentIndex, parentIndex);
////        }
////    }
////
////    if (!preStack.empty()){
////        T curElement = preStack.top();
////
////        int currentIndex = 0;
////        for(auto t : inVec){
////            if (t == curElement)
////                break;
////            else
////                ++currentIndex;
////        }
////        if (currentIndex>parentIndex && currentIndex < grandParentIndex) { // 右节点
////            targetNode->rightChild = new binaryTreeNode<T>(curElement);
////            preStack.pop();
////            Q33Recursion(targetNode->rightChild, inVec, preStack, currentIndex, parentIndex);
////        }
////    }
////}
////
////template<class T>
////binaryTreeNode<T>* getTreeFromPreAndInStack(binaryTreeNode<T>* sourceNode)
////{
////    vector<T> MyPreVec, MyInVec;
////    preVec(sourceNode, MyPreVec);
////    inVec(sourceNode, MyInVec);
////
////    stack<T> PreStack;
////    for (int i = MyPreVec.size()-1;i >=0 ; --i)
////        PreStack.push(MyPreVec[i]);
////
////    T curElement = PreStack.top();
////    PreStack.pop();
////
////    int currentIndex = 0;
////    for(auto t : MyInVec){
////        if (t == curElement)
////            break;
////        else
////            ++currentIndex;
////    }
////
////    auto targetNode = new binaryTreeNode<T>(curElement);
////    Q33Recursion(targetNode, MyInVec, PreStack, currentIndex, MyInVec.size());
////    return targetNode;
////}
//
//// Q33
//// 这个递归和上一个不成功的递归之间的区别就是是否把中序vector逐个拆开，如果不拆开就会导致上面的混乱
//// 且引入很多不必要复杂的表示
//template<class T>
//binaryTreeNode<T>* Q33Recursion(vector<T>& inVec, stack<T>& preStack)
//{
//    binaryTreeNode<T>* node = NULL;
//    if (!preStack.empty() && inVec.size() > 0)
//    {
//        T curElement = preStack.top();
//        int currentIndex = 0;
//        for(auto t : inVec){
//            if (t == curElement)
//                break;
//            else
//                ++currentIndex;
//        }
//        if (currentIndex<inVec.size()) { // 当前vector中存在当前所需元素
////            构造分别对应当前的
//            vector<T> leftVec(inVec.begin(), inVec.begin()+currentIndex);
//            vector<T> rightVec(inVec.begin()+currentIndex+1, inVec.end());
//            preStack.pop();
//            node = new binaryTreeNode<T>(curElement);
//            node->leftChild = Q33Recursion(leftVec, preStack);
//            node->rightChild = Q33Recursion(rightVec, preStack);
//        }
//    }
//    return node;
//}
//
//// Q33
//template<class T>
//binaryTreeNode<T>* getTreeFromPreAndInStack(binaryTreeNode<T>* sourceNode)
//{
//    vector<T> MyPreVec, MyInVec;
//    preVec(sourceNode, MyPreVec);
//    inVec(sourceNode, MyInVec);
//    stack<T> PreStack;
//    for (int i = MyPreVec.size()-1;i >=0 ; --i)
//        PreStack.push(MyPreVec[i]);
//
//    binaryTreeNode<T>* p = Q33Recursion(MyInVec, PreStack);
//    return p;
//}
//
//// 每个运算。符必须有两个操作数，否则会有错误
//binaryTreeNode<char>* getTreeFromPostOrder(string strVec)
//{
//    stack<binaryTreeNode<char>*> NodeStack;
//    for(auto str : strVec){
//        auto temp = new binaryTreeNode<char>(str);
//        if (str == '+' || str == '-' || str == '*' || str == '/' ){ //单操作数或者双操作数
//            temp->rightChild = NodeStack.top();
//            NodeStack.pop();
//            if (!NodeStack.empty()){
//                temp->leftChild = NodeStack.top();
//                NodeStack.pop();
//            }
//        }
//        NodeStack.push(temp);
//    }
//    return NodeStack.top();
//}
*/
#endif //CHAPTER11_BINARYTREENODE_H
