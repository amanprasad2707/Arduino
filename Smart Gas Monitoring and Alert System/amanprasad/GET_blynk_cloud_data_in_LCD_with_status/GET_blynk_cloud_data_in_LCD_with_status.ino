#include <LiquidCrystal_I2C.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

const char* ssid = "VIRUS";
const char* password = "VIRUS123";
const char* serverUrl = "https://blr1.blynk.cloud/external/api/getAll?token=CGCkx8lRfAb50kVnsxPEx1TuXb9HGxks";
const char* statusUrl = "https://blr1.blynk.cloud/external/api/isHardwareConnected?token=CGCkx8lRfAb50kVnsxPEx1TuXb9HGxks";

// Variables to store extracted values
int variable1;
int variable2;
int variable3;
int variable4;
int variable5;

void setup() {
  Serial.begin(115200);
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  // lcd.noBacklight();   // turn off the LCD screen backlight
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");
    delay(3000);
  lcd.clear();
  }
  Serial.println("Connected to WiFi");
  lcd.setCursor(0, 0);
  lcd.print("Connected");
  delay(3000);
  lcd.clear();

  // Make HTTP GET request
  Serial.print("Fetching JSON data from: ");
  Serial.println(serverUrl);
  lcd.setCursor(0, 0);
  lcd.print(" Fetching Data from  Blynk Cloud.....");
  delay(3000);
  lcd.clear();
  // fetchJsonData();
}

void loop() {
  // Your code here
  // Make HTTP GET request
  fetchJsonData();
  isConnected();
}

void fetchJsonData() {
  HTTPClient http;

  // Serial.print("Fetching JSON data from: ");
  // Serial.println(serverUrl);
  // lcd.setCursor(0, 0);
  // lcd.print(" Fetching Data from  Blynk Cloud.....");
  // delay(3000);
  // lcd.clear();


  http.begin(serverUrl);

  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Received JSON data:");
      Serial.println(payload);

      // Parse JSON data
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);

      // Access JSON elements and assign values to variables
      variable1 = doc["v0"].as<int>();  // Replace "key1" with the actual key in your JSON
      variable2 = doc["v1"].as<int>();
      variable3 = doc["v2"].as<int>();
      variable4 = doc["v3"].as<int>();
      variable5 = doc["v4"].as<int>();

      // Print the extracted values
      Serial.println("Variable 1: " + String(variable1));
      Serial.println("Variable 2: " + String(variable2));
      Serial.println("Variable 3: " + String(variable3));
      Serial.println("Variable 4: " + String(variable4));
      Serial.println("Variable 5: " + String(variable5));
      // print data on lcd

      lcd.setCursor(0, 0);
      lcd.print("NH3 :");
      lcd.print(variable1);
      lcd.setCursor(8,0);
      lcd.print("ppm|");
      lcd.setCursor(0,1);  // col row
      lcd.print("CH4 :");
      lcd.print(variable2);
      lcd.setCursor(8,1);
      lcd.print("ppm|");
      lcd.setCursor(0,2); 
      lcd.print("CO  :");
      lcd.print(variable3);
      lcd.setCursor(8,2);
      lcd.print("ppm|");
      lcd.setCursor(0,3);
      lcd.print("Temp:");
      lcd.print(variable4);
      lcd.print((char)223);
      lcd.print("C  |");
      lcd.setCursor(12,0);
      lcd.print("Dis:");
      lcd.print(variable5);
      lcd.setCursor(18,0);
      lcd.print("cm");
      delay(1000);
      // lcd.clear();
    } else {
      Serial.printf("HTTP request failed with error code: %d\n", httpCode);
    }
  } else {
    Serial.println("Unable to connect to server");
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Unable to connect to server");
  }

  http.end();
}

void isConnected(){
  HTTPClient http;
  http.begin(statusUrl);
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.print("Device is connected:");
      Serial.println(payload);
      if(payload == "false"){
        Serial.println("offline");
        lcd.setCursor(13,2);
        lcd.print("OFFLINE");
        // display offline
      }if(payload == "true"){
        // display online
        Serial.println("online");
        lcd.setCursor(13,2);
        lcd.print("ONLINE");
      }
      // Parse JSON data
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      }else {
      Serial.printf("HTTP request failed with error code: %d\n", httpCode);
    }
  } else {
    Serial.println("Unable to connect to server");
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Unable to connect to server");
  }

  http.end();


}
