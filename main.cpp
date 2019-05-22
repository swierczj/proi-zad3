#include <iostream>
#include "binaryCodedRepresentation.h"
#include <string>

int main()
{
    //char ch = '1';
    //isdigit( static_cast<unsigned char>(ch) );
    //int t = static_cast<int>(ch);
    BinaryCodedRepresentation<10, 10> testBCR("0011"); //check if correct

    std::cout << testBCR << std::endl;
    return 0;
}