# 1 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino"
# 2 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino" 2
# 3 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino" 2
# 4 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino" 2
# 5 "C:\\Users\\amanp\\Desktop\\Adafruit.io_DHT\\Adafruit.io_DHT.ino" 2

/************************* WiFi Access Point *********************************/




/************************* Adafruit.io Setup *********************************/






/************* DHT11 Setup ********************************************/


DHT dht(2, DHT22);

/************ Global State **********************************************/

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, "io.adafruit.com", 1883, "amanprasad2707", "aio_VkML24u1u6NZcs6XuzSRj59Qatnj");

Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt, "amanprasad2707" "/feeds/temperature");
Adafruit_MQTT_Publish Humidity = Adafruit_MQTT_Publish(&mqtt, "amanprasad2707" "/feeds/humidity");

/*************************** Sketch Code ************************************/

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin("VIRUS", "VIRUS123");
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

  delay(5000); // Wait 5 seconds before next reading
}
