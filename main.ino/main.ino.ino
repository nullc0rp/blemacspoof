#include <MagSpoof.h>

#include <SoftwareSerial.h>

#include "MagSpoof.h"

#define PIN_A       6      // L293D pin 2
#define PIN_B       7      // L293D pin 7
#define PIN_ENABLE  13     // L293D pin 1; Using Arduino pin 13 to switch on embedded LED during transmission
#define CLOCK_US    400    // Delay for bit transmission, in micro seconds

MagSpoof magSpoof(PIN_A, PIN_B, PIN_ENABLE, CLOCK_US, MagSpoof::BPC7, MagSpoof::Odd);

SoftwareSerial BTSerial(4, 5);

char* code = "holanene";
String codeString = "";
char codeArray[500]; //Overkill, I don't care

void setup() {
   Serial.begin(9600);
   BTSerial.begin(9600);
   //BTSerial.write("AT+DEFAULT\r\n");
   //BTSerial.write("AT+RESET\r\n");
   //BTSerial.write("AT+NAME=Controller\r\n");
   //BTSerial.write("AT+ROLE1\r\n");
   //BTSerial.write("AT+TYPE1"); //Simple pairing

   magSpoof.setup();
}
 
void loop()
{
   if (BTSerial.available())
      codeString = BTSerial.readString();
      codeString.toCharArray(codeArray, codeString.length());
      code = codeArray;
      BTSerial.read();
      Serial.println(codeString);
   if (Serial.available())
       BTSerial.println(Serial.readString());
   delay(2000);
   magSpoof.playTrack(code);
}
