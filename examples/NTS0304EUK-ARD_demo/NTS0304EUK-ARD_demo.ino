/** NTS0304EUK-ARD demo sample
 *
 *  Full featured demo for NTS0304EUK-ARD
 *  All possible combination is demonstrated with 0.95V, 1.2V, 1.8V, 2.5V and 3.3V at LDO1 and 
 *  1.8V, 2.5V, 3.3V and 4.96V at LDO2 except condition of "V_LDO1 > V_LDO2". 
 *  
 *  To perform sample I2C and SPI transfer, it uses AD5161 class library which is defined in "Potentiometer_ADI_Arduino" library. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About NTS0304E:
 *    https://www.nxp.com/products/analog-and-mixed-signal/voltage-level-translators/4-bit-dual-supply-translating-transceiver-open-drain-auto-direction-sensing:NTS0304E
*/

/*
 * NOTE1: Jumper pins
 * 
 * NTS0304EUK-ARD jumper settings may need to be changed. 
 * J8 and J9 pins 1-2, 3-4, 5-6, 7-8 are needed to be shorted. 
 * Be careful that J8 and J9 directions are different.
 * J2 need to be removed to get device data
 */

/*
 * NOTE2: Control pins for genral settings
 *
 * "A2": SPI = 0, I2C = 1
 * "A3": 0 to route op-amp output to "A1"
 * "D5": 0 to Disconnect CS and set address 0x5A, 1 to connrct CS to AD5161
 */

 /*
 * NOTE3: Control pins for LDOs
 * 
 * LDO1 output voltage is controlled by D0, D1 and D4 pins on Arduino shield connector. 
 * Since D0 and D1 are shared with "Serial" library of Arduino SDK, the "Serial.print()" 
 * and "Serial.println()" will disturb the voltage. 
 * For this reason, the termial screen output is disabled in default. So nothing will be 
 * seen on screen. Check the behavior on oscilloscope. 
 */

#include "AD5161.h"
#include "BusInOut.h"

/* Option setings */
//#define I2C_SETTING
#define SERIAL_OUT_DISABLE


#ifdef I2C_SETTING
AD5161_I2C dp;
#else
AD5161_SPI dp;
#endif  // I2C_SETTING

BusInOut setting(5, A3, A2);
BusInOut ldo1(0, 1, 4);
BusInOut ldo2(2, 3);

constexpr int v1_variation = 5;
constexpr int v2_variation = 4;
float v1_values[v1_variation] = { 1.2, 1.8, 2.5, 3.3, 0.95 };
float v2_values[v2_variation] = { 1.8, 2.5, 3.3, 4.96 };

void setup() {
#ifndef SERIAL_OUT_DISABLE
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Hello, NTS0304EUK-ARD");
  Serial.println("\"D0\" and \"D1\" pins are disabled with \"Serial\" feature because those pins are shared");
#endif  // SERIAL_OUT_DISABLE

  setting.config(OUTPUT);
  ldo1.config(OUTPUT);
  ldo2.config(OUTPUT);

#ifdef I2C_SETTING
  setting = 0b100;
  Wire.begin();
#else
  setting = 0b001;
  SPI.begin();
#endif  // I2C_SETTING
}

void loop() {
  uint8_t read_value;

  for (int v1 = 0; v1 < v1_variation; v1++) {
    for (int v2 = 0; v2 < v2_variation; v2++) {
      if (v1_values[v1] > v2_values[v2])
        continue;

      ldo1 = v1;
      ldo2 = v2;

      delay(800);  // wait voltages settle

      for (int i = 0; i < 256; i++) {
        dp = i;
        read_value = dp;

#ifndef SERIAL_OUT_DISABLE
        Serial.println(read_value);
#endif  // SERIAL_OUT_DISABLE

        delay(10);
      }
    }
  }
}
