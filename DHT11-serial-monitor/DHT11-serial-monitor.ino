<<<<<<< HEAD
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2 // GPIO 2 == D4
DHT dht(DHTPIN,DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DHT11 Test!");
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if(isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read DHT11 sensor data...");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" ");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C ");

  Serial.print("Temperature: ");
  Serial.print(f);
  Serial.println("°F ");
=======
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2 // GPIO 2 == D4
DHT dht(DHTPIN,DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DHT11 Test!");
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if(isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read DHT11 sensor data...");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C");

  Serial.print("Temperature: ");
  Serial.print(f);
  Serial.println("°F");
>>>>>>> 9c53fa28f54a5e9465d0d4b6920c46a03efdbf91
}