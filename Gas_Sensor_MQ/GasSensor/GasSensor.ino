// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int ledPin = 13;                 // LED connected to digital pin 13

int sensorValue = 0;        // value read from the sensor




void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // determine alarm status
  if (sensorValue >= 750)
  {
    digitalWrite(ledPin, HIGH);   // sets the LED on
  }
  else
  {
  digitalWrite(ledPin, LOW);    // sets the LED off
  }

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);     

  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);                     
}

