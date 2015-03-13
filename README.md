# Arduino

Files to connect various components to arduino.
Copy the files to the libraries folder for your Arduino software( for linux it is : /usr/share/Arduino). You will get examples for the relevant device in your arduino IDE.

1. Rotary Encoder:
Rotary Encoder is used as a continuous rotation device. It can be used to count how many rotations have happened. A rotary or "shaft" encoder is an angular measuring device. It is used to precisely measure rotation of motors or to create wheel controllers (knobs) that can turn infinitely (with no end stop like a potentiometer has). Some of them are also equipped with a pushbutton when you press on the axis (like the ones used for navigation on many music controllers). They come in all kinds of resolutions, from maybe 16 to at least 1024 steps per revolution.
2. MPU-6050 Accelerometer + Gyro
The InvenSense MPU-6050 sensor contains a MEMS accelerometer and a MEMS gyro in a single chip. It is very accurate, as it contains 16-bits analog to digital conversion hardware for each channel. Therefor it captures the x, y, and z channel at the same time. The sensor uses the I2C-bus to interface with the Arduino. Reading the raw values for the accelerometer and gyro is easy. The sleep mode has to be disabled, and then the registers for the accelerometer and gyro can be read. But the sensor also contains a 1024 byte FIFO buffer. The sensor values can be programmed to be placed in the FIFO buffer. And the buffer can be read by the Arduino.
The FIFO buffer is used together with the interrupt signal. If the MPU-6050 places data in the FIFO buffer, it signals the Arduino with the interrupt signal so the Arduino knows that there is data in the FIFO buffer waiting to be read.
A little more complicated is the ability to control a second I2C-device.
The MPU-6050 always acts as a slave to the Arduino with the SDA and SCL pins connected to the I2C-bus.
But beside the normal I2C-bus, it has it's own I2C controller to be a master on a second (sub)-I2C-bus. It uses the pins AUX_DA and AUX_CL for that second (sub)-I2C-bus.
It can control, for example, a magnetometer. The values of the magnetometer can be passed on to the Arduino.
Things get really complex with the "DMP".
The sensor has a "Digital Motion Processor" (DMP), also called a "Digital Motion Processing Unit". This DMP can be programmed with firmware and is able to do complex calculations with the sensor values.
For this DMP, InvenSense has a discouragement policy, by not supplying enough information how to program the DMP. However, some have used reverse engineering to capture firmware.
The DMP ("Digital Motion Processor") can do fast calculations directy on the chip. This reduces the load for the microcontroller (like the Arduino). The DMP is even able to do calculations with the sensor values of another chip, for example a magnetometer connected to the second (sub)-I2C-bus.


3. GPS-GY-GPS6MV2
The marking on pcb is GY-GPS6MV2. On pcb there are also a 3.3V regulator (so you can connect board to 5V power supply), a small battery for retaining data, nonvolatile storage for configuration and a green LED which starts blinking when the module has GPS data. Antenna is external active antenna and connects to the module via ufl connector.
The GY-GPS/NEO6MV2 module comes with a U-Blox NEO 6 series module fitted upon the PCB, an EEPROM to store configuration, a button cell to keep EEPROM data intact, LED indicator, connectors and a ceramic antenna. It sometime happens that the LED doesn’t blink when the module is powered up, at first it seems that the module is faulty but in actual the LED indicator blinks only when it has got a lock on satellites. So, dont get dishearten, to see a non lit LED after powering up the module. For quick position lock it is suggested that you take the setup nearby window and try.


4. SD card reader
The circuit:
  SD card attached to SPI bus as follows:
  MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
  MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
  CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
  CS - depends on your SD card shield or module.
        Pin 4 used here for consistency with other Arduino examples
The SD card examples are already present in the arduino GUI.


