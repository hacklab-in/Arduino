void setup() {
Serial.begin(9600);
}

void loop() {
move(1,2000, 100);
move(1,1000, 100);
}

void move(int servo, int position, int time) {
Serial.print("#");
Serial.print(servo);
Serial.print("P");
Serial.print(position);
Serial.print("T");
Serial.println(time);
delay(time);
}
