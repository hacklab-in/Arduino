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
  * SD card attached to SPI bus as follows:
 ** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
 ** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
 ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
 ** CS - depends on your SD card shield or module.
        Pin 4 used here for consistency with other Arduino examples
The SD card examples are already present in the arduino GUI
