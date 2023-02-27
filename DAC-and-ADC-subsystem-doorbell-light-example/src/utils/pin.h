/*
 * Pin.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: David "Dawn" Estes McKnight
 */

#ifndef PIN_H_
#define PIN_H_

#include <string>
#include "FIOprep.h"

/**
 * A class to simplify the usage of pins for DDL projects.
 */
class pin
{

public:

	/**
	 * Default constructor for the pin class.
	 */
	pin();

	/**
	 * Copy constructor for the pin class.
	 * @param orig The pin to be copied.
	 */
	pin(const pin& orig);

	/**
	 * Constructs a pin object that refers to the given bit/number corresponding to the provided port number and bit number.
	 * @param port_location The number of the port.
	 * @param bit_number The offset of the bit from the start of the port.
	 */
	pin(unsigned int port_number, unsigned int bit_number);

	/**
	 * Constructs a pin object that refers to the given bit/number corresponding to the provided port number and bit number.
	 * Also sets the pin high (value is true) or low (value is false).
	 * @param port_location The number of the port.
	 * @param bit_number The offset of the bit from the start of the port.
	 * @param value Whether to set the pin high (true) or low (false).
	 */
	pin(unsigned int port_number, unsigned int bit_number, bool value);

	/**
	 * Calls write on the value
	 * @param value the value to be written to this pin
	 */
	void operator = (bool value);

	/**
	 * Writes the value (true = high, false = low) to this pin.
	 * @param value The value to write to the pin (true = high, false = low).
	 */
	void write(bool value);

	/**
	 * Casts the value of this pin to the read-in value.
	 */
	operator bool();

	/**
	 * Reads the value (high = true, low = false) from this pin.
	 * @return The value of the pin (high = true, low = false).
	 */
	bool read();


protected:

	/**
	 * The port number of this pin
	 */
	unsigned int _port_number;

	/**
	 * The bit offset of this pin (the pin number within the port).
	 */
	unsigned int _bit_number;
};

#endif
