#include <iostream>
#include "binaryCodedRepresentation.h"
#include <string>
#include "tests.h"

int main()
{
    /* FIRST ARG FOR BASE, SECOND FOR BITS PER NUMBER */
    if( executeTests() )
        std::cout << "Tests passed." << std::endl;
    else
        std::cout << "Tests failed." << std::endl;

    return 0;
}