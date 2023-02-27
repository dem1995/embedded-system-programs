#ifndef DEMRANDOM_H
#define DEMRANDOM_H
#include <vector>
#include <stdint.h>

/*!
\author David "Dawn" Estes McKnight
\date 4 November 2016
Object with methods for generating random ints and characters without using nice C++ 11 features
*/

class DEMRandomLegacy
{
    public:
    DEMRandomLegacy(uint32_t seed);             //!<Constructs a DEMRandomLegacy object whose methods use the given seed
    
    int randInt(uint16_t minimum, uint16_t maximum);      //!<Generates a random integer between the values of minimum and maximum 
     
    int randChar(char minimum, char maximum);             //!<Generates a random character with a casted value between those of minimum and maximum
    
    std::vector<int> randInts(int numElements, uint16_t minimum, uint16_t maximum);        //!<Generates a vector of numElements random integers between the values of minimum and maximum
    
    std::vector<char> randChars(int numElements, char minimum, char maximum);   //!<Generates a vector of numElements random characters with int-casted values between those of minimum and maximum
    
    private:
    uint16_t _seed;                             //The starting point in the cyclic group we'll use for generating random numbers
    const uint32_t _groupOrder = 2147483647;    //The order of the underlying cyclic group we'll be using to generate random numbers. We'll have it be the 2^31-1, the largest signed int and, conveneniently, a prime number (the eighth Mersenne prime, in fact)
    const uint32_t _multiplier = 48271;         //The multiplier we'll use.
};

#endif