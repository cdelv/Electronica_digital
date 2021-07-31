#include <ESP8266WiFi.h>

WiFiClient client;
String apiKey = "QH1RPZP6AG39OTN3";
const char* ssid = "Casa";
const char* password = "RaTas%KwC.1";
const char* server = "api.thingspeak.com";

void WiFi_send_data(float flujo, float nivel, float turbidez, float color)
{
    if (client.connect(server,80)) 
    {
      String postStr = apiKey;
      postStr +="&field1=";
      postStr += String(flujo);
      postStr +="&field2=";
      postStr += String(nivel);
      postStr +="&field3=";
      postStr += String(turbidez);
      postStr +="&field4=";
      postStr += String(color);
      postStr += "\r\n\r\n";
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
      Serial.print("% send to Thingspeak, Flujo= ");
      Serial.print(flujo);
      Serial.print(", Nivel= ");
      Serial.print(nivel);
      Serial.print(", Turbidez= ");
      Serial.print(turbidez);
      Serial.print(", Color= ");
      Serial.println(color);
  }
  client.stop();
}
void WiFi_set_up(void)
{
  //Setup del WiFi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.print("Conecting ");
  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(200);
      Serial.print(".");
    }
}
