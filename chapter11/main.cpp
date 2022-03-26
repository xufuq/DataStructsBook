#include <iostream>
#include <string>
#include "include/binaryTreeNode.h"
#include "include/linkedBinaryTree.h"

using namespace std;

int main() {
    /*
    // 手动实现二叉树的初始化
//    auto* rootNode = new binaryTreeNode<string>("+");
//    rootNode->leftChild = new binaryTreeNode<string>("+");
//    rootNode->leftChild->leftChild = new binaryTreeNode<string>("*");
//    rootNode->leftChild->rightChild = new binaryTreeNode<string>("12");
//    rootNode->leftChild->leftChild->leftChild = new binaryTreeNode<string>("2");
//    rootNode->leftChild->leftChild->rightChild = new binaryTreeNode<string>("4");
//
//    rootNode->rightChild = new binaryTreeNode<string>("-");
//    rootNode->rightChild->leftChild = new binaryTreeNode<string>("*");
//    rootNode->rightChild->leftChild->leftChild = new binaryTreeNode<string>("8");
//    rootNode->rightChild->leftChild->rightChild = new binaryTreeNode<string>("2");
//    rootNode->rightChild->rightChild = new binaryTreeNode<string>("+");
//    rootNode->rightChild->rightChild->leftChild = new binaryTreeNode<string>("6");
//    rootNode->rightChild->rightChild->rightChild = new binaryTreeNode<string>("/");
//    rootNode->rightChild->rightChild->rightChild->leftChild = new binaryTreeNode<string>("8");
//    rootNode->rightChild->rightChild->rightChild->rightChild = new binaryTreeNode<string>("2");
*/

    auto* rootNode = new binaryTreeNode<string>("a");
    rootNode->leftChild = new binaryTreeNode<string>("b");
    rootNode->leftChild->leftChild = new binaryTreeNode<string>("c");
    rootNode->leftChild->rightChild = new binaryTreeNode<string>("d");
    rootNode->leftChild->leftChild->leftChild = new binaryTreeNode<string>("e");
    rootNode->leftChild->leftChild->rightChild = new binaryTreeNode<string>("f");

    rootNode->rightChild = new binaryTreeNode<string>("g");
    rootNode->rightChild->leftChild = new binaryTreeNode<string>("h");
    rootNode->rightChild->leftChild->leftChild = new binaryTreeNode<string>("i");
    rootNode->rightChild->leftChild->rightChild = new binaryTreeNode<string>("j");
    rootNode->rightChild->rightChild = new binaryTreeNode<string>("k");
    rootNode->rightChild->rightChild->leftChild = new binaryTreeNode<string>("l");
    rootNode->rightChild->rightChild->rightChild = new binaryTreeNode<string>("m");
    rootNode->rightChild->rightChild->rightChild->leftChild = new binaryTreeNode<string>("n");
    rootNode->rightChild->rightChild->rightChild->rightChild = new binaryTreeNode<string>("o");
/*
//    inOrder(rootNode); // 中序输出
//    auto* preCopyNode = new binaryTreeNode<string>();
//    auto* postCopyNode = new binaryTreeNode<string>();
//    preCopyTreeNode(rootNode, preCopyNode);
////    rootNode->element = "fdfa";
//    cout << endl << "pre"<< endl;
//    inOrder(preCopyNode);
//    postCopyTreeNode(rootNode, postCopyNode);
//    cout << endl << "post"<< endl;
//    inOrder(postCopyNode);
//    cout << calculateNum(rootNode) << endl;
//    cout << getDepth(rootNode) << endl;
//    cout << getNodeCount(rootNode) << endl;
//    nodeMostLayer(rootNode);


//    vector<string> MyVec;
//    preVec(rootNode, MyVec);
//    cout << "preStack: ";
//    for (auto v : MyVec)
//        cout << v << " ";
//    MyVec.clear();
//    cout << endl;
//
//    inVec(rootNode, MyVec);
//    cout << "inStack:  ";
//    for (auto v : MyVec)
//        cout << v << " ";
//    MyVec.clear();

//    auto targetNode = getTreeFromPreAndInStack(rootNode);
//    vector<string> MyVec;
//    preVec(rootNode, MyVec);
//    for (auto v : MyVec)
//        cout << v << " ";
//    MyVec.clear();
//    cout << endl;
//    inOrder(rootNode);
//    cout << endl;
//    inOrder(targetNode);
 */
//    auto cal = getTreeFromPostOrder("ba-xy++eb+ca**/");
//    inOrder(cal);

    linkedBinaryTree<string> myLinkedTree, myLinkedTree2;
    myLinkedTree.initialize(rootNode);
    rootNode->rightChild->rightChild->rightChild->rightChild = new binaryTreeNode<string>("z");
    myLinkedTree2.initialize(rootNode);
    myLinkedTree.preOrderOutput();
    cout << myLinkedTree.size() << endl;
    cout << myLinkedTree.compare(myLinkedTree2) << endl;
    myLinkedTree.swapTrees();
    myLinkedTree.preOrderOutput();
    linkedBinaryTree<string>::forwardIterator myIterator = myLinkedTree.begin(), myEnd = myLinkedTree.end();
    while (myIterator!=myEnd){
        cout << *myIterator << "  ";
        ++myIterator;
    }
    cout << endl;
    myLinkedTree.inOrderOutput();
    return 0;
}
