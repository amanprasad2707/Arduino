#define BLYNK_TEMPLATE_ID "TMPL3kgn639Rp"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "MGksUUAHpifID6PIpSzmpXY5y6GvnWOP"
#include <IRremoteESP8266.h>
#include <IRrecv.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "VIRUS";
char pass [] = "12345678";

IRrecv irrecv(16);      //D0
decode_results results;

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Serial.println(value);
  if (value == 1)
  {
    digitalWrite (D4, LOW);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
    digitalWrite (D4, HIGH);
    Serial.println("LED OFF");
  }
}

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  Serial.println(value);
  if (value == 1)
  {
    digitalWrite (D5, LOW);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
    digitalWrite (D5, HIGH);
    Serial.println("LED OFF");
  }
}
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  Serial.println(value);
  if (value == 1)
  {
    digitalWrite (D6, LOW);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
    digitalWrite (D6, HIGH);
    Serial.println("LED OFF");
  }
}

BLYNK_WRITE(V3)
{
  int value = param.asInt();
  Serial.println(value);
  if (value == 1)
  {
    digitalWrite (D7, LOW);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
    digitalWrite (D7, HIGH);
    Serial.println("LED OFF");
  }
}

void setup()
{
  irrecv.enableIRIn();
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

}

void loop()
{
  if(irrecv.decode(&results)){
    Serial.println(results.value,HEX);
    irrecv.resume();
  }
  Blynk.run();
}
