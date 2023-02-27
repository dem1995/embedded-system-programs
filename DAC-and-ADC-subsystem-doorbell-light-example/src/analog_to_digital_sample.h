#ifndef ANALOG_TO_DIGITAL_SAMPLE_H_
#define ANALOG_TO_DIGITAL_SAMPLE_H_

#include "utils/pin.h"

#define PCONP (*(volatile int*)0x400FC0C4)
#define AD0CR (*(volatile int*)0x40034000)
#define PINSEL1 (*(volatile int*)0x4002C004)
#define PINMODE1 (*(volatile int*)0x4002C044)
#define AD0GDR (*(volatile int*)0x40034004)

/**
 * Returns a rescaled analog voltage reading from one of the pins.
 * @return A value between 0 and 1, with 1 representing high voltage and 0 representing low.
 */
double ADsample()
{
	double data;
	double data0;

	//Check to see if ADC Subsystem is already on and start proper shutdown
	if((PCONP>>12)&1)
	{
		AD0CR = 0;
	}

	//Turn off PCONCP Register ADC bit
	PCONP &= ~(1<<12);

	//Enable Power on ADC Subsystem from known state
	PCONP |= (1<<12);
	AD0CR |= (1<<21);

	//Clock defaults to 1 MHz

	//Set up corresponding pin function and resistor
	PINSEL1 |= (1<<14);
	PINMODE1 |= (0b1<<15);

	//Start Conversion using AD control register
	AD0CR |= 1;
	AD0CR |= (1<<24);

	//Wait for conversion to finish
	unsigned int ag0gdr = AD0GDR; 	
	data0 = (ag0gdr>>31)&1; 	
	data = (ag0gdr>>4)&0xFFF;
	while(data0==0)
	{
		ag0gdr = AD0GDR;
		data0 = (ag0gdr>>31)&1;
		data = (ag0gdr>>4)&0xFFF;
	}

	//Read Data off Global Data Register and standardize between 0 and 1
	data /= 4096.0;

    return data;
}
#endif 