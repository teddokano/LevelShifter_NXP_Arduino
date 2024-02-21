# LevelShifter_NXP_Arduino
Level shifter (voltage translator) evaluation board sample code for [Arduino](https://www.arduino.cc) 

> **Note**
This library works with 
[`I2C_device`](https://github.com/teddokano/I2C_device_Arduino),
[`BusInOut_Arduino`](https://github.com/teddokano/BusInOut_Arduino),
and [`Potentiometer_ADI_Arduino`](https://github.com/teddokano/Potentiometer_ADI_Arduino) libraries together.  
Please be sure all libraries are imported in your environment before trying to build. 

![Boards](https://github.com/teddokano/additional_files/blob/main/LevelShifter_NXP_Arduino/board.jpg)  
_NTS0304EUK-ARD : Arduino® Shield Evaluation Board for Level shifter (voltage translator)_  
_Oscilloscope probes are on J8-pin1 and J9-pin1 to measure chip-select signal voltages while the board operated in SPI mode_

## What is this?
An Arduino demo code for **Level shifter (voltage translator)** device evaluation board.  
This demo code shows NTS0304E operation with changing two side (controller side and target side) signal voltages.  
The two voltages are supplied from LDOs on the board. This sample code controls those LDOs via GPIO pins.   

A digital potentiometer:AD5161 is on the board. The sample code communicats with the potentiometer to show its waveform.  
Use an oscilloscope to find voltage/waveform on the board. 

## Supported board
Type#|Features|Evaluation board
---|---|---
[NTS0304E](https://www.nxp.com/products/analog-and-mixed-signal/voltage-level-translators/4-bit-dual-supply-translating-transceiver-open-drain-auto-direction-sensing:NTS0304E)	|4-Bit Dual-Supply Translating Transceiver (Open-Drain, Auto-Direction Sensing)	|[NTS0304EUK-ARD Level Shifter Evaluation Board](https://www.nxp.com/design/design-center/development-boards/analog-toolbox/arduino-shields-solutions/nts0304euk-ard-level-shifter-evaluation-board:NTS0304EUK-ARD)

# Getting started

Use Library manager in Arduino IDE for easy install

# What's inside?

## No class library
Since the NTS0304E is just a level shifter, no sofware control is needed.  
So, this repository is **NOT** containing `NTS0304E` class library but just a sample demo code.  

## Examples
Examples are provided as scketch files.

### How to use? : Full featured demo: `NTS0304EUK-ARD_demo`

**NTS0304EUK-ARD_demo** is a full featured demo code.   
After library install, Choose menu on Arduino-IDE: `File`→`Examples`→`LevelShifter_NXP_Arduino`→ NTS0304EUK-ARD_demo


On **Arduino Uno R3**, this demo code will show **nothing** on terminal screen.  
Since the LDO1 output voltage is controled by D0 and D1 pins, the `Serial` API to print characters on screen disturbs the behavior.  
Again, **while the demo running, no screen update will be done**.  
<U>To perform output all voltage variation on LDO1, the screen message needed to be disabled.</U>  
While the demo, prove on the signal lines and monitor the waveform on an oscilloscope.  

On **Arduino Uno R4**, such restriction does not exist.  
The messages will be shown on the screen.  

LDO1 and LDO2 can output several voltages. LDO1 voltage becomes the signal voltage on A-side of DUT and LDO2 voltage becomes B-side one.  
- LDO1 (A-side, I²C signals on J8) output can be set 0.95V, 1.2V, 1.8V, 2.5V and 3.3V.  
- LDO2 (B-side, I²C signals on J9) output can be set 1.8V, 2.5V, 3.3V and 4.96V.   

The demo performs I²C/SPI comunication with all combination of two LDO output except condition of "LDO1 > LDO2V"..  

User can set to show messages while the demo by disabling `SERIAL_OUT_DISABLE` option (comment-out the line of this word definition). It will show some information on the screen but the voltage on LDO1 is affected.    

Followings are waveform. Both are ChipSelect line voltage while the program is running in SPI mode, ch1 (yellow) is A-side and ch2 (blue) is B-side.  
Probes were on JP8(A-side)-pin1 and J9(B-side)-pin1. All possible LDO2 output tried at one LDO1 output level.  
The demo sets LDO voltages and wait for 1 second to settle. Then I²C or SPI (depends on user setting in the code) communication done to sweep the potentiometer setting from minimum (0x00) to maximun (0xFF).   
Signal voltages on both side of level shifter can be measured on those pins.  

![Waveforms](https://github.com/teddokano/additional_files/blob/main/LevelShifter_NXP_Arduino/waveform0.png)  

Next picture is output voltage by optentiometer. The potentiomenter is configured as volume between 3.3V and GND. The output of wiper pin is buffered by voltage follower buffer and provided on J10.  
This voltage is measured on pin1 of J10 (pin2 of J10 is GND).   

![Waveforms](https://github.com/teddokano/additional_files/blob/main/LevelShifter_NXP_Arduino/waveform1.png)  

### How to use? : Simplified demo: `NTS0304EUK-ARD_simple_I2C` and `NTS0304EUK-ARD_simple_SPI` 

**NTS0304EUK-ARD_simple_I2C** and **NTS0304EUK-ARD_simple_SPI** are simplified demo code to give better code visibility and user friendry message on screen.  
To have terminal screen message, the LDO1 (A-side supply voltage control) is fixed to 0.95V only.  
The screen message shows read-out value from potentiometer and its output voltage which is routed to A1 pin on Arduino
connector.  

## Related libraries
Library|Feature|Target devices|Required library
---|---|---|---
[GPIO_NXP_Arduino](https://github.com/teddokano/GPIO_NXP_Arduino)				|GPIO libraries						|PCAL6408A, PCAL6416A, PCAL6524, PCAL6534, PCA9555, PCA9554	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[LCDDriver_NXP_Arduino](https://github.com/teddokano/LCDDriver_NXP_Arduino)		|LCD driver libraries				|PCA8561						|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[LEDDriver_NXP_Arduino](https://github.com/teddokano/LEDDriver_NXP_Arduino)		|LED driver libraries				|PCA9955B, PCA9956B, PCA9957	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[MUX_SW_NXP_Arduino](https://github.com/teddokano/MUX_SW_NXP_Arduino)			|I²C mux/switch libraries			|PCA9846						|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[RTC_NXP_Arduino](https://github.com/teddokano/RTC_NXP_Arduino)					|RTC libraries						|PCF2131, PCF85063A				|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[TempSensor_NXP_Arduino](https://github.com/teddokano/TempSensor_NXP_Arduino)	|Temperature sensor libraries		|LM75B, PCT2075, P3T1085		|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)			|Base library for I²C operations	|none (can be applied as base class for all I²C targets)|---
[BusInOut](https://github.com/teddokano/BusInOut_Arduino)						|Utility library for IO pin operation	|none						|---
[Potentiometer_ADI_Arduino](https://github.com/teddokano/Potentiometer_ADI_Arduino)		|Potentiometer library		|AD5161							|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
