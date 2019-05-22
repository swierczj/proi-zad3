#include <iostream>
#include "binaryCodedRepresentation.h"
#include <string>

int main()
{
    /* FIRST ARG FOR BASE, SECOND FOR BITS PER NUMBER */
    //char ch = '1';
    //isdigit( static_cast<unsigned char>(ch) );
    //int t = static_cast<int>(ch);
    BinaryCodedRepresentation<16, 4> testBCR("f1"); //check if correct
    BinaryCodedRepresentation<16, 4> testBCRCopy(testBCR);

    std::cout << testBCRCopy << std::endl
              << testBCRCopy.getDecimalValue() << std::endl;
    return 0;
}