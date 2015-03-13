
/****************************************************************************
   HC-SR04 : test program for ultrasonic module


   Author: Enrico Formenti
   Permissions: MIT licence
   
   Remarks:
      
*****************************************************************************/





const uint8_t trigPin = 4;
const uint8_t echoPin = 2;
 
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}
 
void loop()
{
  
  uint32_t duration; // duration of the round trip
  uint32_t cm;        // distance of the obstacle
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);


  // Start trigger signal


  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (uint32_t)((duration<<4)+duration)/1000.0; // cm = 17 * duration/1000
                                
  Serial.print(cm);
  Serial.print(" centimeters");
  Serial.println();
 
  delay(100);
}


