#include "sortedArrayList.h"
#include <iostream>
#include "string"

int main()
{
    sortedArrayList<int, std::string> myMap(10);
    myMap.insert(std::pair<int, std::string>(2, "fa"));
    myMap.insert(std::pair<int, std::string>(0, "fd"));
    myMap.insert(std::pair<int, std::string>(3, "fb"));
    myMap.insert(std::pair<int, std::string>(5, "fc"));
    myMap.insert(std::pair<int, std::string>(1, "fd"));
    myMap.insert(std::pair<int, std::string>(10, "fe"));
    std::cout << myMap << std::endl;
    myMap.erase(2);
    std::cout << myMap << std::endl;
    std::cout << myMap.find(3)->second << std::endl;
	return 0;
}