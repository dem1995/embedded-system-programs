#include "mbed.h" // Requires configured ARM mbed compiler
#include "DEMRandom/DEMRandom.h"
#include "DEMUtils/BouncelessTrigger.h"
#include <vector>
#include <iostream>
#include <sstream>

/*!
\author David "Dawn" Estes McKnight
\date 8 November 2016
Program for a character-memorization game on an MBED device.
*/

//Global methods and variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void addA();                    //Called when a player presses the 'A' button
void addB();                    //Called when a player presses the 'B' button
void addC();                    //Called when a player presses the 'C' button

static uint8_t CHAR_A = 0x77;   //Binary string literal for outputting to SPI to send to LED Display to display the letter 'A'
static uint8_t CHAR_B = 0x7C;   //Binary string literal for outputting to SPI to send to LED Display to display the letter 'B'
static uint8_t CHAR_C = 0x39;   //Binary string literal for outputting to SPI to send to LED Display to display the letter 'C'

vector<char> randCharVector(5); //A vector that will contain a number of randomly generated characters
int counter=0;                  //How many characters players have input as guesses
vector<char> playerInput(5);    //A vector that stores a player's guessed inputs

SPI spi(p11, p12, p13);         //SPI spi(MOSIPIN, MISOPIN, SCKPIN);
DigitalOut fs1(p14);            //Follower Select 1;

bool randCharsDisplayed=false;  //Whether the current round's randomly-generated characters have been displayed

//The main program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {
    Timer timer;                //Timer used for helping to ensure random characters are generated
    timer.start();              //Starting the seed-generating timer    
    
    Serial pc(USBTX, USBRX);    //Used for outputting information to computer terminal
    
    spi.format(8, 0);           //SPI format(numberOfBits, mode);

    //Declare trigger-inputs for player button presses ~~~~~~~~~~~~~~~~~~~~~~~~~
    BouncelessTrigger pinA = BouncelessTrigger(p29);
    BouncelessTrigger pinB = BouncelessTrigger(p28);
    BouncelessTrigger pinC = BouncelessTrigger(p27);
    
    //Attach functions to player's trigger-inputs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    pinA.attach(addA, BouncelessTrigger::OnPress);
    pinB.attach(addB, BouncelessTrigger::OnPress);
    pinC.attach(addC, BouncelessTrigger::OnPress);
    
    int numRoundsLasted=0;      //The player has lasted 0 rounds so far
    
    
    //The game loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for (double diff=1; diff!=-1; diff*=.75)
    {
        randCharsDisplayed=false;                               //At this point, this round's random characters have not been displayed
        DEMRandomLegacy randGenerator(timer.read_us());         //Feeds my random number generator the time elapsed on the timer as a seed
        randCharVector = randGenerator.randChars(5, 'A', 'C');  //Randomly generates 5 characters with ASCII values between those of 'A' and 'C', inclusive
        
        //Displaying the randomly-generated characters
        for (int i=0; i<randCharVector.size(); i++)
        {
            fs1=0;
            switch(randCharVector[i])                           //determining what character is next in the random character array and outputting it via SPI for the LED to display
            {
                case 'A': spi.write(CHAR_A); break;
                case 'B': spi.write(CHAR_B); break;
                case 'C': spi.write(CHAR_C); break;
                default:  spi.write(0xff);   break;
            }
            fs1=1;
            
            wait(diff-diff/10.0);   //Wait a moment so that people can actually tell what displayed character is. Waits the period of the character display minus some time for blanking the screen.
            
            fs1=0;
            spi.write(0x00);        //Blank the screen so that two of the same letter don't look like one of that letter
            fs1=1;
            
            wait(diff/10.0);        //Wait the remaining time
        }
        
        counter=0;          //Reset the number of characters input by the player (preparing for a few moments from now)
        randCharsDisplayed=true;//The random characters for this round have been displayed by this point

        //Player input loop (most of the logic here is handled by interrupts)
        while (counter<5)   //While fewer than 5 characters have been input by the player for this round
        {
            pc.printf("pi@%i: %c", counter, playerInput[counter]);            
        }
        
        //Blank the screen for a moment so the player knows their input was accepted
        wait(1);
        fs1=0;
        spi.write(0x00);    //Writing the binary string that will ultimately represent a blank screen on the LED display via SPI.
        fs1=1;
        wait(1);
        
        //Assume the player has passed the round. If their input does not match the random character array, then they did not pass the round.
        bool passedRound=true;
        for (int i=0; i<randCharVector.size(); i++)
        {
              if (randCharVector[i]!=playerInput[i])
              {
                  passedRound=false;
                  break;
              }
        }
        
        //If they passed the round, we'll increment the number of rounds they've lasted and continue for another game round
        if (passedRound)
            numRoundsLasted++;
        //If they did not pass the round, we'll break out of the game loop, as the game has finished, and proceed to display how many rounds they lasted
        else
            break;
            
    }
    
    //The game has ended. We will now display how many rounds the player lasted
    fs1=0;
    switch(numRoundsLasted)
    {
        case 0: spi.write(0x3f); break;
        case 1: spi.write(0x06); break;
        case 2: spi.write(0x5B); break;
        case 3: spi.write(0x4F); break;
        case 4: spi.write(0x66); break;
        case 5: spi.write(0x6D); break;
        case 6: spi.write(0x7D); break;
        case 7: spi.write(0x07); break;
        case 8: spi.write(0x7F); break;
        case 9: spi.write(0x6F); break;
        default: break;
    }
    fs1=1;
    
}

//Called when the player presses the 'A' button
void addA(){
    if(randCharsDisplayed)
    {
        if (counter<5){
            playerInput[counter]='A';   //Add an instance of the character 'A' to the player input vector
            counter++;                  //Increment the counter of how many character have been entered
            fs1=0;
            spi.write(CHAR_A);          //Output the binary string for representing 'A' on the LED display via SPI
            fs1=1;
        }
    }
}

//Called when the player presses the 'B' button
void addB(){
    if(randCharsDisplayed)
    {
        if (counter<5){
            playerInput[counter]='B';   //Add an instance of the character 'B' to the player input vector
            counter++;                  //Increment the counter of how many character have been entered
            fs1=0;
            spi.write(CHAR_B);          //Output the binary string for representing 'B' on the LED display via SPI
            fs1=1;
        }
    }
}

//Called when the player presses the 'C' button
void addC(){
    if(randCharsDisplayed)
    {
        if (counter<5){
            playerInput[counter]='C';   //add an instance of the character 'C' to the player input vector
            counter++;                  //Increment the counter of how many character have been entered
            fs1=0;
            spi.write(CHAR_C);          //Output the binary string for representing 'C' on the LED display via SPI
            fs1=1;
        }
    }
}    
