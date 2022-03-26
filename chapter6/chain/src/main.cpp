#include "chain.h"
#include "extendedChain.h"
#include "arrayList.h"
#include "circularListWithHearder.hpp"
#include "doubleLinkedList.hpp"
#include "doubleCircularList.hpp"
#include "doubleCircularListWithHeader.hpp"
#include <iostream>


int main()
{
    std::cout << "----------------------chain---------------------------------" << std::endl;
    chain<int> chainTest(10);
    for(int i=0;i<10;i++)
        chainTest.insert(i, 3*i-2);
    std::cout << chainTest <<std::endl;
    chainTest.erase(5);
    std::cout<<chainTest.get(8)<<std::endl;
    std::cout<<chainTest.indexOf(19)<<std::endl;

    chain<int>::myIterator currentP = chainTest.begin();
    for(;currentP!=chainTest.end();currentP++)
        std::cout<<*currentP<<" ";
    std::cout<<std::endl;
        std::cout << "----------------------extendedChain---------------------------------" << std::endl;
    extendedChain<int> chainTest2(10);
    for(int i=0;i<10;i++)
        chainTest2.insert(i, i);
    std::cout << chainTest2 <<std::endl;
    chainTest2.erase(9);
    std::cout << chainTest2 <<std::endl;
    chainTest2.push_back(10);
    chainTest2.push_back(11);
    std::cout << chainTest2 <<std::endl;
    extendedChain<int> chainTest3(chainTest2);
    chainTest3.push_back(12);
    std::cout << chainTest3 <<std::endl;
    chainTest3.setSize(5);
    std::cout << chainTest3 <<std::endl;
    chainTest3.set(2, 5);
    std::cout << chainTest3 <<std::endl;
    std::cout << "----------------------Q4 to Q9---------------------------------" << std::endl;
    extendedChain<int> chainTest4(10);
    for(int i=0;i<10;i++)
        chainTest4.insert(i, i);
    std::cout << chainTest4 <<std::endl;
    chainTest4.removeRange(5,10);
    std::cout << chainTest4 <<std::endl;
    chainTest4.push_back(10);
    std::cout << chainTest4 <<std::endl;
    chainTest4.removeRange(0, 6);
    std::cout << chainTest4 <<std::endl;
    chainTest4.push_back(69);
    std::cout << chainTest4 <<std::endl;
    chainTest4.push_back(33);
    std::cout << chainTest4 <<std::endl;
    chainTest4.insert(0, 10);
    std::cout << chainTest4 <<std::endl;
    chainTest4.push_back(23);
    std::cout << chainTest4 <<std::endl;
    std::cout << chainTest4.lastIndexOf(23) <<std::endl;
    std::cout << chainTest4[2] <<std::endl;
    chainTest4[2] = 5;
    std::cout << chainTest4[2] <<std::endl;
    extendedChain<int> chainTest5(chainTest4);
    std::cout << (chainTest4 == chainTest5) <<std::endl;
    chainTest5[3] = 0;
    std::cout << " == " << (chainTest4 == chainTest5) <<std::endl;
    std::cout << " != " << (chainTest4 != chainTest5) <<std::endl;
    std::cout << chainTest4<<std::endl;
    std::cout << chainTest5 <<std::endl;
    std::cout << " < " <<  (chainTest4 < chainTest5) <<std::endl;
    std::cout << " > " <<  (chainTest4 > chainTest5) <<std::endl;
    chainTest4.swap(chainTest5);
    std::cout << chainTest4<<std::endl;
    std::cout << chainTest5 <<std::endl;
    chainTest5.push_back(111);
    std::cout << chainTest5 <<std::endl;
    std::cout << "----------------------Q11 and Q17---------------------------------" << std::endl;
    arrayList<int> arrayTest;
    for(int i=0;i<10;i++)
        arrayTest.insert(i, i);
    extendedChain<int> chainTest6 = array2chain(arrayTest);
    std::cout << chainTest6 <<std::endl;
    chainTest6[2]=10;
    arrayTest = chain2array(chainTest6);
    std::cout << arrayTest <<std::endl;
    chainTest6.fromList(arrayTest);
    std::cout << chainTest6 <<std::endl;
    arrayTest = chainTest6.toList();
    std::cout << arrayTest <<std::endl;
    chainTest6.leftShift(1);
    std::cout << chainTest6 <<std::endl;
    chainTest6.reverse();
    std::cout << chainTest6 <<std::endl;
    chainTest6.push_back(22);
    std::cout << chainTest6 <<std::endl;
    std::cout << "----------------------Q17 and Q23---------------------------------" << std::endl;
    chainTest6 = meld(chainTest4, chainTest5);
    std::cout << "chainTest4: " << chainTest4 <<std::endl;
    std::cout << "chainTest5: " << chainTest5 <<std::endl;
    std::cout << chainTest6 <<std::endl;
    chain<int> chainTest7(10);
    for(int i=0;i<10;i++)
        chainTest7.insert(i, 3*i-2);
    chain<int> chainTest8(10);
    for(int i=0;i<7;i++)
        chainTest8.insert(i, i);
    std::cout << "chainTest7: " << chainTest7 <<std::endl;
    std::cout << "chainTest8: " << chainTest8 <<std::endl;
    chainTest.meld(chainTest7, chainTest8);
    std::cout << "chainTest: " << chainTest <<std::endl;
    extendedChain<int> chainTest9, chainTest10;
    for(int i=0; i<10;i++)
    {
        chainTest9.push_back(i);
        chainTest10.push_back(3*i-8);
    }
    std::cout << "chainTest9: " << chainTest9 <<std::endl;
    std::cout << "chainTest10: " << chainTest10 <<std::endl;
    chainTest6 = merge(chainTest9, chainTest10);
    std::cout << chainTest6 <<std::endl;
    for(int i=0;i<10;i++)
    {
        chainTest7.insert(i, 3*i-2);
        chainTest8.insert(i, i);
    }
    std::cout << "chainTest7: " << chainTest7 <<std::endl;
    std::cout << "chainTest8: " << chainTest8 <<std::endl;
    chainTest.merge(chainTest7, chainTest8);
    std::cout << chainTest <<std::endl;
    split(chainTest6, chainTest9, chainTest10);
    std::cout << "chainTest7: " << chainTest9 <<std::endl;
    std::cout << "chainTest8: " << chainTest10 <<std::endl;
    std::cout << chainTest6 <<std::endl;
    chainTest.split(chainTest7, chainTest8);
    std::cout << "chainTest7: " << chainTest7 <<std::endl;
    std::cout << "chainTest8: " << chainTest8 <<std::endl;
    chainTest6.circularShift(3);
    std::cout << chainTest6 <<std::endl;
    std::cout << "----------------------Q17 and Q23---------------------------------" << std::endl;
    chain<int> chainTest11(4);
    chainTest11.insert(0,5);
    chainTest11.insert(0,8);
    chainTest11.insert(0,6);
    chainTest11.insert(0,9);
    chainTest11.insert(0,20);
    std::cout << chainTest11 <<std::endl;
    // chainTest11.insertSort();
    chainTest11.bubbleSort();
    std::cout << chainTest11 <<std::endl;
    std::cout << "----------------------Q38 and Q42---------------------------------" << std::endl;
    circularListWithHeader<int> chainTest12(10), chainTest13(12), chainTest14(10);
    for(int i=0; i<10; i++)
        chainTest12.insert(0, i);
    for(int i=0; i<12; i++)
        chainTest13.insert(0, 2*i);
    std::cout << chainTest12 << std::endl;
    chainTest12.reverse();
    chainTest13.reverse();
    std::cout << chainTest12 << std::endl;
    std::cout << chainTest13 << std::endl;
    // chainTest14.meld(chainTest12, chainTest13);
    // std::cout << chainTest14 << std::endl;
    chainTest14.merge(chainTest12, chainTest13);
    std::cout << chainTest14 << std::endl;
    std::cout << "----------------------Q43 and Q48---------------------------------" << std::endl;
    doubleLinkedList<int> chainTest15(10), chainTest16(10), chainTest17(10);
    for(int i=0; i<10; i++)
    {
        chainTest15.insert(0, i);
        chainTest16.insert(0, 2*i-5);
        chainTest17.insert(0, 3*i+2);
    }
    std::cout << chainTest15 << std::endl;
    std::cout << chainTest16 << std::endl;
    std::cout << chainTest17 << std::endl;
    chainTest15.erase(0);
    chainTest15.erase(1);
    chainTest16.erase(2);
    chainTest16.erase(8);
    chainTest17.erase(9);
    chainTest17.erase(0);
    std::cout << chainTest15 << std::endl;
    std::cout << chainTest16 << std::endl;
    std::cout << chainTest17 << std::endl;
    // chainTest15.appendChain(chainTest16);
    // chainTest16.insert(0, 121);
    // std::cout << chainTest15 << std::endl;
    // std::cout << chainTest16 << std::endl;
    // chainTest15.reverse();
    // std::cout << chainTest15 << std::endl;
    // chainTest16.meld(chainTest15, chainTest17);
    // std::cout << chainTest16 << std::endl;
    // chainTest16.reverse();
    // std::cout << chainTest16 << std::endl;
    chainTest15.reverse();
    chainTest16.reverse();
    chainTest17.merge(chainTest15, chainTest16);
    std::cout << "merge: " << chainTest17 << std::endl;
    chainTest17.split(chainTest15, chainTest16);
    std::cout << "split: " << chainTest15 << std::endl;
    std::cout << "split: " << chainTest16 << std::endl;

    std::cout << "----------------------Q49 and Q54---------------------------------" << std::endl;
    doubleCircularList<int> chainTest18(10), chainTest19(10), chainTest20(10);
    for(int i=0; i<10; i++)
    {
        chainTest18.insert(i, i);
        chainTest19.insert(i, 2*i-3);
        chainTest20.insert(i, 3*i - 10);
    }
    std::cout << chainTest18 << std::endl;
    std::cout << chainTest19 << std::endl;
    // chainTest20.meld(chainTest18, chainTest19);
    chainTest20.merge(chainTest18, chainTest19);
    std::cout << chainTest20 << std::endl;
    chainTest20.split(chainTest18, chainTest19);
    std::cout << chainTest18 << std::endl;
    std::cout << chainTest19 << std::endl;
    std::cout << "----------------------Q55 and Q61---------------------------------" << std::endl;
    doubleCircularListWithHeader<int> chainTest21(10), chainTest22(10);
    for(int i=0; i<10; i++)
    {
        chainTest21.insert(i, i);
        chainTest22.insert(i, 2*i-3);
    }
    doubleCircularListWithHeader<int> chainTest23(chainTest21);
    std::cout << chainTest21 << std::endl;
    std::cout << chainTest22 << std::endl;
    std::cout << chainTest23 << std::endl;
    chainTest23.reverse();
    std::cout << chainTest23 << std::endl;
    chainTest22.erase(5);
    // chainTest23.meld(chainTest22, chainTest21);
    chainTest23.merge(chainTest21, chainTest22);
    std::cout << chainTest23 << std::endl;
    chainTest23.split(chainTest21, chainTest22);
    std::cout << chainTest21 << std::endl;
    std::cout << chainTest22 << std::endl;
    return 0;
}

