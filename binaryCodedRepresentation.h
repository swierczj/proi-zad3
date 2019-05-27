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

//forward declarations
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
    int getCharactersDecimalValue(char);
    std::string getNumeralSystemRepresentationFromValue(int);
    std::string reduceGivenNumber(const std::string&);
    void deleteBinaryRepArrays();
    void assignObjectToNumber(const std::string&);
    char getCharacterFromDecimalValue(int);
    int getStringDecimalValue(const std::string&);
public:
    explicit BinaryCodedRepresentation(const std::string& number = "0");
    explicit BinaryCodedRepresentation(unsigned int number = 0) : BinaryCodedRepresentation( getNumeralSystemRepresentationFromValue(number) ) {}; //explicit due to implicit conversion from const char* to unsigned int
    BinaryCodedRepresentation(const char* number = "0") : BinaryCodedRepresentation( std::string(number) ) {}; //not marked explicit due to above fact(surprising behaviour)
    BinaryCodedRepresentation(const BinaryCodedRepresentation&);
    BinaryCodedRepresentation(BinaryCodedRepresentation&&) noexcept;
    ~BinaryCodedRepresentation();

    unsigned int getDecimalValue() const;

    BinaryCodedRepresentation& operator=(const BinaryCodedRepresentation&);
    BinaryCodedRepresentation& operator=(BinaryCodedRepresentation&&) noexcept;
    BinaryCodedRepresentation& operator=(unsigned int);
    BinaryCodedRepresentation& operator=(const std::string&);
    BinaryCodedRepresentation& operator=(const char* objCharPtr) { return( this -> operator=( std::string(objCharPtr) ) ); }

    bool operator==(const BinaryCodedRepresentation&) const;
    bool operator==(int) const;
    bool operator==(const std::string&) const;
    bool operator==(const char* rhsCharPtr) const { return( this -> operator==( std::string(rhsCharPtr) ) ); }
    friend bool operator==(int lhsInt, const BinaryCodedRepresentation& rhsBCR) { return rhsBCR.operator==(lhsInt); }
    friend bool operator==(const std::string& lhsString, const BinaryCodedRepresentation& rhsBCR) { return rhsBCR.operator=(lhsString); }
    friend bool operator==(const char* lhsCharPtr, const BinaryCodedRepresentation& rhsBCR) { return rhsBCR.operator=(lhsCharPtr); }

    bool operator!=(const BinaryCodedRepresentation&) const;
    bool operator!=(int) const;
    bool operator!=(const std::string&) const;
    bool operator!=(const char* rhsCharPtr) const { return( this -> operator!=( std::string(rhsCharPtr) ) ); }
    friend bool operator!=(int lhsInt, const BinaryCodedRepresentation& rhsBCR) { return !( rhsBCR.operator==(lhsInt) ); }
    friend bool operator!=(const std::string& lhsString, const BinaryCodedRepresentation& rhsBCR) { return !( rhsBCR.operator=(lhsString) ); }
    friend bool operator!=(const char* lhsCharPtr, const BinaryCodedRepresentation& rhsBCR) { return !( rhsBCR.operator==(lhsCharPtr) ); }

    bool operator>(const BinaryCodedRepresentation&) const;
    bool operator>(int) const;
    bool operator>(const std::string&) const;
    bool operator>(const char* rhsCharPtr) const { return( this -> operator>( std::string(rhsCharPtr) ) ); }
    friend bool operator>(int lhsInt, const BinaryCodedRepresentation& rhsBCR) { return ( !( lhsInt == rhsBCR ) && !( rhsBCR > lhsInt ) ); } //probably ok
    friend bool operator>(const std::string& lhsString, const BinaryCodedRepresentation& rhsBCR) { return ( !( lhsString == rhsBCR) && !( rhsBCR > lhsString ) ); }
    friend bool operator>(const char* lhsCharPtr, const BinaryCodedRepresentation& rhsBCR) { return( std::string(lhsCharPtr) > rhsBCR ); }

    bool operator<(const BinaryCodedRepresentation&) const;
    bool operator<(int) const;
    bool operator<(const std::string&) const;
    bool operator<(const char* rhsCharPtr) const { return( this -> operator<( std::string(rhsCharPtr) ) ); }
    friend bool operator<(int lhsInt, const BinaryCodedRepresentation& rhsBCR) { return( !( rhsBCR < lhsInt ) && !( lhsInt == rhsBCR ) ); }
    friend bool operator<(const std::string& lhsString, const BinaryCodedRepresentation& rhsBCR) { return ( !( lhsString == rhsBCR) && !( rhsBCR < lhsString ) ); }
    friend bool operator<(const char* lhsCharPtr, const BinaryCodedRepresentation& rhsBCR) { return std::string(lhsCharPtr) < rhsBCR; }

    bool operator>=(const BinaryCodedRepresentation& rhs) const { return( this -> operator>(rhs) || this -> operator==(rhs) ); }
    bool operator>=(int rhsInt) const { return( this -> operator>(rhsInt) || this -> operator==(rhsInt) ); }
    bool operator>=(const std::string& rhsString) const { return( this -> operator>(rhsString) || this -> operator==(rhsString) ); }
    bool operator>=(const char* rhsCharPtr) const { return( this -> operator>=( std::string(rhsCharPtr) ) ); }
    friend bool operator>=(int lhsInt, const BinaryCodedRepresentation& rhsBCR) { return( lhsInt > rhsBCR || lhsInt == rhsBCR ); }
    friend bool operator>=(const std::string& lhsString, const BinaryCodedRepresentation& rhsBCR) { return( lhsString > rhsBCR || lhsString == rhsBCR ); }
    friend bool operator>=(const char* lhsCharPtr, const BinaryCodedRepresentation& rhsBCR) { return( std::string(lhsCharPtr) >= rhsBCR ); }

    bool operator<=(const BinaryCodedRepresentation& rhs) const { return( this -> operator<(rhs) || this -> operator==(rhs) ); }
    bool operator<=(int rhsInt) const { return( this -> operator<(rhsInt) || this -> operator==(rhsInt) ); }
    bool operator<=(const std::string& rhsString) const { return( this -> operator<(rhsString) || this -> operator==(rhsString) ); }
    bool operator<=(const char* rhsCharPtr) const { return( this -> operator<=( std::string(rhsCharPtr) ) ); }
    friend bool operator<=(int lhsInt, const BinaryCodedRepresentation& rhsBCR) { return( lhsInt < rhsBCR || lhsInt == rhsBCR ); }
    friend bool operator<=(const std::string& lhsString, const BinaryCodedRepresentation& rhsBCR) { return( lhsString < rhsBCR || lhsString == rhsBCR ); }
    friend bool operator<=(const char* lhsCharPtr, const BinaryCodedRepresentation& rhsBCR) { return( std::string(lhsCharPtr) <= rhsBCR ); }

    BinaryCodedRepresentation& operator+=(const BinaryCodedRepresentation&);
    BinaryCodedRepresentation& operator+=(int);
    BinaryCodedRepresentation& operator+=(const std::string&);
    BinaryCodedRepresentation& operator+=(const char* rhsCharPtr) { return( this -> operator+=( std::string(rhsCharPtr) ) ); }

    BinaryCodedRepresentation& operator-=(const BinaryCodedRepresentation&);
    BinaryCodedRepresentation& operator-=(int);
    BinaryCodedRepresentation& operator-=(const std::string&);
    BinaryCodedRepresentation& operator-=(const char* rhsCharPtr) { return( this -> operator-=( std::string(rhsCharPtr) ) ); }

    BinaryCodedRepresentation& operator*=(const BinaryCodedRepresentation&);
    BinaryCodedRepresentation& operator*=(int);
    BinaryCodedRepresentation& operator*=(const std::string&);
    BinaryCodedRepresentation& operator*=(const char* rhsCharPtr) { return( this -> operator*=( std::string(rhsCharPtr) ) ); }

    BinaryCodedRepresentation& operator/=(const BinaryCodedRepresentation&);
    BinaryCodedRepresentation& operator/=(int);
    BinaryCodedRepresentation& operator/=(const std::string&);
    BinaryCodedRepresentation& operator/=(const char* rhsCharPtr) { return( this -> operator/=( std::string(rhsCharPtr) ) ); }

    BinaryCodedRepresentation& operator++(); //prefix
    BinaryCodedRepresentation& operator--();

    const BinaryCodedRepresentation operator++(int); //postfix
    const BinaryCodedRepresentation operator--(int);

    friend BinaryCodedRepresentation operator+(BinaryCodedRepresentation lhs, const BinaryCodedRepresentation& rhs) { lhs += rhs; return lhs; }
    friend BinaryCodedRepresentation operator+(BinaryCodedRepresentation lhs, int rhsInt) { lhs += rhsInt; return lhs; }
    friend BinaryCodedRepresentation operator+(int lhsInt, const BinaryCodedRepresentation& rhs) { return( operator+(rhs, lhsInt) ); }
    friend BinaryCodedRepresentation operator+(BinaryCodedRepresentation lhs, const std::string& rhsString) { int decimalValue = lhs.getStringDecimalValue(rhsString); return lhs += decimalValue; }
    friend BinaryCodedRepresentation operator+(const std::string& lhsString, BinaryCodedRepresentation rhs) { return rhs + lhsString; }
    friend BinaryCodedRepresentation operator+(const char* lhsCharPtr, BinaryCodedRepresentation& rhs) { return operator+( std::string(lhsCharPtr), rhs ); }
    friend BinaryCodedRepresentation operator+(BinaryCodedRepresentation lhs, const char* rhsCharPtr) { return operator+( lhs, std::string(rhsCharPtr) ); }

    /* TODO */
    friend BinaryCodedRepresentation operator-(BinaryCodedRepresentation lhs, const BinaryCodedRepresentation& rhs) { lhs += rhs; return lhs; }
    friend BinaryCodedRepresentation operator-(BinaryCodedRepresentation lhs, int rhsInt) { lhs += rhsInt; return lhs; }
    friend BinaryCodedRepresentation operator-(int lhsInt, const BinaryCodedRepresentation& rhs) { return( operator+(rhs, lhsInt) ); }
    friend BinaryCodedRepresentation operator-(BinaryCodedRepresentation lhs, const std::string& rhsString) { int decimalValue = lhs.getStringDecimalValue(rhsString); return lhs += decimalValue; }
    friend BinaryCodedRepresentation operator-(const std::string& lhsString, BinaryCodedRepresentation rhs) { return rhs + lhsString; }
    friend BinaryCodedRepresentation operator-(const char* lhsCharPtr, BinaryCodedRepresentation& rhs) { return operator+( std::string(lhsCharPtr), rhs ); }
    friend BinaryCodedRepresentation operator-(BinaryCodedRepresentation lhs, const char* rhsCharPtr) { return operator+( lhs, std::string(rhsCharPtr) ); }

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
    if( !isInputCorrect(other.originalRepresentation) ) //compare with this object requirements, maybe unnecessary
        throw std::runtime_error("incorrect number given or template args don't meet requirements in copy ctor");
    systemBase = numeral_system;
    bitsPerDigit = bits_per_digit;
    originalRepresentation = reduceGivenNumber(other.originalRepresentation);

    setBinaryRepresentation();
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>::BinaryCodedRepresentation(BinaryCodedRepresentation&& other) noexcept
{
    /*if( !isInputCorrect(other.originalRepresentation) ) //compare with this object requirements, maybe unnecessary
        throw std::runtime_error("incorrect number given or template args don't meet requirements in copy rRef ctor");*/
    systemBase = numeral_system;
    bitsPerDigit = bits_per_digit;
    originalRepresentation = reduceGivenNumber(other.originalRepresentation); //maybe unnecessary
    setBinaryRepresentation();

    //everything set now clear the other object
    other.deleteBinaryRepArrays();

    other.systemBase = 0;
    other.originalRepresentation.clear();
    other.bitsPerDigit = 0;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>::~BinaryCodedRepresentation()
{
    deleteBinaryRepArrays();
    systemBase = 0;
    originalRepresentation.clear();
    bitsPerDigit = 0;
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
    binaryRepresentation = new int*[width]; // array of pointers for every digit

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
        decimalToConvert = getCharactersDecimalValue( originalRepresentation.at(i) );
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
int BinaryCodedRepresentation<numeral_system, bits_per_digit>::getCharactersDecimalValue(char ch)
{
    int retValue = 0;
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
std::string BinaryCodedRepresentation<numeral_system, bits_per_digit>::getNumeralSystemRepresentationFromValue(int to_convert)
{
    if( to_convert < 0 )
        return std::string("-"); //non alphanumeric character

    const int bitsPerGivenNumber = static_cast<int>( floor( log( to_convert ) / log( numeral_system ) ) + 1 );
    int intsBuffer[bitsPerGivenNumber];
    for( int i = 0; i < bitsPerGivenNumber; ++i )
    {
        intsBuffer[i] = to_convert % numeral_system;
        if( to_convert >= 1 )
            to_convert = to_convert / numeral_system;
        //else do nothing it's already 0
    }

    std::string result; //empty string
    for( int i = bitsPerGivenNumber - 1; i >= 0; --i )
    {
        result.push_back( getCharacterFromDecimalValue( intsBuffer[i] ) );
    }

    return result;
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
unsigned int BinaryCodedRepresentation<numeral_system, bits_per_digit>::getDecimalValue() const
{
    double retValue = 0; //double since pow()
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

template <unsigned long numeral_system, unsigned long bits_per_digit>
void BinaryCodedRepresentation<numeral_system, bits_per_digit>::deleteBinaryRepArrays()
{
    for( int i = 0; i < originalRepresentation.size(); ++i )
    {
        delete[] binaryRepresentation[i];
        binaryRepresentation[i] = nullptr;
    }

    delete[] binaryRepresentation;
    binaryRepresentation = nullptr;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
void BinaryCodedRepresentation<numeral_system, bits_per_digit>::assignObjectToNumber(const std::string& number)
{
    deleteBinaryRepArrays();
    //system base and bitsPerDigit remains the same
    //if assigning to other existing object then it's ensured that number must be correct
    originalRepresentation = number;
    setBinaryRepresentation();
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
char BinaryCodedRepresentation<numeral_system, bits_per_digit>::getCharacterFromDecimalValue(int intValue)
{
    if( intValue < 10 )
        return '0' + intValue;
    else if( intValue >= 10 && intValue < MAX_NUMERAL_SYSTEM )
    {
        intValue = intValue - 10; //it's an offset
        return 'a' + intValue;
    }
    else
        return '-'; //useful for debug
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
int BinaryCodedRepresentation<numeral_system, bits_per_digit>::getStringDecimalValue(const std::string& toCalculate)
{
    int retVal = 0;
    std::string temp;

    if( toCalculate.at(0) == '-' )
        temp = toCalculate.substr(1);
    else
        temp = toCalculate;

    if( !( isStringCorrect(temp) ) )
        throw std::runtime_error( "unable to calculate string value in +=" );

    for( int i = 0; i < temp.size(); ++i )
        retVal = retVal + ( getCharactersDecimalValue( temp.at(i) ) * pow( numeral_system, temp.size() - i - 1 ) );

    if( temp.size() == toCalculate.size() - 1 ) //if the '-' sign was discarded
        return -retVal;
    return retVal;
}

/* -------------- OPERATORS -------------- */
template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator=(
    const BinaryCodedRepresentation& rhs)
{
    if(this != &rhs && originalRepresentation != rhs.originalRepresentation) //if two BCNums are equal then don't copy
        assignObjectToNumber( rhs.originalRepresentation );
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator=(
    BinaryCodedRepresentation&& rhs) noexcept
{
    if(this != &rhs && originalRepresentation != rhs.originalRepresentation) //if two BCNums are equal then don't copy
    {
        assignObjectToNumber(rhs.originalRepresentation);

        rhs.deleteBinaryRepArrays();
        rhs.systemBase = 0;
        rhs.originalRepresentation.clear();
        rhs.bitsPerDigit = 0;
    }
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator=(unsigned int numberInt)
{
    BinaryCodedRepresentation<numeral_system, bits_per_digit> temp(numberInt); //not most efficient
    *this = temp;
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator=(const std::string& numberString)
{
    BinaryCodedRepresentation<numeral_system, bits_per_digit> temp(numberString); //not most efficient too
    *this = temp;
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator==(const BinaryCodedRepresentation& rhs) const
{
    return this -> getDecimalValue() == rhs.getDecimalValue();
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator==(int rhsInt) const
{
    if( rhsInt < 0 )
        return false;
    return this -> getDecimalValue() == rhsInt;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator==(const std::string& rhsString) const
{
    if( rhsString.at(0) == '-' )
        return false;
    BinaryCodedRepresentation<numeral_system, bits_per_digit> temp(rhsString);
    return *this == temp;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator!=(const BinaryCodedRepresentation& rhs) const
{
    return !( this -> operator==(rhs) );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator!=(int rhsInt) const
{
    return !( this -> operator==(rhsInt) );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator!=(const std::string& rhsString) const
{
    return !( this -> operator==(rhsString) );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator>(const BinaryCodedRepresentation& rhs) const
{
    return this -> getDecimalValue() > rhs.getDecimalValue();
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator>(int rhsInt) const
{
    if( rhsInt < 0 ) //due to implicit conversion to unsigned
        return true;
    return this -> getDecimalValue() > rhsInt;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator>(const std::string& rhsString) const
{
    //unable to create object, then return true and catch except

    if( rhsString.at(0) == '-' )
        return true;
    try
    {
        BinaryCodedRepresentation<numeral_system, bits_per_digit> errorCheck(rhsString);
    }
    catch(std::runtime_error& err)
    {
        std::cout << "unable to compare two numbers";
    }
    BinaryCodedRepresentation<numeral_system, bits_per_digit> temp(rhsString);
    return this -> operator>(temp);
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator<(const BinaryCodedRepresentation& rhs) const
{
    return ( !( this -> operator>(rhs) ) && !( this -> operator==(rhs) ) );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator<(int rhsInt) const
{
    return ( !( this -> operator>(rhsInt) ) && !( this -> operator==(rhsInt) ) );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
bool BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator<(const std::string& rhsString) const
{
    return ( !( this -> operator>(rhsString) ) && !( this -> operator==(rhsString) ) );
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator+=(const BinaryCodedRepresentation& rhs)
{
    auto resultDecimalValue = this -> getDecimalValue() + rhs.getDecimalValue();
    this -> operator=(resultDecimalValue);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator+=(int rhsInt)
{
    int resultDecimalValue = this -> getDecimalValue() + rhsInt;
    if( resultDecimalValue < 0 )
        throw std::out_of_range("operator +=(int), trying to make BC number negative");
    this -> operator=(resultDecimalValue);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator+=(const std::string& rhsString)
{
    this -> operator+=( getStringDecimalValue(rhsString) ); //call int operator
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator-=(const BinaryCodedRepresentation& rhs)
{
    if( this -> getStringDecimalValue() < rhs.getDecimalValue() )
        throw std::out_of_range( "trying to make BC number negative in -=" );

    auto resultDecimalValue = this -> getDecimalValue() - rhs.getDecimalValue();
    this -> operator=(resultDecimalValue);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator-=(int rhsInt)
{
    if( rhsInt < 0 )
    {
        int absValue = -rhsInt;
        return this -> operator+=(absValue);
    }

    if( this -> getDecimalValue() < rhsInt )
        throw std::out_of_range( "trying to make BC number negative in -=" );

    auto resultDecimalValue = this -> getDecimalValue() - rhsInt;

    this -> operator=(resultDecimalValue);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator-=(const std::string& rhsString)
{
    this -> operator-=( getStringDecimalValue(rhsString) ); //call int operator
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator*=(const BinaryCodedRepresentation& rhs)
{
    auto newValue = this -> getDecimalValue() * rhs.getDecimalValue();
    this -> operator=(newValue);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator*=(int rhsInt)
{
    if( rhsInt < 0 )
        throw std::out_of_range( "trying to make BC number negative in *=" );

    auto resultDecimalValue = this -> getDecimalValue() * rhsInt;

    this -> operator=(resultDecimalValue);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator*=(const std::string& rhsString)
{
    this -> operator*=( getStringDecimalValue(rhsString) ); //call int operator
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator/=(const BinaryCodedRepresentation& rhs)
{
    if( rhs.getDecimalValue() == 0 )
        throw std::out_of_range( "trying to divide by 0 in /=");

    auto newValue = this -> getDecimalValue() / rhs.getDecimalValue();
    this -> operator=(newValue);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator/=(int rhsInt)
{
    if( rhsInt <= 0 )
        throw std::out_of_range( "trying to divide by 0 or negative number in /=");

    auto newValue = this -> getDecimalValue() / rhsInt;
    this -> operator=(newValue);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator/=(const std::string& rhsString)
{
    this -> operator/=( getStringDecimalValue(rhsString) ); //call int operator
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator++()
{
    this -> operator+=(1);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator--()
{
    this -> operator-=(1);
    return *this;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
const BinaryCodedRepresentation<numeral_system, bits_per_digit> BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator++(int)
{
    BinaryCodedRepresentation result(*this);
    ++(*this);
    return result;
}

template <unsigned long numeral_system, unsigned long bits_per_digit>
const BinaryCodedRepresentation<numeral_system, bits_per_digit> BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator--(int)
{
    BinaryCodedRepresentation result(*this);
    --(*this);
    return result;
}

/*template <unsigned long numeral_system, unsigned long bits_per_digit>
BinaryCodedRepresentation<numeral_system, bits_per_digit>& BinaryCodedRepresentation<numeral_system, bits_per_digit>::operator=(const char* numberLiteral)
{
    operator=( std::string(numberLiteral) );
    return *this;
}
*/
/* -------------- FRIEND FUNCTIONS --------------
 * Majority of friend functions are named like member methods so I decided to put their definitions in class itself in order
 * to prevent issues with templates. These which aren't error prone are defined below.
 */

/*
template <unsigned long numeral_system, unsigned long bits_per_digit>
bool operator==(int lhsInt, const BinaryCodedRepresentation<numeral_system, bits_per_digit>& rhsBCR)
{
    return rhsBCR.operator=(lhsInt);
}
*/
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
