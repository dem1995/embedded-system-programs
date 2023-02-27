#ifndef BOUNCELESSINPUT_H
#define BOUNCELESSINPUT_H

#include "mbed.h" // Requires configured ARM mbed compiler

/*!
\author David "Dawn" Estes McKnight
\date 12 September 2016
BouncelessInput is a class for eliminating temporary noise (like bounce) from input.
*/

class BouncelessInput:DigitalIn
{
public:
    BouncelessInput(PinName in, PinMode mode=PullUp);   //!<Constructor (same constructor information as mbed::DigitalIn).

    
    
    operator int();                 //!<Returns read().
    int read();                     //!<Returns the last steady state.
    void mode(PinMode pinMode);     //!<Need to define this so that we can know the pin mode if users change it away from the constructor.

    
    bool recentlyPressed();         //!<True if the button has been pressed since the last time this method was called.
    bool recentlyDepressed();       //!<True if the button has been depressed since the last time this method was called.

    //void clearRecentPress();      //<Manually clears presses. Not needed, as recentlyPressed does this automatically.
    //void clearRecentDepress();    //<Manually clears depresses. Not needed, as recentlyDepressed does this automatically.

protected:
    PinMode _pinMode;               //!<Stores the PinMode that this BouncelessInput is attached to (AKA, PullUp, PullDown). Also determines whether a change in reading of _bitStream from 0x00->0xFF is a press or a depress (and vice-versa).
    uint8_t  _bitStream;            //!<An integer that holds a stream of 8 bits that is updated whenever Update is called by shifting all bits left and tacking a 1 on the end.
    bool _lastSteadyState;          //!<The state the button was in the last time the stream read 00000000 or 11111111.
    bool _recentlyPressed;          //!<True if the button has been pressed since the last time recentlyPressed() was called.
    bool _recentlyDepressed;        //!<True if the button has been depressed since the last time recentlyDepressed() was called.
    Ticker _ticker;                 //!<Used to call update() repeatedly at a given rate. Keep less than .05 seconds to stabilize (so .05/number of bits), as recommended by http://www.eng.utah.edu/~cs5780/debouncing.pdf .
    void update();                  //!<Updates this BouncelessInput's reading with raw input; updates _bitStream, _lastSteadyState, _recentlyPressed and recentlyDepressed.
};

#endif