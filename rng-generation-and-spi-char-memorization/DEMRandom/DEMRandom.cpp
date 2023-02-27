#ifndef DEMRANDOM_CPP
#define DEMRANDOM_CPP
#include "DEMRandom.h"

/*!
\author David "Dawn" Estes McKnight
\date 6 November 2016
*/

DEMRandomLegacy::DEMRandomLegacy(uint32_t seed)
{
    _seed=seed;
}

//!<Generates a random integer between the values of minimum and maximum 
int DEMRandomLegacy::randInt(uint16_t minimum, uint16_t maximum)
{
    _seed=(_seed*_multiplier)%_groupOrder;
    return _seed%(maximum-minimum+1)+minimum;
}
 
//!<Generates a random character with an ascii value between those of minimum and maximum
int DEMRandomLegacy::randChar(char minimum, char maximum)
{
    return (char)randInt((uint16_t)minimum, (uint16_t)maximum);
}   

//!<Generates a vector of numElements random integers between the values of minimum and maximum
std::vector<int> DEMRandomLegacy::randInts(int numElements, uint16_t minimum, uint16_t maximum)
{    
    std::vector<int> randomIntegers(numElements);
    
    for (int i=0; i<randomIntegers.size(); i++)
    {
        randomIntegers[i] = randInt(minimum, maximum);
    }
    
    return randomIntegers;
 
}

//!<Generates a vector of numElements random characters with ascii values between those of minimum and maximum
std::vector<char> DEMRandomLegacy::randChars(int numElements, char minimum, char maximum)
{    
    std::vector<char> randomCharacters(numElements);
    
    for(int i=0; i<randomCharacters.size(); i++)
    {
        randomCharacters[i] = randChar(minimum, maximum);
    }
    
    return randomCharacters;
    
}
#endif