#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <OneWire.h>
#include <DallasTemperature.h>

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "Block-G"
#define WLAN_PASS       "Rise@2023"

/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "amanprasad2707"
#define AIO_KEY         "aio_VkML24u1u6NZcs6XuzSRj59Qatnj"

/************************* DS18B20 Setup *************************************/
#define ONE_WIRE_BUS 2 // Pin connected to DS18B20 data line
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/************************* Capacitive Moisture Sensor Setup ******************/
#define MOISTURE_PIN A0 // Pin connected to moisture sensor

/************ Global State ***************************************************/
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish Moisture = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/moisture");

/*************************** Sketch Code *************************************/

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToMQTT() {
  Serial.print("Connecting to MQTT...");
  while (!mqtt.connected()) {
    if (mqtt.connect()) {
      Serial.println("Connected!");
    } else {
      Serial.print("Failed, retrying in 5 seconds. Error: ");
      Serial.println(mqtt.connectErrorString(mqtt.connect()));
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  sensors.begin();  // Start DS18B20 temperature sensor
  Serial.println("Starting Adafruit MQTT demo");

  connectToWiFi();
}

void loop() {
  if (!mqtt.connected()) {
    connectToMQTT();
  }

  // Request temperature readings from DS18B20
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0); // Get temperature from first sensor
  
  // Read moisture sensor value
  int moistureVal = analogRead(MOISTURE_PIN);
  
  // Map moisture value to percentage (4 = 0%, 900 = 100%)
  int moisturePercent = map(moistureVal, 4, 900, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100); // Ensure value is between 0 and 100
  
  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Moisture: ");
  Serial.print(moisturePercent);
  Serial.print(" %");
  Serial.print("  moisture voltage: ");
  Serial.println(moistureVal);

  // Publish data to Adafruit IO
  if (!Temperature.publish(temperature)) {
    Serial.println("Failed to publish temperature");
  }
  if (!Moisture.publish(moisturePercent)) {
    Serial.println("Failed to publish moisture percentage");
  }

  delay(5000);  // Wait 5 seconds before next reading
}
