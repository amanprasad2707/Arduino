#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Blynk Auth Token (Get from Blynk App)
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";  

// WiFi Credentials
char ssid[] = "YOUR_WIFI_SSID";  
char pass[] = "YOUR_WIFI_PASSWORD";  

// DHT11 Settings
#define DHTPIN D4  // GPIO2 (D4)
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LED Pin
#define LED_PIN D1  // GPIO5 (D1)

// Blynk Virtual Pins
#define TEMP_VPIN V5  // Send Temperature Data
#define HUMI_VPIN V6  // Send Humidity Data
#define LED_VPIN V1   // LED Control from Blynk

BlynkTimer timer;

// Function to send temperature & humidity to Blynk
void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C, Humidity: ");
  Serial.print(h);
  Serial.println("%");

  // Send data to Blynk app
  Blynk.virtualWrite(TEMP_VPIN, t);
  Blynk.virtualWrite(HUMI_VPIN, h);
}

// Function to control LED via Blynk app
BLYNK_WRITE(LED_VPIN) {
  int ledState = param.asInt(); // Get value from Blynk button
  digitalWrite(LED_PIN, ledState);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  
  // Run sendSensorData() every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

