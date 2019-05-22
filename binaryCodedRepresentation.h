#ifndef PROI2_BINARYCODEDREPRESENTATION_H
#define PROI2_BINARYCODEDREPRESENTATION_H
#define MAX_NUMERAL_SYSTEM 36 //alphanuemerical chars, non-case sensitive
#define MIN_NUMERAL_SYSTEM 2 //unary system is useless
#define DISTANCE_BETWEEN_BASE_AND_LAST_CHARACTER 86 //used for lower case
#define DISTANCE_BETWEEN_BASE_AND_LAST_DIGIT 47
#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
//#include <algorithm>
#include <cctype>

template <unsigned long numeral_system, unsigned long bits_per_digit>
class BinaryCodedRepresentation;

template <unsigned long numeral_system, unsigned long bits_per_digit>
std::ostream& operator<<(std::ostream&, const BinaryCodedRepresentation<numeral_system, bits_per_digit>&);


template <unsigned long numeral_system, unsigned long bits_per_digit>
class BinaryCodedRepresentation
{
private:
    std::string originalRepresentation;
    int** binaryRepresentation;
    long systemBase;
    long bitsPerDigit;
    bool isInputCorrect(const std::string&);
    bool areTemplateArgumentsCorrect();
    bool isBaseCorrect();
    bool isNumberOfBitsCorrect();
    int getMinimumNumberOfBitsPerDigit();
    bool isStringCorrect(const std::string&);
    bool isCharacterInRange(char);
    bool isLetterInRange(char);
    void setBinaryRepresentation();
    void fillBinaryCodedArray();
    void fillSlotAtGivenPosition(int, int);
    int getDecimalRepresentation(char);
    std::string reduceGivenNumber(const std::string&);
public:
    BinaryCodedRepresentation(const std::string& number = "0");
    BinaryCodedRepresentation(unsigned int number = 0) : BinaryCodedRepresentation( std::to_string(number) ) {};
    BinaryCodedRepresentation(const BinaryCodedRepresentation&);
    unsigned int getDecimalValue();
    friend std::ostream& operator<< <numeral_system, bits_per_digit>(std::ostream&, const BinaryCodedRepresentation&);

};

/* --------- TEMPLATE METHODS IMPLEMENTATION --------- */

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>::BinaryCodedRepresentation(const std::string& number)
{
    if( !isInputCorrect(number) )
        throw std::runtime_error("incorrect number given or template args don't meet requirements");
    systemBase = numeral_system;
    bitsPerDigit = bits_per_digit;
    originalRepresentation = reduceGivenNumber(number);

    setBinaryRepresentation();
}

