# 1 "D:\\Arduino\\Smart Gas Monitoring and Alert System\\amanprasad\\all_sensor_code\\all_sensor_code.ino"
# 11 "D:\\Arduino\\Smart Gas Monitoring and Alert System\\amanprasad\\all_sensor_code\\all_sensor_code.ino"
const int trigPin = 5;
const int echoPin = 15;

long duration;
int distance;

# 18 "D:\\Arduino\\Smart Gas Monitoring and Alert System\\amanprasad\\all_sensor_code\\all_sensor_code.ino" 2
# 19 "D:\\Arduino\\Smart Gas Monitoring and Alert System\\amanprasad\\all_sensor_code\\all_sensor_code.ino" 2
# 20 "D:\\Arduino\\Smart Gas Monitoring and Alert System\\amanprasad\\all_sensor_code\\all_sensor_code.ino" 2

char auth[] = "CGCkx8lRfAb50kVnsxPEx1TuXb9HGxks";

char ssid[] = "VIRUS";
char pass[] = "VIRUS123";

DHT dht(4, DHT11);

BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int sensorValueMQ137 = analogRead(34);
  int sensorValueMQ4 = analogRead(35);
  int sensorValueMQ7 = analogRead(25);
  digitalWrite(trigPin, 0x0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 0x1);
delayMicroseconds(10);
digitalWrite(trigPin, 0x0);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, 0x1);
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor


  float concentrationMQ137 = map(sensorValueMQ137, 0, 1023, 0, 100);
  float concentrationMQ4 = map(sensorValueMQ4, 0, 1023, 0, 100);
  float concentrationMQ7 = map(sensorValueMQ7, 0, 1023, 0, 100);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("    Ammonia: "); // MQ-137
  Serial.print(concentrationMQ137);
  Serial.print("    Methane: "); // MQ-4
  Serial.print(concentrationMQ4);
  Serial.print("    Carbon Mono-oxide: "); // MQ-7
  Serial.print(concentrationMQ7);
  Serial.print("    Temperature: ");
  Serial.print(t);
  Serial.print("    Humidity: ");
  Serial.print(h);

  Serial.print("    Distance: ");
  Serial.println(distance);
  Blynk.virtualWrite(0, concentrationMQ137);
  Blynk.virtualWrite(1, concentrationMQ4);
  Blynk.virtualWrite(2, concentrationMQ7);
  Blynk.virtualWrite(3, t);
  // Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(4, distance);
}

void setup() {
  // Debug console
  Serial.begin(9600);
  pinMode(trigPin, 0x03); // Sets the trigPin as an Output
  pinMode(echoPin, 0x01); // Sets the echoPin as an Input
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
