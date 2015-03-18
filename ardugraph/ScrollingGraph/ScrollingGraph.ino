/*
  ScrollingGraph

 Peter Corbett 2013

 Adapted from Graph, adjusted to give nice constant timing.
 
 created 2006
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe and Scott Fitzgerald
 
 http://www.arduino.cc/en/Tutorial/Graph
 */

long t;
int mt;
int mut;

void setup() {
  Serial.begin(115200);
  t = micros();
  // Milliseconds to delay
  mt = 0;
  // Microseconds to delay
  mut = 500;
  // It doesn't like taking less than 500 microseconds per
  // cycle - i.e. 2kHz. Possibly this could be increased
  // with more efficient serial (or other) communication.
  // Set up an LED to say if we're taking too long.
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  Serial.println(analogRead(A0));
  // Book our next reading
  t += (1000L * mt) + mut;
  // Wait some number of milliseconds, as delayMicroseconds 
  // doesn't like long waits
  if(mt > 1) delay(mt-1);
  if(micros() > t) {
    // Use the pin 13 LED for emergencies
    digitalWrite(13, HIGH);
    t = micros() + mut;
  }
  // OK, now we've delayed enough milliseconds, delaying to
  // the correct microsecond should work  
  delayMicroseconds(t - micros());
}


