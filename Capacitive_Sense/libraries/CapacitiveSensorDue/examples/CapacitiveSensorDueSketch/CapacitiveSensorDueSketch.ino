#include <CapacitiveSensorDue.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger
 * resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this
 * pin.
 */

CapacitiveSensorDue cs_4_2 = CapacitiveSensorDue(4,2);	// 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensorDue cs_4_6 = CapacitiveSensorDue(4,6);	// 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensorDue cs_4_8 = CapacitiveSensorDue(4,8);	// 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()					
{
	Serial.begin(9600);
}

void loop()					
{
	long start = millis();
	long total1 = cs_4_2.read(30);
	long total2 = cs_4_6.read(30);
	long total3 = cs_4_8.read(30);
	
	Serial.print(millis() - start);	// check on performance in milliseconds
	Serial.print("\t");				// tab character for debug windown spacing
	
	Serial.print(total1);			// print sensor output 1
	Serial.print("\t");
	Serial.print(total2);			// print sensor output 2
	Serial.print("\t");
	Serial.println(total3);			// print sensor output 3
	
	delay(10);						// arbitrary delay to limit data to serial port
}
