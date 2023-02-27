#ifndef DEMRANDOMPROTOTYPE_H
#define DEMRANDOMPROTOTYPE_H

#include <vector>
#include <random>

/*!
\author David "Dawn" Estes McKnight
\date 4 November 2016
Methods for generating random ints and characters
*/

class DEMRandom
{
    //Object used for generating random elements
    static std::default_random_engine generator;
    
    
    //!<Generates a random integer between the values of minimum and maximum 
    static int randomInt(int minimum, int maximum)
    {
        std::uniform_int_distribution<int> distribution(minimum, maximum);
        return distribution(generator);
    }
     
    //!<Generates a random character with an ascii value between those of minimum and maximum
    static int randomChar(char minimum, char maximum)
    {
        std::uniform_int_distribution<int> distribution((int)minimum, (int)maximum);
        return (char)distribution(generator);
    }   
    
    //!<Generates a vector of numElements random integers between the values of minimum and maximum
    static std::vector<int> randomIntegerVector(int numElements, int minimum, int maximum)
    {
        std::uniform_int_distribution<int> distribution(minimum, maximum);
        
        std::vector<int> randomIntegers(numElements);
        
        for (int i=0; i<randomIntegers.size(); i++)
        {
            randomIntegers[i] = distribution(generator);
        }
        
        return randomIntegers;
     
    }
    
    //!<Generates a vector of numElements random characters with ascii values between those of minimum and maximum
    static std::vector<char> randomCharacterVector(int numElements, char minimum, char maximum)
    {
        std::uniform_char_distribution<char> distribution((int)minimum, (int)maximum);
        
        std::vector<char> randomCharacters(numElements);
        
        for(int i=0; i<randomCharacters.size(); i++)
        {
            randomCharacters[i] = (char)distribution(generator);
        }
        
        return randomCharacters;
        
    }
}

#endif