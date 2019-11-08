#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <DHT.h>

//Replace your wifi credentials here
const char* ssid     = "Your WiFi SSID";
const char* password = "Your WiFi Password";

unsigned long myChannelNumber = Your ThingSpeak Channel Number;
const char * myWriteAPIKey = "Your ThingSpeak Write API Key";

#define DHTPIN D2
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321 or DHT11 (Blue Sensor)
DHT dht(DHTPIN, DHTTYPE);

WiFiClient  client;

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(D2, INPUT);
  
  WiFi.begin(ssid,password);                    // initialize wifi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                //print local IP address
  ThingSpeak.begin(client);

}
 
void loop() {
  float h = dht.readHumidity();                  // read temperature sensor
  float t = dht.readTemperature();               // read humidity sensor
  Serial.println("temperature : ");
  Serial.println(t);
  Serial.println("humidity : ");
  Serial.println(h);
  delay (2000); 
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 
}
