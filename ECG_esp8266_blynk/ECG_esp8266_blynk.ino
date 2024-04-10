#define BLYNK_TEMPLATE_ID "TMPL3EI8BL9yJ"
#define BLYNK_TEMPLATE_NAME "Pulse"
#define BLYNK_AUTH_TOKEN "gtIAGWnI2_GEa-QAwjTZRvs7xP1fZCld"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



char auth[] = BLYNK_AUTH_TOKEN; // Enter your Blynk authentication token here
char ssid[] = "VIRUS"; // Enter your WiFi SSID here
char pass[] = "VIRUS123"; // Enter your WiFi password here

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(14, INPUT); // Setup for leads off detection LO +
  pinMode(12, INPUT); // Setup for leads off detection LO -
  
  Blynk.begin(auth, ssid, pass); // Initialize Blynk with your authentication token and WiFi credentials
}

void loop() {
  
  
  if ((digitalRead(10) == 1) || (digitalRead(11) == 1)) {
    Serial.println('!'); // Print '!' if leads off detection occurs
  } else {
    int sensorValue = analogRead(A0); // Read the sensor value from analog pin A0
    Serial.println(sensorValue); // Print the sensor value
    Blynk.virtualWrite(V0, sensorValue); // Send the sensor value to Blynk virtual pin V0
  }
  Blynk.run(); // Run Blynk to process incoming commands
  
  delay(1); // Wait for a short period to avoid saturating serial data
}
