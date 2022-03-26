#include <iostream>
#include "include/binarySearchTree.h"

int main() {
    binarySearchTree<int, char> testSearch;
    testSearch.insert(std::pair<int, char>(10, 'a'));
    testSearch.insert(std::pair<int, char>(5, 'b'));
    testSearch.insert(std::pair<int, char>(20, 'c'));
    testSearch.insert(std::pair<int, char>(14, 'd'));
    testSearch.insert(std::pair<int, char>(30, 'e'));
    testSearch.insert(std::pair<int, char>(8, 'f'));
    testSearch.insert(std::pair<int, char>(6, 'g'));
    testSearch.insert(std::pair<int, char>(35, 'h'));
    testSearch.insert(std::pair<int, char>(25, 'i'));
    testSearch.insert(std::pair<int, char>(3, 'j'));
    testSearch.insert(std::pair<int, char>(12, 'k'));
    testSearch.insert(std::pair<int, char>(17, 'l'));
    testSearch.ascend();

    testSearch.outputInRange(10, 30);

    binarySearchTree<int, char> lessTree, greaterTree;
    binaryTreeNode<std::pair<const int, char>>* theResult = testSearch.split(13, lessTree, greaterTree);
    if (theResult!=NULL)
        std:: cout << "the == element: " << theResult->element << std::endl;
    std::cout << "root tree: ";
    std::cout << testSearch.size() << std::endl;
    std::cout << "less tree: ";
    std::cout << lessTree.size() << std::endl;
    lessTree.ascend();
    std::cout << "greater tree: ";
    std::cout << greaterTree.size() << std::endl;
    greaterTree.ascend();

    return 0;
}