/*template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>::BinaryCodedRepresentation(unsigned int number)
: BinaryCodedRepresentation( std::to_string(number) )
{
    worked
}
*/

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>::BinaryCodedRepresentation(const BinaryCodedRepresentation& other)
{
    if( !isInputCorrect(other.originalRepresentation) ) //compare with this object requirements
        throw std::runtime_error("incorrect number given or template args don't meet requirements in copy ctor");
    systemBase = numeral_system;
    bitsPerDigit = bits_per_digit;
    originalRepresentation = reduceGivenNumber(other.originalRepresentation);

    setBinaryRepresentation();
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::isInputCorrect(const std::string& number)
{
    return( areTemplateArgumentsCorrect() && isStringCorrect(number) );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::areTemplateArgumentsCorrect()
{
    return( isBaseCorrect() && isNumberOfBitsCorrect() );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::isBaseCorrect()
{
    return( numeral_system <= MAX_NUMERAL_SYSTEM && numeral_system >= MIN_NUMERAL_SYSTEM );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::isNumberOfBitsCorrect()
{
    return( bits_per_digit >= getMinimumNumberOfBitsPerDigit() );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
int BinaryCodedRepresentation<numeral_system, bits_per_digit>::getMinimumNumberOfBitsPerDigit()
{
    return static_cast<int>( floor( log2( numeral_system - 1 ) ) ) + 1; //was log2(numeral_system)+1 but it's needed to calculate number of bits for maximum number in given system
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::isStringCorrect(const std::string& number)
{
    for( char ch : number ) //for every char in given string
    {
        if( !isalnum(ch) || !isCharacterInRange(ch) ) //check if it's alphanumeric and if it's available character
            return false;
    }
    return true;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::isCharacterInRange(char character)
{
    if( numeral_system <= 10 ) //only digits can appear
    {
        if( isdigit( static_cast<unsigned char>(character) ) )
        {
            /*auto testNumSys = numeral_system + DISTANCE_BETWEEN_BASE_AND_LAST_DIGIT;
            int testChar = character;*/
            return character <= numeral_system + DISTANCE_BETWEEN_BASE_AND_LAST_DIGIT; //return for systems containing only digits
        }

        return false; //if numeral system but not a digit found then return false
    }
    else
    {
        if( !isdigit( static_cast<unsigned char>(character) ) ) //if letter
            return isLetterInRange(character); //check if temp has correct value

        return true; //if digit then it's true
    }
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::isLetterInRange(char ch)
{
    ch = static_cast<char>( tolower(static_cast<unsigned char>(ch) ) );
    return numeral_system + DISTANCE_BETWEEN_BASE_AND_LAST_CHARACTER >= ch; //hopefully it works, e.g base is 11 then last char is 'a'
    //and 'a' number in ascii is 97, for 'b' and greater it returns false
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
void BinaryCodedRepresentation<numeral_system, bits_per_digit>::setBinaryRepresentation()
{
    auto width = originalRepresentation.size();
    binaryRepresentation = new int*[width]; // array of pointers for every digit /*TODO PREVENT LEAKS */

    for(int i = 0; i < width; i++) //matrix creation
    {
        binaryRepresentation[i] = new int[bitsPerDigit];
    }
    fillBinaryCodedArray(); //filling array with proper digits
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
void BinaryCodedRepresentation<numeral_system, bits_per_digit>::fillBinaryCodedArray()
{
    int decimalToConvert;
    for( int i = 0; i < originalRepresentation.size(); ++i )
    {
        decimalToConvert = getDecimalRepresentation( originalRepresentation.at(i) );
        fillSlotAtGivenPosition(decimalToConvert, i);
    }
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
void BinaryCodedRepresentation<numeral_system, bits_per_digit>::fillSlotAtGivenPosition(int decimal, int position)
{
    //fill in such way that the index of array is equivalent to power of 2
    for( int i = 0; i < bitsPerDigit; ++i )
    {
        binaryRepresentation[position][i] = decimal % 2;
        if( decimal >= 1 )
            decimal = decimal / 2;
        //else, do nothing it's already 0
    }
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
int BinaryCodedRepresentation<numeral_system, bits_per_digit>::getDecimalRepresentation(char ch)
{
    int retValue;
    if( isdigit( static_cast<unsigned char>(ch) ) )
        retValue = ch - ( DISTANCE_BETWEEN_BASE_AND_LAST_DIGIT + 1 );
    else
    {
        ch = static_cast<char>( tolower(static_cast<unsigned char>(ch) ) );
        retValue = ch - ( DISTANCE_BETWEEN_BASE_AND_LAST_CHARACTER + 1 );
    }
    return retValue;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
std::string BinaryCodedRepresentation<numeral_system, bits_per_digit>::reduceGivenNumber(const std::string& to_reduce)
{
    if( to_reduce.at(0) != '0' || to_reduce.size() == 1 )
        return to_reduce;

    int zerosCounter = 0;
    for( int i = 0; i < to_reduce.size(); ++i)
    {
        if( to_reduce.at(i) != '0' || i == to_reduce.size() - 1 ) //second cond. may be unnecessary, put it in for break cond.(?)
            break;
        ++zerosCounter;
    }

    return std::string( to_reduce.substr( zerosCounter ) );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
unsigned int BinaryCodedRepresentation<numeral_system, bits_per_digit>::getDecimalValue()
{
    double retValue = 0;
    double slotValue = 0;
    for( int i = 0; i < originalRepresentation.size(); ++i )
    {
        for(int j = 0; j < bitsPerDigit; ++j)
        {
            slotValue = slotValue + binaryRepresentation[i][j] * pow(2, j); //will be ok
        }
        retValue = retValue + slotValue * pow( systemBase, originalRepresentation.size() - i - 1 ); //ogRep.size()-i-1 since array indexes are opposite to powers
        slotValue = 0;
    }
    return static_cast<unsigned int> (retValue);
}

/* -------------- FRIEND FUNCTIONS -------------- */
template <unsigned long numeral_system, unsigned long bits_per_digit>
std::ostream& operator<<(std::ostream& os, const BinaryCodedRepresentation<numeral_system, bits_per_digit>& object)
{
    for( int i = 0; i < object.originalRepresentation.size(); ++i )
    {
        for ( int j = object.bitsPerDigit - 1; j >= 0; --j )
            os << object.binaryRepresentation[i][j];
        os << " ";
    }
    return os;
}

#endif //PROI2_BINARYCODEDREPRESENTATION_H
