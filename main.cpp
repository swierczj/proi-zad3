#include <iostream>
#include "binaryCodedRepresentation.h"
#include <string>

int main()
{
    /* FIRST ARG FOR BASE, SECOND FOR BITS PER NUMBER */
    //char ch = '1';
    //isdigit( static_cast<unsigned char>(ch) );
    //int t = static_cast<int>(ch);
    std::string x = "120";
    BinaryCodedRepresentation<16, 4> testBCR("f1"); //check if correct
    BinaryCodedRepresentation<8, 4> testBCRoperators = "10";
    //testBCRoperators = "140";

    std::cout << testBCR.getDecimalValue() << " to " << testBCR << std::endl
              << testBCRoperators.getDecimalValue() << std::endl;
    return 0;
}