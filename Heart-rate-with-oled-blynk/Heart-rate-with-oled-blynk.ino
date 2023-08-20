#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


#define BLYNK_TEMPLATE_ID "TMPL3xoOrdgHJ"
#define BLYNK_TEMPLATE_NAME "Pulse"
#define BLYNK_AUTH_TOKEN "M-B6FKGiq-BhYAJ5CDcDTvsenKSEOjBx"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
// #include <WiFi.h>
// #include <WiFiClient.h>          // for ESP32
// #include <BlynkSimpleEsp32.h>
// #include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h> // Change the WiFi library for NodeMCU
#include <BlynkSimpleEsp8266.h> // Change the Blynk library for NodeMCU

// Define the pulse sensor settings
const int pulsePin = A0; // the pulse sensor pin
const int ledPin = 14; // the LED pin
int pulseValue; // the pulse sensor value
int bpm; // the heart rate in beats per minute


// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Block-G";
char pass[] = "Rise@2023";
BlynkTimer timer;

void setup()
 {
  // Start the serial communication
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
  while (!Blynk.connected()) {
    Serial.println("Connecting to Blynk...");
    delay(1000);
  }
  Serial.println("Connected to Blynk");

  // Set up the pulse sensor
  pinMode(pulsePin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);




  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  // delay(2000);
  // display.clearDisplay();

  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // display.setCursor(20, 20);
  // Display static text
  // display.println("Aman"); 
  // display.display(); 

}

void loop()
 {
  // Read the pulse sensor value
  pulseValue = analogRead(pulsePin);

  // Detect the pulse
  if (pulseValue > 600) {
    digitalWrite(ledPin, HIGH); // turn on the LED
    delay(100); // wait for a short time
    digitalWrite(ledPin, LOW); // turn off the LED
    bpm = 60000 / pulseValue; // calculate the heart rate in beats per minute
    Serial.print("Heart rate: ");
    delay(2000);
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Heart rate");
    // display.display();
    Serial.print(bpm);
    display.setCursor(30, 30);
    display.print(bpm);
    display.println(" BPM");
    display.display();
    Serial.println(" BPM");

    // Send the heart rate to Blynk
    Blynk.virtualWrite(V0, bpm);
    delay(200);

    // Print the heart rate on the serial monitor
    String message = "Heart rate: " + String(bpm) + " BPM";
    Serial.println(message);
  }

  // Run the Blynk loop
  Blynk.run();
}