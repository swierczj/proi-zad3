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
    void convertToBinary(char);
public:
    BinaryCodedRepresentation(const std::string& number = "0");
};

/* --------- TEMPLATE METHODS IMPLEMENTATION --------- */

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>::BinaryCodedRepresentation(const std::string& number)
{
    if( !isInputCorrect(number) )
        throw std::runtime_error("incorrect number given");
    systemBase = numeral_system;
    bitsPerDigit = bits_per_digit;
    originalRepresentation = number;
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
    return static_cast<int>( floor( log2(numeral_system) ) ) + 1;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::isStringCorrect(const std::string& number)
{
    for( char i : number ) //for every char in given string
    {
        if( !isalnum(i) || !isCharacterInRange(i) ) //check if it's alphanumeric and if it's available character
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
            return character < numeral_system + DISTANCE_BETWEEN_BASE_AND_LAST_DIGIT; //return for systems containing only digits
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
    binaryRepresentation = new int*[width]; // array of pointers for every digit

    for(int i = 0; i < width; i++) //matrix creation
    {
        binaryRepresentation[i] = new int[bitsPerDigit];
    }

    fillBinaryCodedArray(width); //filling array with proper digits
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
void BinaryCodedRepresentation<numeral_system, bits_per_digit>::fillBinaryCodedArray()
{
    for( char ch : originalRepresentation )
    {
        convertToBinary(ch);
    }
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
void BinaryCodedRepresentation<numeral_system, bits_per_digit>::convertToBinary(char ch)
{
    if( isdigit(ch) ) //get number nevertheless if number or letter
}


#endif //PROI2_BINARYCODEDREPRESENTATION_H
