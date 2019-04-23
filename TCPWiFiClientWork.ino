/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>

const char* ssid     = "University of Washington";
const char* password = "";
int nodeNumber = 0;
double temp = 0;
const char* host = "10.16.30.219";
//const char* streamId   = "....................";
//const char* privateKey = "....................";

void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to...");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    Serial.println("WiFi connected :: Start sending data to the server");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    nodeNumber = 1;
    char*sensorName[50] = {"Temprature Sensor"};
    temp = 32.47;
    
    String node = "Node Number: ";
    nodeNumber = 1;
    String nodePrint = node + nodeNumber;

    String name = "Sensor Name: Temprature Sensor";
    String SensorPrint = name;

    String valueName = "Value: ";
    String PrintValue = valueName + temp;
    
    delay(1000);
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 6969;
    if (!client.connect(host, httpPort)) 
    {
        Serial.println("connection failed");
        return;
    }

    //This will send the request to the server
    //client.print(String("GET: Hello World!!!, ")+"Host: " + host + ", " + "Connection: "+ httpPort);
    client.print(nodePrint+"\n"+SensorPrint+"\n"+PrintValue);
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) 
    {
        String line = client.readStringUntil('\r');
        client.print("The server is OKAY!!");
        Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
}
