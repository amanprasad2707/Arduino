// #include <IRremoteESP8266.h>
#include <IRrecv.h>

IRrecv irrecv(14);      //D5
decode_results results;
const int led1 = D2;
const int led2 = D3;
void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  Serial.begin(9600);

}
void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results)){
    Serial.println(results.value,HEX);
    if(results.value == 0xFFC03F){
      digitalWrite(led1,HIGH);
    }
    else if(results.value == 0xFF906F){
      digitalWrite(led1,LOW);
    }
    if(results.value == 0xFFB04F){
      digitalWrite(led2,HIGH);
    }
    else if(results.value == 0xFFD827)
    digitalWrite(led2,LOW);
    delay(1000);
    irrecv.resume();
    
  }
}
