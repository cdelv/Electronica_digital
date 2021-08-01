#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

WiFiClient client;

#define apiKey "NGU3VJXOEHWUPGCF"
const char* ssid = "Casa";
const char* password = "RaTas%KwC.1";
const char* server = "api.thingspeak.com";
long unsigned int Channel = 1459010;

void WiFi_send_data(float flujo, float nivel, float turbidez, float color)
{
  if(WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid, password);
    Serial.print("Reconecting ");
  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
 Serial.println(" WiFi reconnected");
  }
  
  ThingSpeak.setField(1,flujo);
  ThingSpeak.setField(2,nivel);
  ThingSpeak.setField(3,turbidez);
  ThingSpeak.setField(4,color);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(Channel,apiKey);
  if(x==200)
  {
      Serial.print("Sended to Thingspeak, Flujo= ");
      Serial.print(flujo);
      Serial.print(", Nivel= ");
      Serial.print(nivel);
      Serial.print(", Turbidez= ");
      Serial.print(turbidez);
      Serial.print(", Color= ");
      Serial.println(color);
  }
  
  Serial.println("Waiting ...");
}

void WiFi_set_up(void)
{
  //Setup del WiFi
  WiFi.begin(ssid, password);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("Conecting ");
  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
 Serial.println(" WiFi connected");
 ThingSpeak.begin(client);
}
