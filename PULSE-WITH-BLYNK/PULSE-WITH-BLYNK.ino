#define BLYNK_TEMPLATE_ID "TMPL3EI8BL9yJ"
#define BLYNK_TEMPLATE_NAME "Pulse"
#define BLYNK_AUTH_TOKEN "gtIAGWnI2_GEa-QAwjTZRvs7xP1fZCld"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <BlynkSimpleEsp32.h>
// #include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h> // Change the WiFi library for NodeMCU
#include <BlynkSimpleEsp8266.h> // Change the Blynk library for NodeMCU

// Define the pulse sensor settings
const int pulsePin = A0; // the pulse sensor pin
const int ledPin = 4; // the LED pin
int pulseValue; // the pulse sensor value
int bpm; // the heart rate in beats per minute

// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "VIRUS";
char pass[] = "VIRUS123";
BlynkTimer timer;

void setup()
 {
  // Start the serial communication
  Serial.begin(9600);
// OLED
  srituhobby.begin(SSD1306_SWITCHCAPVCC, 0x3C);// Address 0x3C for 128x32
  delay(1000);
  srituhobby.clearDisplay();

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
    
    Serial.print(bpm);
    Serial.println(" BPM");

    // Send the heart rate to Blynk
    Blynk.virtualWrite(V1, bpm);
    delay(200);

    // Print the heart rate on the serial monitor
    String message = "Heart rate: " + String(bpm) + " BPM";
    Serial.println(message);
  }

  // Run the Blynk loop
  Blynk.run();
}