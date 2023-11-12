#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 3 // GPIO 2 == D4
DHT dht(DHTPIN,DHTTYPE);
int var1, var2;
int segA = 16;
int segB = 5;
int segC = 4;
int segD = 0;
int segE = 14;
int segF = 12;
int segG = 13;
int digit1 = 2;
int digit2 = 15;
void setup() {
  // put your setup code here, to run once:
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
  Serial.println("Counting begins..");
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  // delay(2000);
  int t = dht.readTemperature();
  if(isnan(t))
  {
    Serial.println("Failed to read DHT11 sensor data...");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C ");



  if (t>=10) {
  var1 = int(t/10);
  var2 = int(t%10);
  displayNumber(var1);
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, LOW);
  delay(10);
  displayNumber(var2);
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, HIGH);
  delay(10);
  
  }
  else{
    var1 = t;
    var2 = 0;
    displayNumber(var2);
    digitalWrite(digit1, HIGH);
    digitalWrite(digit2, LOW);
    delay(10);
    displayNumber(var1);
    digitalWrite(digit1, LOW);
    digitalWrite(digit2, HIGH);
    delay(10);
  }
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
      digitalWrite(segG, LOW);
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

