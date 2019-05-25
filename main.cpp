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
    BinaryCodedRepresentation<8, 4> testBCR("11"); //check if correct
    BinaryCodedRepresentation<8, 4> testBCRoperators = "10";
    //testBCRoperators = "140";

    testBCRoperators = "2";

    std::cout << "wieksze?\n"; //debug
    std::string doCouta = testBCRoperators > std::string("180") ? "tak" : "nie"; //debug
    std::cout << doCouta << '\n'; //debug

//    std::cout << "rowne?\n"; //debug
//    std::string doCouta2 = 140 == testBCRoperators ? "tak" : "nie"; //debug
//    std::cout << doCouta2 << '\n'; //debug

    std::cout << testBCR.getDecimalValue() << " to " << testBCR << std::endl
              << testBCRoperators.getDecimalValue() << std::endl;
    return 0;
}