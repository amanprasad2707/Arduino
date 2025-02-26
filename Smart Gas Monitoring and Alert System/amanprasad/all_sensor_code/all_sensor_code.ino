#define BLYNK_TEMPLATE_ID "TMPL3RngVD2I_"
#define BLYNK_TEMPLATE_NAME "Aman Prasad"
#define BLYNK_AUTH_TOKEN "ZBXRpvsQfGBHSpI0XMdhlD7ScLTLup_R"
#define MQ137 34
#define MQ4 35
#define MQ7 32
#define DHT_PIN 4
#define DHTTYPE DHT11
#define BLYNK_PRINT Serial

const int trigPin = 5;
const int echoPin = 15;

long duration;
int distance;

#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Akhlesh";
char pass[] = "12345678";

DHT dht(DHT_PIN, DHTTYPE);

BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int sensorValueMQ137 = analogRead(MQ137);
  int sensorValueMQ4 = analogRead(MQ4);
  int sensorValueMQ7 = analogRead(MQ7);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor

  
  float concentrationMQ137 = map(sensorValueMQ137, 0, 1023, 0, 100);
  float concentrationMQ4 = map(sensorValueMQ4, 0, 1023, 0, 100);
  float concentrationMQ7 = map(sensorValueMQ7, 0, 1023, 0, 100);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("    Ammonia: ");  // MQ-137
  Serial.print(concentrationMQ137);
  Serial.print("    Methane: ");   // MQ-4
  Serial.print(concentrationMQ4);  
  Serial.print("    Carbon Mono-oxide: ");  // MQ-7
  Serial.print(concentrationMQ7);
  Serial.print("    Temperature: ");
  Serial.print(t);
  Serial.print("    Humidity: ");
  Serial.print(h);

  Serial.print("    Distance: ");
  Serial.println(distance);
  Blynk.virtualWrite(V0, concentrationMQ137);
  Blynk.virtualWrite(V1, concentrationMQ4);
  Blynk.virtualWrite(V2, concentrationMQ7);
  Blynk.virtualWrite(V3, t);
  // Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(V4, distance);
}

void setup() {
  // Debug console
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