5. Soil Moisture Sensor-YL-69 - An example code is given in the Folder SoilMoistureSensor.
Chinese-built YL-69. These sensors also come with a circuit which allows you to get two outputs: one is an analog readout of the resistance between the sensor’s two plates and the second is a digital output (essentially, HIGH or LOW, 5v or 0v) depending on whether the humidity is above or below a threshold which can in turn be adjusted by a built-in POTS. 
The analog readout is connected to A0 pin in the Arduino Nano. The code reads out the input from the pin using an ADC and converts the value into the percentage of humidity present.


6. BMP180 - barometric pressure and temperature sensor
Like most pressure sensors, the BMP180 measures absolute pressure.
Since absolute pressure varies with altitude, you can use the pressure
to determine your altitude.
Because pressure also varies with weather, you must first take a pressure
reading at a known baseline altitude. Then you can measure variations
from that pressure
Hardware connections:
(GND) to GND
(VIN) to 3.3V
(WARNING: do not connect + to 5V or the sensor will be damaged!)
You will also need to connect the I2C pins (SCL and SDA) to your
Arduino. The pins are different on different Arduinos:
Any Arduino pins labeled: SDA SCL
Uno, Redboard, Pro, Nano: A4 A5
Mega2560, Due: 20 21
Leonardo: 2 3


7. Gas Sensor - MQ
The MQ series of gas sensors use a small heater inside with an electro-chemical sensor. They are sensitive for a range of gasses and are used indoors at room temperature.
They can be calibrated more or less but a known concentration of the measured gas or gasses is needed for that. 
The heater
----------
The voltage for the internal heater is very important.
Some sensors use 5V for the heater, others need 2V. The 2V can be created with a PWM signal, using analogWrite() and a transistor or logic-level mosfet.
The heater may not be connected directly to an output-pin of the Arduino, since it uses too much current for that.
Some sensors need a few steps for the heater. This can be programmed with an analogWrite() function and delays. A transistor or logic-level mosfet should also in this situation be used for the heater.
If it is used in a battery operated device, a transistor or logic-level mosfet could also be used to switch the heater on and off.
The sensors that use 5V or 6V for the internal heater do get warm. They can easily get 50 or 60 degrees Celcius.
After the "burn-in time", the heater needs to be on for about some time (3 minutes when tested with MQ-2) before the readings become stable. 
Load-resistor
--------------
The sensor needs a load-resistor at the output to ground. It's value could be from 2kOhm to 47kOhm. The lower the value, the less sensitive. The higher the value, the less accurate for higher concentrations of gas.
If only one specific gas is measured, the load-resistor can be calibrated by applying a know concentration of that gas. If the sensor is used to measure any gas (like in a air quality detector) the load-resistor could be set for a value of about 1V output with clean air.
Choosing a good value for the load-resistor is only valid after the burn-in time. 
Info source:http://playground.arduino.cc/Main/MQGasSensors#interesting

8. ADXL345 -Accelerometer:
The ADXL345 is a small, thin, low power, 3-axis accelerometer with high resolution (13-bit) measurement at up to ±16 g. Digital output data is formatted as 16-bit twos complement and is accessible through either a SPI (3- or 4-wire) or I2C digital interface. The ADXL345 is well suited to measure the static acceleration of gravity in tilt-sensing applications, as well as dynamic acceleration resulting from motion or shock. Its high resolution (4 mg/LSB) enables measurement of inclination changes less than 1.0°. Several special sensing functions are provided. Activity and inactivity sensing detect the presence or lack of motion and if the acceleration on any axis exceeds a user-set level. Tap sensing detects single and double taps. Free-fall sensing detects if the device is falling. These functions can be mapped to one of two interrupt output pins. An integrated, patent pending 32-level first in, first out (FIFO) buffer can be used to store data to minimize host processor intervention. Low power modes enable intelligent motion-based power management with threshold sensing and active acceleration measurement at extremely low power dissipation.
It has both SPI and I2C interfaces.I2C is a 2-wire serial connection, so you just need to connect the SDA (Data) and SCL (Clock) lines to your Arduino for communication. On your Arduino (everything but the mega) SDA is on analog pin 4, and SCL is on analog pin 5. On an arduino mega, SDA is digital 20, and SCL is digital 21.
Make sure both VCC and the CS pins on the sensor are connected to 3.3v. We connect CS to 3.3V to tell the sensor we will be using it as an I2C device, and not an SPI device.
SPI interface.
Arduino Pin 	ADXL345 Pin
10 		CS
11 		SDA
12 		SDO
13 		SCL
3V3 		VCC
Gnd 		GND

