int sensorPin = A0;
int sensorThreshold = 250;

void setup() {
   // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(sensorPin, INPUT);
}

void loop() {
   // put your main code here, to run repeatedly:
   if (analogRead(sensorPin) > sensorThreshold) {
      Serial.println("Gas concentration too high!");
      delay(1000);
   } else {
      Serial.println("Gas concentration in control");
      Serial.println(analogRead(sensorPin));
      delay(1000);
   }
}

