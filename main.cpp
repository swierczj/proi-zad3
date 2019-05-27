#include <iostream>
#include "binaryCodedRepresentation.h"
#include <string>

int main()
{
    /* FIRST ARG FOR BASE, SECOND FOR BITS PER NUMBER */
    //char ch = '1';
    //isdigit( static_cast<unsigned char>(ch) );
    //int t = static_cast<int>(ch);

    BinaryCodedRepresentation<36, 6> testBCR(35); //check if correct
    BinaryCodedRepresentation<4, 3> testBCRoperators = "3";
    //testBCRoperators += "-z"; //unable to calculate so it's good

    testBCRoperators++;
    //testBCRoperators = "140";

    //testBCRoperators = "2";

//    bool BCRtestGreater = testBCR > testBCRoperators;
//    bool BCRoperEqual = BinaryCodedRepresentation<8, 4>(10) > testBCRoperators;
//    bool BCRtestLesser = testBCRoperators > testBCR;
//    std::cout << BCRtestGreater << ' ' << BCRoperEqual << ' ' << BCRtestLesser << '\n';

    /*std::cout << "wieksze?\n"; //debug
    std::string doCouta = testBCRoperators > std::string("180") ? "tak" : "nie"; //debug
    std::cout << doCouta << '\n'; //debug
*/
//    std::cout << "rowne?\n"; //debug
//    std::string doCouta2 = 140 == testBCRoperators ? "tak" : "nie"; //debug
//    std::cout << doCouta2 << '\n'; //debug

    std::cout << testBCR.getDecimalValue() << " to " << testBCR << std::endl
              << testBCRoperators.getDecimalValue() << std::endl;
    return 0;
}