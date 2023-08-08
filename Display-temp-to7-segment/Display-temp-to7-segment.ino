int a, b;
int i = 2150;

#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 1
DHT dht(DHTPIN,DHTTYPE);

int segA = D0;
int segB = D1;
int segC = D2;
int segD = D3;
int segE = D4;
int segF = D5;
int segG = D6;

int digit1 = D7;
int digit2 = D8; 

void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  Serial.begin(9600);
  Serial.println("start");
  dht.begin();
}

void loop() {
    delay(2000);
  float h = dht.readHumidity();
  int t = dht.readTemperature();
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
    a = int(t/10);
    b = int(t%10);
    displayNumber(a);
    digitalWrite(digit1, HIGH);
    digitalWrite(digit2, LOW);
    delayMicroseconds(i);
    displayNumber(b);
    digitalWrite(digit1, LOW);
    digitalWrite(digit2, HIGH);
    delayMicroseconds(i);
  }

void displayNumber(int numbertoDisplay){
  switch(numbertoDisplay){
    case 0:
      digitalWrite(segA, LOW );
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);     //Generating 8
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;

    case 1:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);       //Generating 1
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 2:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);      //Generating 2
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      break;

    case 3:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);      //Generating 3
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segF, LOW);
      break;

    case 4:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);     //Generating 4
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 5:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, HIGH);     //Generating 5
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 6:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);    //Generating 6
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 7:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);   //Generating 7
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 8:
      digitalWrite(segA, LOW );
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);     //Generating 8
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 9:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, HIGH);    //Generating 9
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

  }
}
