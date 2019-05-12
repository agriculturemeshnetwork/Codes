#include "ArduinoJson.h"
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
}

void loop() 
{

  //Start the server and wifi to start sendin the JSON data
  Serial.println("Starting sending data to the server");

  int experimentalvalue = 10;
  //Original message being sent to the server
  char JSONMessage[] = " {\"Sensor Type\": \"Temperature\", \"Value\": 10}";
  
  //Dynamically allocating memory in-place
  StaticJsonDocument<300>JSONBuffer; 
  
  //deserializeJson() prase a JSON input and put the result in the JSON document or Buffer 
  auto error = deserializeJson(JSONBuffer,JSONMessage);
  
  if(error){
    //The string in being wrapped by F() because we want it to not use the memory 
    Serial.print(F("Deserlization process failed with the code"));
    Serial.print(error.c_str());
    delay(5000);
    return;
  }
  
  //Pull the sensor type and save the value in the sensor type array
  const char * sensortype = JSONBuffer["Sensor Type"];

  //Pull the value for the talked about sensor
  int value = JSONBuffer["Value"];

  //Printing out the data 
  Serial.print("Sensor type: ");
  Serial.println(sensortype);
  Serial.print("Sensor Value: ");
  Serial.println(value);  

  Serial.println();
  delay(5000);
}
