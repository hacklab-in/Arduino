 #include <i2cmaster.h>
  #include <Servo.h>
  
  //Servo setup
  int servoPin1 = 9;
  int servoPin2 = 10;
  Servo servo1; 
  Servo servo2;
  int angle1 = 40;   // servo start positions in degrees
 int angle2 = 50;
 
 
 //Melexis setup
 int sensor = 0;
 int inByte = 0;
 
 
 void setup()
 {
     Serial.begin(9600);
    
        // attach pan-tilt servos
        servo1.attach(servoPin1);
        servo2.attach(servoPin2);
 
 
        servo1.write(angle1);
        servo2.write(angle2);
 
 
     //Initialise the i2c bus
     i2c_init();
     PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
        establishContact();
 }
 
 
 void loop()
 {
  if (Serial.available() > 0)
   {
    inByte = Serial.read();
    
    int dev = 0x5A<<1;
    int data_low = 0;
    int data_high = 0;
    int pec = 0;
 
 
    i2c_start_wait(dev+I2C_WRITE);
    i2c_write(0x07);
 
 
    // read
    i2c_rep_start(dev+I2C_READ);
    data_low = i2c_readAck(); //Read 1 byte and then send ack
    data_high = i2c_readAck(); //Read 1 byte and then send ack
    pec = i2c_readNak();
    i2c_stop();
 
 
    //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
    double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
    double tempData = 0x0000; // zero out the data
    int frac; // data past the decimal point
 
 
  // Serial.print(tempData);
  // Serial.write(inByte);
    // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
    tempData = (double)(((data_high & 0x007F) << 8) + data_low);
    tempData = (tempData * tempFactor)-0.01;
 
 
    //inByte = (float)(((data_high & 0x007F) << 8) + data_low);
 
 
   float celsius = tempData - 273.15;
    sensor=(int)(celsius*100);
    //float fahrenheit = (celsius*1.8) + 32;
 
   Serial.print(sensor);
  
    
    // horizontal "H"-> 72; reverse "R"-> 82; vertical "V"-> 86; end "E"-> 69
    
   if(inByte==72)
   {
    angle1=angle1+1;
    servo1.write(angle1);
   }
    if(inByte==82)
   {
    angle1=40;
    servo1.write(angle1);
   }
   if(inByte==86)
   {
    angle2=angle2+1;
   servo2.write(angle2);
  }
    if(inByte==69)
  {
   angle1 = 40;   // servo back to start
   angle2 = 50;
   servo1.write(angle1);
   servo2.write(angle2);
  }
 
   delay(15); // 15 works; wait 15 milliseconds before printing again
}


}



void establishContact()
{
while (Serial.available() <= 0)
{
   Serial.print('A');
   delay(100);
}
}
