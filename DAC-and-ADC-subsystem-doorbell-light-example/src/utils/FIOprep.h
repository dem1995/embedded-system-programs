/*
 * FIOprep.h
 *
 *  Created on: Feb 6, 2019
 *      Author: David "Dawn" Estes McKnight
 *
 * A class for holding a struct for accessing details of pins cleanly.
 */

#ifndef FIOPREP_H_
#define FIOPREP_H_

#define FIO ((struct FIOREGS*)0x2009C000)
struct FIOREGS
{
	volatile unsigned int FIODIR;			//The direction of some pin
	volatile unsigned int NOTOUCHING[3];	//Don't touch this
	volatile unsigned int FIOMASK;			//Masks for writing/reading. Not important.
	volatile unsigned int FIOPIN;			//The value of the pins
	volatile unsigned int FIOSET;
	volatile unsigned int FIOCLR;
};


#endif /* FIOPREP_H_ */