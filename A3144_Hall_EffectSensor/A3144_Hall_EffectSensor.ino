int sensorPin = 2;
int counter = 0;
boolean sensorState = false;

void setup() 
{
  // setup serial - diagnostics - port
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
}

void loop() 
{
  
  if(magnetPresent(sensorPin) && !sensorState)
  {
    sensorState = true;
    printMessage("Magnet Present");
  }
  else if(!magnetPresent(sensorPin) && sensorState)
  {
    sensorState = false;
    printMessage("Magnet Gone");
  }
 
}

void printMessage(String message){
  counter++;
  Serial.print(counter);
  Serial.print(" ");
  Serial.println(message);
//  delay(1000);
}

boolean magnetPresent(int pin){
  return digitalRead(pin) == LOW;
}

