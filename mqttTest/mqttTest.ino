#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "VIRUS";
const char* password = "VIRUS123";

// ThingSpeak MQTT server and port
const char* mqtt_server = "mqtt3.thingspeak.com";
const int mqtt_port = 1883;

// ThingSpeak channel details
const char* mqtt_username = "BSc5OiknBwwHOhwbMywoGQc"; // Replace with your ThingSpeak channel ID
const char* mqtt_password = "8z4HiERkMoAHenj/Xk754Qtc"; // Replace with your ThingSpeak Write API Key

// Initialize DHT sensor
#define DHTPIN 2 // Pin where the DHT sensor is connected
#define DHTTYPE DHT11 // DHT 11 sensor
DHT dht(DHTPIN, DHTTYPE);

// Create an instance of the ESP8266 WiFi client
WiFiClient espClient;
// Create an instance of the PubSubClient class
PubSubClient client(espClient);

// Function to connect to the WiFi network
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to connect to the MQTT server
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP8266Client", mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  dht.begin();
  
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Create the payload message
  String payload = String("{\"field1\":") + temperature + ",\"field2\":" + humidity + "}";

  // Publish the data to ThingSpeak
  if (client.publish("channels/BSc5OiknBwwHOhwbMywoGQc/publish/fields/1", payload.c_str())) { // Replace with your topic
    Serial.println("Data published successfully");
  } else {
    Serial.println("Failed to publish data");
  }

  // Wait for 30 seconds before publishing again
  delay(1000);
}