9. TSL2561:- Luminosity Sensor
The TSL2561 is an inexpensive, yet sophisticated, light sensor. Unlike simpler sensors, like photoresistors and photodiodes, the TSL2561 incorporates both infrared and visible light sensors to better approximate the response of the human eye. Because the TSL2561 is an integrating sensor (it soaks up light for a predetermined amount of time), it is capable of measuring both very small and very large amounts of light. One lux is equal to one lumen per square meter. Practically, lux is a measure of how bright any given illumination will appear to the human eye.The human eye has a huge dynamic range, far more than most electronic sensors. Real-world conditions can range from 0.0001 lux in starlight, to over 100,000 lux in direct sunlight. The TSL2561 has features that allow it to handle this huge dynamic range. These settings are similar to a camera; one can change both the sensitivity, which is like an ASA film rating, and the integration time, which is like the shutter speed. Like a camera, you can balance those measurements for the best results.Lux is a very complex measurement to make because it involves both the human eye’s response to color (frequency) and the concentration of that light (a flashlight will produce a higher lux value than the equivalent bare bulb). The TSL2561 is not a true luxmeter, but the manufacturer of the TSL2561 has characterized its output against professional equipment to come up with lux approximation equations. (You can find these equations in the datasheet.) It should be noted that although these equations will get you in the ballpark, the TSL2561 is not a calibrated instrument (nor is it priced like one). If you need highly accurate results you should at least perform your own calibration. For everyday use however, the TSL2561 is far superior to simpler photoresistors and photodiodes for illumination measurement.

