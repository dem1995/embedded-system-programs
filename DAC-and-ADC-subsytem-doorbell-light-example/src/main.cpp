/*Includes*/
#include <deque>
#include <valarray>
#include <numeric>
#define _USE_MATH_DEFINES
#include <cmath>
#include "pin.h"
#include "timer.h"
#include "analog_to_digital_sample.h"

#define PINSEL1 (*(volatile int*)0x4002C004)
#define PINMODE1 (*(volatile int*)0x4002C044)

//Used for setting the Digital-to-Analog subsystem values.
#define DACR (*(volatile unsigned int *)0x4008C000)

/**
*	Generates a valarray with values ranging from start through end, with the given step size.
*	@param start The lowest value of the generated valarray.
*	@param end The upper bound on the highest value of the generated valarray.
*	@param step The spacing between members of the generated valarray
*	@return a valarray with a range of values specified by the parameters
*/
std::valarray<double> generate_values(double start, double end, double step)
{
	std::valarray<double> return_array((end-start)/step+1);
	for (int i=0; i<return_array.size(); i++)
	{
		return_array[i] = start + i*step;
	}
	return return_array;
}


/*Main function*/
/**
*	Project to gain experience with the LPC1769's Analog-to-Digital and Digital-to-Analog subsystems.
*	Lights up an LED when the brightness on a phototransistor gets too low. Also outputs a
*	doorbell sound when a button is pressed.
*/
int main()
{
	//How long to wait each main program loop
	//One of these wait times is used to create an ~659 Hz square wave, while the other
	//is used to generate an ~523 Hz square wave.
	const double seconds_to_wait_1 = 0.00046;
	const int ticks_to_wait_1 = seconds_to_ticks(seconds_to_wait_1);
	const double seconds_to_wait_2 = 0.00066;
	const int ticks_to_wait_2 = seconds_to_ticks(seconds_to_wait_2);
	//The ticks to wait value for the entire program
	int ticks_to_wait = ticks_to_wait_1;

	//The clock was not fast enough to shape nice sine waves at the desired frequencies,
	//so this actually just has sin(0) and sin(pi/2)
	std::valarray<double> sin_values {0.0,1.0};

	//A list of sine wave values
	std::valarray<double> sin_values = sin(generate_values(0, 2*M_PI, 2*M_PI/3.0));

	//Scales the wave values to match the expected format for the digitalto-analog
	// subsystem's DACR register
	std::valarray<double> scaled_sin_values = sin_values - sin_values.min();
	scaled_sin_values/= (scaled_sin_values.max() - scaled_sin_values.min());
	scaled_sin_values *= 1023;

	//An array of readings
	double readings[40] = {0};
	int readings_size = 40;
	int num_readings = 0;
	int cycle_number = 0;
	double multiplied_average = 0;

	//The pin used for the doorbell button input.
	pin button_pin = pin(0, 27);

	PINSEL1 |= 1 << 21;
	PINSEL1 &= ~(1<<20);

	PINMODE1 |= 0b11<<23;

	//Were we to have more values in our wave array, this count would make sure we cycled
	//through them well. The max_tapering values are used to ensure that the amplitudes
	//of the produced wave signals decrease over time
	int count = 0;
	long tapering = 0;
	const long max_tapering_1 = 900;
	const long max_tapering_2 = 900;

	bool doorbell_pressed = false;
	bool previously_pressed =false;
	bool sound1_playing = false;
	bool sound2_playing = false;
	//Main loop. Determines doorbell logic, then if nothing needs to be done
	//with the doorbells, keeps track of ambient light to determine whether to turn the
	//LED on
	while(true)
	{
		doorbell_pressed = button_pin;

		//If the doorbell is pressed, prepare to play sound 1
		//Also prepare to play sound 2 when the switch is released
		if (doorbell_pressed)
		{
			if (!previously_pressed)
			{
				if (!sound1_playing)
					tapering = 0;
				previously_pressed = true;
				sound1_playing = true;
				sound2_playing = false;
			}
		}
		//If that's not the case, but the doorbell has been recently previously pressed,
		//prepare to play sound 2
		else if (previously_pressed)
		{
			if (!sound2_playing)
				tapering = 0;
			previously_pressed = false;
			sound1_playing = false;
			sound2_playing = true;
		}

		//If sound 1 is supposed to be playing, play it.
		if (sound1_playing)
		{
			ticks_to_wait = ticks_to_wait_1;
			count %=scaled_sin_values.size();

			//Taper and start/continue playing sound 1
			DACR = (int)(scaled_sin_values[count]*((max_tapering_1-tapering)/(double)max_tapering_1))<<6;
			count++;
			tapering++;
			if (tapering > max_tapering_1)
			{
				doorbell_pressed = false;
				sound1_playing = false;
			}
		}
		//Otherwise, if sound 2 is supposed to be playing, play it.
		else if (sound2_playing)
		{
			ticks_to_wait = ticks_to_wait_2;
			count %=scaled_sin_values.size();
			//Taper and start/continue playing sound 2
			DACR = (int)(scaled_sin_values[count]*((max_tapering_2-tapering)/(double)max_tapering_2))<<6;
			count++;
			tapering++;
			if (tapering > max_tapering_2)
			{
				sound2_playing = false;
			}
		}

		//If neither of the sounds are supposed to be playing, handle the light sensor
		// to see if we need to light the LED.
		if (!sound1_playing && !sound2_playing)
		{
			/*
			* Taking light readings and computing the average
			*/
			//Take light voltage
			double current_light_reading = ADsample();

			if (num_readings<readings_size)
				num_readings++;

			//Fast way of keeping track of the average light value
			//for the past num_readings readings.
			multiplied_average += current_light_reading;
			multiplied_average -= readings[cycle_number];

			readings[cycle_number] = current_light_reading;

			//Ensures that the array acts as a circular queue
			cycle_number = (cycle_number+1)%readings_size;

			//If the ambient light is high enough, light up the LED
			if(num_readings == readings_size)
			{
				double average = multiplied_average/(double)readings_size;
				if (average<0.4)
					pin(2, 13) = 0;
				else
					pin(2, 13) = 1;
			}
		}
		wait_ticks(ticks_to_wait);
	}

	return 0 ;
}
