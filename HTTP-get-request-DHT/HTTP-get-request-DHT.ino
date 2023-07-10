#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

DHT dht(D5, DHT11);

String host = "api.thingspeak.com";
int httpPort = 80;
String apiKey = "NNDIZZW7HU5FWMQR";

WiFiClient client;
HTTPClient http;

void setup()
{
  Serial.begin(9600);
  WiFi.begin("VIRUS", "12345678");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + String(t));
  Serial.println("Humidity: " + String(h));

  String url1 = "/update?api_key=" + apiKey + "&field1=" + String(t);
  http.begin(client, host, httpPort, url1);
  int httpCode = http.GET();
  Serial.println(httpCode);
  http.end();
  delay(2000);

  String url2 = "/update?api_key=" + apiKey + "&field2=" + String(h);
  http.begin(client, host, httpPort, url2);
  httpCode = http.GET();
  Serial.println(httpCode);
  http.end();
  delay(2000);
}
