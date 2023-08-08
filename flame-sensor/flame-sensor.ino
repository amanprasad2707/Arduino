int Flame = 2; // Flame sensor connected to digital pin 2
int buzzer = 3;
void setup(){
  pinMode(Flame, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}
void loop() {
if(digitalRead(Flame) == LOW){ 
  digitalWrite(buzzer,HIGH);
  Serial.println("Flame Detected");
}
else{
  digitalWrite(buzzer,LOW);
  Serial.println("No Flame Detected..");
}
delay(1000);
}