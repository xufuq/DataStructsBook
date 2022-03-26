//
// Created by dell on 2021/1/27.
//

#ifndef MAIN_PRINTERROR_H
#define MAIN_PRINTERROR_H
#include <string>
#include <iostream>

class printError
{
public:
    printError(std::string mes){message=mes;}
    void what(){std::cout << message <<std::endl;}
private:
    std::string message;
};

#endif //MAIN_PRINTERROR_H
