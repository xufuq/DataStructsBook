#include <iostream>
#include "include/completeWinnerTree.h"

using namespace std;

int main() {
    completeWinnerTree<int> tree;
    int player[] = {0, 12, 34, 8, 20, 9, 3, 55};
//    tree.initialize(player, 7);
//    cout << "winner: " << tree.winner() << endl;
//    player[tree.winner()] = 100;
//    tree.rePlay(tree.winner());
//    cout << "winner: " << tree.winner() << endl;
//    player[tree.winner()] = 100;
//    tree.rePlay(tree.winner());
//    cout << tree.winner() << endl;
    tree.initWithRecursion(player, 7);
    cout << endl << tree.winner() << endl;
    int *mySort;
    tree.getSort(mySort);
    for (int i = 1; i < sizeof(mySort); ++i) {
        cout << mySort[i] << " ";
    }
    cout << endl << tree.winner() << endl;
    return 0;
}