10. A3144 Hall-Effect Sensor:   The A3144 is an integrated Hall effect non-latching sensor. Holding a magnet near the sensor will cause the output pin to toggle. This makes for a robust presence sensor. . The device includes an on-chip Hall voltage generator for magnetic sensing, a comparator that amplifies the Hall voltage, and a Schmitt trigger to provide switching hysteresis for noise rejection, and open-collector output. An internal bandgap regulator is used to provide temperature compensated supply voltage for internal circuits and allows a wide operating supply range.
If a magnetic flux density larger than threshold Bop, the output is turned on (low). The output state is held until a magnetic flux density reversal falls below Brp causing the output to be turned off (high).
Connection
----------
![Connection Hall Effect Sensor](http://bildr.org/blog/wp-content/uploads/2011/04/0h090u1-400x302.png?raw=true "Connection Hall Effect Sensor. Similar Connection for A3144")

11. BH1750 Light Intensity Sensor
BH1750 light intensity sensor breakout board with a 16 bit AD converter built-in which can directly output a digital signal, there is no need for complicated calculations. This is a more acurate and easier to use version of the simple foto resistor which only outputs a voltage that needs to be calculated in order to obtain meaningful data. With the BH1750 Light Sensor intensity can be directly measured by the luxmeter, without needing to make calculations. The data which is output by this sensor is directly output in Lux (Lx). When objects which are lighted in homogeneous get the 1 lx luminous flux in one square meter ,their light intensity is 1lx. Sometimes to take good advantage of the illuminant, you can add a reflector to the illuminant.So that there will be more luminous flux in some directions and it can increase the ilumination of the target surface. 
For example
    Night: 0.001--0.02;  
    moonlightnight:0.02--0.3;  
    cloudy indoor:5--50;
    cloudy outdoor:50--500;
    Sunny indoor:100--1000;
    under the sunlight in summer afternoon: about 10*6 power; 
    reading books for intensity of illumination:50--60;
    home video standard intensity of illumination:1400
Specification
--------------
power supply voltage: +3 to 5Vdc.
Interface: I2C.
Wide range and High resolution. ( 1 - 65535 lx ).
It is possible to select 2 types of I2C slave-address.
Small measurement variation (+/- 20%).
Size: 0.85*0.63*0.13"(21*16*3.3mm)
Connection Diagram
------------------
![Connection Diagram](http://cdn.instructables.com/F0H/Q2D2/HLZRHA0P/F0HQ2D2HLZRHA0P.LARGE.jpg?raw=true "Connection Diagram")

12. Human Capacitive Sensor
The capacitiveSensor library turns two or more Arduino pins into a capacitive sensor, which can sense the electrical capacitance of the human body. All the sensor setup requires is a medium to high value resistor and a piece of wire and a small (to large) piece of aluminum foil on the end. At its most sensitive, the sensor will start to sense a hand or body inches away from the sensor. 
Applications
------------
Capacitive sensing may be used in any place where low to no force human touch sensing is desirable. An Arduino and the library may be used to sense human touch through more than a quarter of an inch of plastic, wood, ceramic or other insulating material (not any kind of metal though), enabling the sensor to be completely visually concealed.
A capacitive sensor covered with paper or other insulator also acts as fairly good (human touch) pressure sensor with an approximately logarithmic response. In this regard it may surpass force sensing resistors in some applications.
![Capacitive Sensing](http://playground.arduino.cc/uploads/Main/CapSense.gif)
The capacitiveSensor method toggles a microcontroller send pin to a new state and then waits for the receive pin to change to the same state as the send pin. A variable is incremented inside a while loop to time the receive pin's state change. The method then reports the variable's value, which is in arbitrary units. 
The physical setup includes a medium to high value (100 kilohm - 50 megohm) resistor between the send pin and the receive (sensor) pin. The receive pin is the sensor terminal. A wire connected to this pin with a piece of foil at the end makes a good sensor. For many applications, a more useful range of values is obtained if the sensor is covered with paper, plastic, or another insulating material, so that users do not actually touch the metal foil. Research has shown that a small capacitor (100 pF) or so from sensor pin to ground improves stability and repeatability.
When the send pin changes state, it will eventually change the state of the receive pin. The delay between the send pin changing and the receive pin changing is determined by an RC time constant, defined by R * C, where R is the value of the resistor and C is the capacitance at the receive pin, plus any other capacitance (e.g. human body interaction) present at the sensor (receive) pin. Adding small capacitor (20 - 400 pF) in parallel with the body capacitance, is highly desirable too, as it stabilizes the sensed readings.  
	   Use a 1 megohm resistor (or less maybe) for absolute touch to activate.
	   With a 10 megohm resistor the sensor will start to respond 4-6 inches away.
	   With a 40 megohm resistor the sensor will start to respond 12-24 inches away (dependent on the foil size). Common resistor sizes usually end at 10 megohm so you may have to solder four 10 megohm resistors end to end.
	   One tradeoff with larger resistors is that the sensor's increased sensitivity means that it is slower. Also if the sensor is exposed metal, it is possible that the send pin will never be able to force a change in the receive (sensor) pin, and the sensor will timeout.
	   Also experiment with small capacitors (100 pF - .01 uF) to ground, on the sense pin. They improve stability of the sensor. 
The grounding of the Arduino board is very important in capacitive sensing. The board needs to have some connection to ground, even if this is not a low-impedance path such as a wire attached to a water pipe.
More info:http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense
13. HC-SR04 
HC-SR04 is an ultrasonic ranging module that provides 2 cm to 400 cm non-contact measurement function. The ranging accuracy can reach to 3mm and effectual angle is < 15°. It can be powered from a 5V power supply.
HC-SR04 Specifications
    Working Voltage: DC 5V
    Working Current: 15mA
    Working Frequency: 40Hz
    Max Range: 4m
    Min Range: 2cm
    Measuring Angle: 15 degree
    Trigger Input Signal: 10µS TTL pulse
    Echo Output Signal Input TTL lever signal and the range in proportion
    Dimension 45 * 20 * 15mm

