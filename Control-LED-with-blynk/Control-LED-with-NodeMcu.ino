
#define BLYNK_TEMPLATE_ID "TMPL38yifX6jb"
#define BLYNK_TEMPLATE_NAME "Control LED"
#define BLYNK_AUTH_TOKEN "O4iLtSxO4TvG49mlZqCfZFGDzju3sOnu"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>
 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "VIRUS";  // Enter your Wifi Username
char pass[] = "12345678";  // Enter your Wifi password

int ledpin = D4;
void setup()
{     
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);    
  pinMode(ledpin,OUTPUT);
}

void loop()
{
  Blynk.run(); 
}