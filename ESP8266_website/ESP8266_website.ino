#include <SoftwareSerial.h>
 
#define DEBUG true
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message
  {
/*
while(esp8266.available())
{
// The esp has data so display its output to the serial window
  char c = esp8266.read(); // read the next character.
  Serial.write(c);
} */
    if(esp8266.find("+IPD,"))
    {
      delay(1000);
 
      int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns
// the ASCII decimal value and 0 (the first decimal number) starts at 48
      String webpage = "<h1>Hello</h1>&lth2>World!</h2><button>LED1</button>";
 
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend +=webpage.length();
      cipSend +="\r\n";
      sendData(cipSend,1000,DEBUG);
      sendData(webpage,1000,DEBUG);
      webpage="<button>LED2</button>";
      cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend +=webpage.length();
      cipSend +="\r\n";
      sendData(cipSend,1000,DEBUG);
      sendData(webpage,1000,DEBUG);
 
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand+=connectionId; // append connection id
      closeCommand+="\r\n";
      sendData(closeCommand,3000,DEBUG);
    }
  }
}
 
 
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command); // send the read character to the esp8266
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(esp8266.available())
    {
// The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response+=c;
    }
  }
  if(debug)
  {
    Serial.print(response);
  }
  return response;
}
