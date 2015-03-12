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
The TSL2561 is an inexpensive, yet sophisticated, light sensor. Unlike simpler sensors, like photoresistors and photodiodes, the TSL2561 incorporates both infrared and visible light sensors to better approximate the response of the human eye. Because the TSL2561 is an integrating sensor (it soaks up light for a predetermined amount of time), it is capable of measuring both very small and very large amounts of light. One lux is equal to one lumen per square meter. Practically, lux is a measure of how bright any given illumination will appear to the human eye.The human eye has a huge dynamic range, far more than most electronic sensors. Real-world conditions can range from 0.0001 lux in starlight, to over 100,000 lux in direct sunlight. The TSL2561 has features that allow it to handle this huge dynamic range. These settings are similar to a camera; one can change both the sensitivity, which is like an ASA film rating, and the integration time, which is like the shutter speed. Like a camera, you can balance those measurements for the best results.

Lux is a very complex measurement to make because it involves both the human eye’s response to color (frequency) and the concentration of that light (a flashlight will produce a higher lux value than the equivalent bare bulb). The TSL2561 is not a true luxmeter, but the manufacturer of the TSL2561 has characterized its output against professional equipment to come up with lux approximation equations. (You can find these equations in the datasheet, and we’re also using them in our software library.) It should be noted that although these equations will get you in the ballpark, the TSL2561 is not a calibrated instrument (nor is it priced like one). If you need highly accurate results you should at least perform your own calibration. For everyday use however, the TSL2561 is far superior to simpler photoresistors and photodiodes for illumination measurement.
