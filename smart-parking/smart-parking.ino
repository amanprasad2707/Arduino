// Define Blynk template credentials (mandatory for Blynk 2.0)
#define BLYNK_TEMPLATE_ID "TMPL3dKJTBwmb"
#define BLYNK_TEMPLATE_NAME "SmartParking"
#define BLYNK_AUTH_TOKEN "W14XdIAheKyUrEeUElY44Ki1LEnpon8c"
#define BLYNK_PRINT Serial

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// LCD setup (I2C address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// IR sensor pin assignments
#define SLOT1 14
#define SLOT2 26
#define SLOT3 27

// WiFi credentials
char ssid[] = "VIRUS";
char pass[] = "VIRUS123";

// Variables to store sensor values
int slot1Status, slot2Status, slot3Status;

void setup() {
  // Serial monitor for debugging
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Set IR sensor pins as input
  pinMode(SLOT1, INPUT);
  pinMode(SLOT2, INPUT);
  pinMode(SLOT3, INPUT);

  // Start Blynk connection
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  delay(1000);
}

void loop() {
  Blynk.run();

  // Read IR sensor values
  slot1Status = digitalRead(SLOT1);
  slot2Status = digitalRead(SLOT2);
  slot3Status = digitalRead(SLOT3);

  // Update LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Available slots:");

  lcd.setCursor(0, 1);
  lcd.print(slot1Status + slot2Status + slot3Status);

  // Send slot status to Blynk app
  Blynk.virtualWrite(V0, (slot1Status == LOW) ? 1 : 0);
  Blynk.virtualWrite(V1, (slot2Status == LOW) ? 1 : 0);
  Blynk.virtualWrite(V2, (slot3Status == LOW) ? 1 : 0);

  delay(2000);  // Delay for readability and avoid spamming Blynk
}
