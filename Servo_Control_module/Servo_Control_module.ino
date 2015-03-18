void setup() {
Serial.begin(9600);
}

void loop() {
move(1,2000, 100);// move servo number 1 to position 2000 for 100 millisecond
move(1,1000, 100);// move servo number 1 to position 2000 for 100 millisecond
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
