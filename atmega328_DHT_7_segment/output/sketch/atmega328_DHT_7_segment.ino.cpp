#include <Arduino.h>
#line 1 "D:\\Arduino\\atmega328_DHT_7_segment\\atmega328_DHT_7_segment.ino"
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 10
DHT dht(DHTPIN, DHTTYPE);

int var1, var2;
int segA = 0;
int segB = 1;
int segC = 2;
int segD = 3;
int segE = 4;
int segF = 5;
int segG = 6;
int digit1 = 7;
int digit2 = 9;

void setup() {
  // Initialize segment pins as OUTPUT
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  int t = dht.readTemperature(); // Read temperature from DHT11

  if (isnan(t)) {
    // If DHT11 is not connected, turn on only the G segment (active low)
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, LOW); // Only G segment is on
  } else {
    // If DHT11 is connected, display the temperature
    if (t >= 10) {
      var1 = int(t / 10); // Tens digit
      var2 = int(t % 10); // Units digit
    } else {
      var1 = 0; // Leading zero for single-digit temperatures
      var2 = t;
    }

    // Display the tens digit
    displayNumber(var1);
    digitalWrite(digit1, HIGH);
    digitalWrite(digit2, LOW);
    delay(10);

    // Display the units digit
    displayNumber(var2);
    digitalWrite(digit1, LOW);
    digitalWrite(digit2, HIGH);
    delay(10);
  }
}

void displayNumber(int numbertoDisplay) {
  // Turn off all segments initially (active low)
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);

  // Turn on the required segments for the number (active low)
  switch (numbertoDisplay) {
    case 0:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      break;

    case 1:
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      break;

    case 2:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segD, LOW);
      break;

    case 3:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      break;

    case 4:
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      break;

    case 5:
      digitalWrite(segA, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      break;

    case 6:
      digitalWrite(segA, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      break;

    case 7:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      break;

    case 8:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 9:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;
  }
}
