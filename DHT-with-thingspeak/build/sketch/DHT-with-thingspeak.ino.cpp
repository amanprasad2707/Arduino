#include <Arduino.h>
#line 1 "D:\\Arduino\\DHT-with-thingspeak\\DHT-with-thingspeak.ino"
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

DHT dht(2, DHT11);

WiFiClient client;

long myChannelNumber = 2215718;
const char myWriteAPIKey[] = "NNDIZZW7HU5FWMQR";

#line 12 "D:\\Arduino\\DHT-with-thingspeak\\DHT-with-thingspeak.ino"
void setup();
#line 28 "D:\\Arduino\\DHT-with-thingspeak\\DHT-with-thingspeak.ino"
void loop();
#line 12 "D:\\Arduino\\DHT-with-thingspeak\\DHT-with-thingspeak.ino"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("VIRUS", "VIRUS123");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(200);
}
