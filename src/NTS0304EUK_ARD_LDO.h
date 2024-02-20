/** BusInOut library for Arduino
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#ifndef ARDUINO_NTS0304EUK_ARD_LDO_H
#define ARDUINO_NTS0304EUK_ARD_LDO_H

#include <Arduino.h>
#include <stdint.h>

#include "BusInOut.h"

/** Nts0304euk_Ard_LDO class
 *	
 *  @class Nts0304euk_Ard_LDO
 */


class Nts0304euk_Ard_LDO : public BusInOut {
public:
	using BusInOut::operator=;
	
	/** Create a Nts0304euk_Ard_LDO instance with specified pins
	 *
	 * @param ldo_number 1 or 2 to specify the LDO
	 */
	Nts0304euk_Ard_LDO(	int ldo_number, int pin0, int pin1, int pin2, float *v_v );
	~Nts0304euk_Ard_LDO();

	/** Get Nts0304euk_Ard_LDO output voltage
	 *
	 * @return voltage
	 */
	float	voltage( void );

	/** Get Nts0304euk_Ard_LDO output voltage
	 *
	 * @param v setting value but no output will be changed
	 * @return voltage
	 */
	float	voltage( int v );

	constexpr static int v1_variation = 5;
	constexpr static int v2_variation = 4;
	
	static float	v1_values[ v1_variation ];
	static float	v2_values[ v2_variation ];
	
private:
	int				num;
	BusInOut		ldo;
	float			*v_values;

};

class Nts0304euk_Ard_LDO1 : public Nts0304euk_Ard_LDO {
public:
	using Nts0304euk_Ard_LDO::operator=;

	Nts0304euk_Ard_LDO1( int ldo_number = 1, int pin0 = 0, int pin1 = 1, int pin2 = 4, float *v_v = v1_values );
	~Nts0304euk_Ard_LDO1();
};

class Nts0304euk_Ard_LDO2 : public Nts0304euk_Ard_LDO {
public:
	using Nts0304euk_Ard_LDO::operator=;

	Nts0304euk_Ard_LDO2( int ldo_number = 2, int pin0 = 2, int pin1 = 3, float *v_v = v2_values );
	~Nts0304euk_Ard_LDO2();
};


#endif //	ARDUINO_NTS0304EUK_ARD_LDO_H
