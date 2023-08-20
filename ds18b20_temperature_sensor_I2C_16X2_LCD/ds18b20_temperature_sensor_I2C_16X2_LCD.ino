// ds18b20 temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 3
// for I2C LCD display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;

void setup() {
  sensors.begin();
  Serial.begin(9600);
  Serial.println("Testing ds18b20 temperature sensor...");
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  lcd.setCursor(0,0);
  lcd.print("WELCOME..");
  delay(3000);
  lcd.clear();
  lcd.print("Initializing...");
  delay(3000);
  lcd.clear();
  lcd.print("Temperature");
}

void loop() {
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

  Serial.print(Celsius);
  Serial.print(" C  ");
  lcd.setCursor(0,1);     // col row
  lcd.print(Celsius);
  lcd.print(" C");
  Serial.print(Fahrenheit);
  Serial.println(" F");
  lcd.setCursor(9,1);
  lcd.print(Fahrenheit);
  lcd.print(" F");
  delay(1000);
}
