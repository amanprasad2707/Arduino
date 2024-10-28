#include <IRremoteESP8266.h>
#include <IRrecv.h>

IRrecv irrecv(2);
decode_results results;
const int ledPin = 4;
void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();
  pinMode(ledPin,OUTPUT);
  // Serial.println(results.value, HEX);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results)){
    Serial.println(results.value,HEX);
    if(results.value == 0xFFC03F){
      digitalWrite(ledPin,HIGH);
    }
    else if(results.value == 0xFF906F){
      digitalWrite(ledPin,LOW);
    }
    delay(200);
    irrecv.resume();
    
  }
}
