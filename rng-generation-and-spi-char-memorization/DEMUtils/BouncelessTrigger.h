#ifndef BOUNCELESSTRIGGER_H
#define BOUNCELESSTRIGGER_H

#include "mbed.h" // Requires configured ARM mbed compiler
#include "BouncelessInput.h"

/*!
\author David "Dawn" Estes McKnight
\date 24 September 2016
BouncelessTrigger is a class for eliminating temporary noise (like bounce) from input and calling an attached function when the button has been recently pressed or recently depressed.
*/

class BouncelessTrigger: public BouncelessInput
{
public:
    BouncelessTrigger(PinName in, PinMode mode=PullDown);   //!<Constructor (same information as mbed::DigitalIn).
    
    enum CallbackMode{OnPress=0, OnDepress=1};              //!<Whether to call the attached function when it's detected that the button has been BouncelessTrigger::recentlyPressed(), or when it has been BouncelessTrigger::recentlyDepressed().
    
    void attach(void (*function)(void), CallbackMode=BouncelessTrigger::OnPress);    //!<Attaches a function to this BouncelessTrigger to be called whenever BouncelessTrigger::recentlyPressed() (if BouncelessTrigger::Mode::OnPress is passed), or BouncelessTrigger::recentlyDepressed() (if BouncelessTrigger::Mode::OnDepress is passed). BouncelessTrigger::Mode::OnPress is passed by default.
    
    void callCallback();                                    //<!Calls the function attached to _callback.
    

    
protected:
    FunctionPointer _callback;                      //!<Uses the mbed's FunctionPointer class to allow us to attach a function to be called whenever BouncelessTrigger::recentlyPressed().
    CallbackMode _callbackMode;                     //!<Whether to call BouncelessTrigger::_callback when BouncelessTrigger::recentlyPressed(), or BouncelessTrigger::recentlyDepressed().
    void update();                                  //!<Called by the ticker attached to this BouncelessTrigger (see BouncelessInput::_ticker).
};

#endif