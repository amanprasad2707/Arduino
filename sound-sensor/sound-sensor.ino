#define sensorPin 8
// #define LED 2
bool is_on = false;
// Variable to store the time when last event happened
unsigned long lastEvent = 0;
void setup() {
	pinMode(sensorPin, INPUT);	// Set sensor pin as an INPUT
  // pinMode(LED, OUTPUT);
	Serial.begin(9600);
  Serial.println("testing sound sensor..");
}

void loop() {
	// Read Sound sensor
	int sensorData = digitalRead(sensorPin);
  // Serial.println(sensorData);
  // delay(1000);

	// If pin goes LOW, sound is detected
	if (sensorData == LOW) {
		
		// If 25ms have passed since last LOW state, it means that
		// the clap is detected and not due to any spurious sounds
		if (millis() - lastEvent > 25) {
			Serial.println("Clap detected!");
		}
		// Remember when last event happened
		lastEvent = millis();
	}
}
