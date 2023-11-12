//*** By Zafer YILDIZ YouTobe ***

#include "SevSeg.h"
 SevSeg Display;  
 const unsigned long period = 1000;  
 const unsigned long led_period = 500;  
 unsigned long startMillis;  
 unsigned long led_startMillis;  
 unsigned long currentMillis;  
 unsigned long led_currentMillis;  
 
 const int hrs_btn = A5;  
 const int min_btn = A4;  
 const int ledPin = 13;  
 
 int Hrs = 12;  
 int Min = 0;  
 int Sec = 0;  
 int Time;  
 int ledState = LOW;  
 void setup()  
 {  
 pinMode(hrs_btn, INPUT_PULLUP);  
 pinMode(min_btn, INPUT_PULLUP);  
 pinMode(ledPin, OUTPUT);  
 byte numDigits = 4;  
 
 byte digitPins[] = {A3, A2, A1, A0};  
 byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8};  
 
 bool resistorsOnSegments = true;  
 bool updateWithDelaysIn = true;  
  
 byte hardwareConfig = COMMON_ANODE;
   
 Display.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);  
 Display.setBrightness(100);  
 }  
 void loop()  
 {  
 currentMillis = millis();  
 if (currentMillis - startMillis >= period)  
 {  
 Sec = Sec + 1;  
 startMillis = currentMillis;  
 }  
 led_currentMillis = millis();  
 if (led_currentMillis - led_startMillis >= led_period)  
 {  
 led_startMillis = led_currentMillis;  
 if (ledState == LOW)  
 {  
 ledState = HIGH;  
 if (digitalRead(hrs_btn) == LOW)  
 {  
 Hrs = Hrs + 1;  
 }  
 if (digitalRead(min_btn) == LOW)  
 {  
 Min = Min + 1;  
 Sec = 0;  
 }  
 }  
 else  
 {  
 ledState = LOW;  
 }  
 digitalWrite(ledPin, ledState);  
 }  
 if (Sec == 60)  
 {  
 Sec = 0;  
 Min = Min + 1;  
 }  
 if (Min == 60)  
 {  
 Min = 0;  
 Hrs = Hrs + 1;  
 }  
 if (Hrs == 13)  
 {  
 Hrs = 1;  
 }  
 Time = Hrs * 100 + Min;  
 Display.setNumber(Time);  
 Display.refreshDisplay();  
 }  
