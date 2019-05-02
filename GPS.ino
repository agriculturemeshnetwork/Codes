#include <Arduino.h>

#define RXD2 16
char buf[200];

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1, RXD2);

}

void loop() {
  String out = "";
  int i = 0;
  while ( Serial2.available()) {
    buf[i] = char(Serial2.read());
    Serial.print( buf[i]);
    i++;
  }



}
  
