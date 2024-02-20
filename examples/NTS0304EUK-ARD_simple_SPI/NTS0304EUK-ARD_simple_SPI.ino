/** NTS0304EUK-ARD demo sample
 *
 *  Simple sample to operate two LDOs to try signal voltage convination
 *  In this demo, A-side signal voltage (by LDO1) is fixed to 0.95V to show message on terminal screen.  
 *  B-side (by LDO2) will chaged to 1.8V, 2.5V, 3.3V and 4.96V. 
 *  
 *  To perform sample SPI transfer, it uses AD5161 class library which is defined in "Potentiometer_ADI_Arduino" library. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About NTS0304E:
 *    https://www.nxp.com/products/analog-and-mixed-signal/voltage-level-translators/4-bit-dual-supply-translating-transceiver-open-drain-auto-direction-sensing:NTS0304E
*/


#include "AD5161.h"
#include "BusInOut.h"

AD5161_SPI dp;

BusInOut setting(5, A3, A2);
BusInOut ldo1(0, 1, 4);
BusInOut ldo2(2, 3);

constexpr int v1_variation = 5;
constexpr int v2_variation = 4;
float v1_values[v1_variation] = { 1.2, 1.8, 2.5, 3.3, 0.95 };
float v2_values[v2_variation] = { 1.8, 2.5, 3.3, 4.96 };

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Hello, NTS0304EUK-ARD");
  Serial.println("LDO1 output voltage is fixed to 0.95V in this demo");

  setting.config(OUTPUT);
  ldo1.config(OUTPUT);
  ldo2.config(OUTPUT);

  setting = 0b001;
  ldo1 = 4;

  SPI.begin();
}

void loop() {
  uint8_t read_value;
  float analog_value;

  for (int v2 = 0; v2 < v2_variation; v2++) {
    ldo2 = v2;

    delay(800);  // wait voltages settle

    for (int i = 0; i < 256; i++) {
      dp = i;
      read_value = dp;
      analog_value = analogRead(A0) * 5.0 / 1023.0;

      Serial.print("Comm = SPI    LDO1 = 0.95V    LDO2 = ");
      Serial.print(v2_values[v2], 2);
      Serial.print("V    pot-meter read value = 0x");
      Serial.print(read_value, HEX);
      Serial.print("    pot-meter output = ");
      Serial.print(analog_value, 2);
      Serial.print("V\n");
      delay(10);
    }
  }
}
