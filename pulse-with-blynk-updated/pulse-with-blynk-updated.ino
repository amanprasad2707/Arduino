#define BLYNK_TEMPLATE_ID "TMPL3EI8BL9yJ"
#define BLYNK_TEMPLATE_NAME "Pulse"
#define BLYNK_AUTH_TOKEN "gtIAGWnI2_GEa-QAwjTZRvs7xP1fZCld"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PulseSensorPlayground.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "VIRUS";
char pass[] = "VIRUS123";

const int PulseWire = A0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
int Threshold = 550;      // Default threshold value, adjust as needed

PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
    Serial.println("Pulse sensor initialized successfully");
  } else {
    Serial.println("Error initializing pulse sensor");
  }
}

void loop() {
  Blynk.run();
  int BPM = pulseSensor.getBeatsPerMinute();
  if (BPM > 0) {
    Serial.print("BPM: ");
    Serial.println(BPM);
    Blynk.virtualWrite(V1, BPM);
  }
  delay(10); // Adjust delay as needed to avoid overwhelming Blynk server
}
