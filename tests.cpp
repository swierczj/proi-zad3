#include "binaryCodedRepresentation.h"
#include "tests.h"
#include <stdexcept>
#include <iostream>

bool executeTests()
{
    return(  negativeValueInitTest()
             && compoundAssignmentPlusOperatorTest()
             && compoundAssignmentMinusOperatorTest()
             && compoundAssignmentMultiplyOperatorTest()
             && compoundAssignmentDivideOperatorTest()
             && binaryArithmeticPlusOperatorTest()
             && binaryArithmeticMinusOperatorTest()
             && binaryArithmeticMultiplyOperatorTest()
             && binaryArithmeticDivideOperatorTest()
             && prefixIncDecTest()
             && postfixIncDecTest()
    );
}

bool negativeValueInitTest()
{
    try
    {
        BinaryCodedRepresentation<16, 4> test("-23");
    }
    catch(const std::runtime_error& rterr)
    {
        std::cout << "Caught: " << rterr.what() << std::endl;
        return true;
    }
}

bool compoundAssignmentPlusOperatorTest()
{
    BinaryCodedRepresentation<10, 4> b(293);
    b += 7; // int
    try
    {
        b += -301;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<10, 4> c = b;
    c += "5"; // char*, string
    try
    {
        c += "-600";
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<10, 4> a(5);
    a += b; // other BCD
    a += c;

    return ( b == 300 && c == 305 && a == 610 );
}

bool compoundAssignmentMinusOperatorTest()
{
    BinaryCodedRepresentation<13, 4> b(293);
    b -= 3; // int
    try
    {
        b -= 300;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<13, 4> c = b;
    c -= "5"; // char*, string
    try
    {
        c -= "372"; //600
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<13, 4> a(600);
    a -= b; // other BCD
    a -= c;
    try
    {
        BinaryCodedRepresentation<13, 4> x(30);
        a -= x;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    return ( b == 290 && c == 285 && a == 25 );
}

bool compoundAssignmentMultiplyOperatorTest()
{
    BinaryCodedRepresentation<20, 6> b(293);
    b *= 10; // int
    try
    {
        b *= -1;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<20, 6> c = b;
    c *= "2"; // char*, string
    try
    {
        c *= "-1";
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<20, 6> a(1);
    a *= b; // other BCD

    return ( b == 2930 && c == 5860 && a == 2930 );
}

bool compoundAssignmentDivideOperatorTest()
{
    BinaryCodedRepresentation<9, 4> b(120);
    b /= 3; // int
    try
    {
        b /= -2; //b /= 0;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<9, 4> c = b;
    c /= "3"; // char*
    try
    {
        c /= "-6";
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<9, 4> a(600);
    a /= b; // other BCD

    return ( b == 40 && c == 13 && a == 15 );
}

bool binaryArithmeticPlusOperatorTest()
{
    BinaryCodedRepresentation<3, 4> b(2);
    BinaryCodedRepresentation<3, 4> c = 11 + b; // int, symmetry provided, check
    try
    {
        b = c - 30;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    c = b + "12"; // char* //+ 5
    try
    {
        c = "-211020" + b; // -600
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<3, 4> a = b + c; // BCD

    return ( b == 2 && c == 7 && a == 9 );
}

bool binaryArithmeticMinusOperatorTest()
{
    BinaryCodedRepresentation<8, 4> b(20);
    BinaryCodedRepresentation<8, 4> c = b - 11; // int, type symmetry provided
    try
    {
        b = c - 30;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    c = "226" - b; // char* //150 -
    try
    {
        c = b - "50"; // - 40
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<8, 4> a = c - b;
    try
    {
        c = b - c;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    return ( b == 20 && c == 130 && a == 110 );
}

bool binaryArithmeticMultiplyOperatorTest()
{
    BinaryCodedRepresentation<16, 4> b(2);
    BinaryCodedRepresentation<16, 4> c = 11 * b; // int, symmetry provided
    try
    {
        b = c * (-30);
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    c = b * "5"; // char*
    try
    {
        c = "-258" * b;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<16, 4> a = b * c; // BCD

    return ( b == 2 && c == 10 && a == 20 );
}

bool binaryArithmeticDivideOperatorTest()
{
    BinaryCodedRepresentation<30, 5> b(30);
    BinaryCodedRepresentation<30, 5> c = 110 / b; // int, symmetry provided
    try
    {
        b = c / (-3);
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    c = b / "5"; // char*
    try
    {
        c = "-j0" / b; //c = "-600" / b;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    BinaryCodedRepresentation<30, 5> a = b / c; // BCD

    return ( b == 30 && c == 6 && a == 5 );
}

bool prefixIncDecTest()
{
    BinaryCodedRepresentation<7, 3> a(2);
    BinaryCodedRepresentation<7, 3> b = ++a;

    --b;
    try
    {
        BinaryCodedRepresentation<7, 3> c(static_cast<unsigned int>(0)); //ambiguous
        --c;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    return(a == 3 && b == 2);
}

bool postfixIncDecTest()
{
    BinaryCodedRepresentation<5, 3> a(2);
    BinaryCodedRepresentation<5, 3> b = a++;

    b--;
    try
    {
        BinaryCodedRepresentation<5, 3> c(static_cast<unsigned int>(0)); //ambiguous
        c--;
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Caught: " << oor.what() << std::endl;
    }

    return(a == 3 && b == 1);
}

