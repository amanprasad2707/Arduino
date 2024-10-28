#include <Arduino.h>
#line 1 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino"
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "VIRUS"
#define WLAN_PASS       "VIRUS123"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "amanprasad2707"
#define AIO_KEY         "aio_VkML24u1u6NZcs6XuzSRj59Qatnj"

/************* DHT11 Setup ********************************************/
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/************ Global State **********************************************/

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish Humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");

/*************************** Sketch Code ************************************/

#line 33 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino"
void connectToWiFi();
#line 45 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino"
void connectToMQTT();
#line 58 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino"
void setup();
#line 66 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino"
void loop();
#line 33 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino"
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
  dht.begin();
  Serial.println("Starting Adafruit MQTT demo");

  connectToWiFi();
}

void loop() {
  if (!mqtt.connected()) {
    connectToMQTT();
  }
  
  // Read sensor data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Publish data
  if (!Temperature.publish(temperature)) {
    Serial.println("Failed to publish temperature");
  }
  if (!Humidity.publish(humidity)) {
    Serial.println("Failed to publish humidity");
  }

  delay(5000);  // Wait 5 seconds before next reading
}

