#ifndef BOUNCELESSTRIGGER_CPP
#define BOUNCELESSTRIGGER_CPP

#include "BouncelessTrigger.h"

/*!
\author David "Dawn" Estes McKnight
\date 24 September 2016
BouncelessTrigger is a class for eliminating temporary noise (like bounce) from input and calling an attached function when the button has been recently pressed or recently depressed.
*/

BouncelessTrigger::BouncelessTrigger(PinName in, PinMode mode):BouncelessInput(in, mode)
{
    _ticker.detach();
    _ticker.attach(this, &BouncelessTrigger::update, 0.001);
    _callback=NULL;
    _callbackMode=OnPress;
    }
    

void BouncelessTrigger::attach(void (*callback)(void), CallbackMode mode)
{
    _callback.attach(callback);
    _callbackMode=mode;
    }

void BouncelessTrigger::callCallback(void)
{
    _callback.call();
    }
    
void BouncelessTrigger::update(void)
{
    BouncelessInput::update();
    if (_callbackMode==OnPress)
    {
        if(recentlyPressed())
            callCallback();
    }
    else if (_callbackMode==OnDepress)
    {
        if(recentlyDepressed())
            callCallback();
        }
    
    }
#endif