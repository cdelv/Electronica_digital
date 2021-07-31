#include <WiFiServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

#include <ThingSpeak.h>

//#include <ESP8266WiFi.h>

// ThingSpeak server data
#define CHANNEL_ID 1459010
#define CHANNEL_API_KEY "QH1RPZP6AG39OTN3"

WiFiClient client;

// WiFi client data
#define WIFI_TIMEOUT_MS 20000
#define WIFI_NETWORK "Casa"
#define WIFI_PASSWORD "RaTas%KwC.1"

void connectToWiFi(){
  Serial.print("Conecting to WiFi");
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  //keep looping while we are not connected and havent reached the time out
  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  //Make shure we are connected, otherwise go to sleep
  if(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(" Failed!");
  }
  else
  {
    Serial.print(" Connected!");
    Serial.print(WiFi.localIP());
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectToWiFi();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:

  float Data=2.2;

//set the variables to send and to what channels
  ThingSpeak.setField(1,Data);
  ThingSpeak.setField(2,Data);
  ThingSpeak.setField(3,Data);

  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);

  delay(15000);
}
