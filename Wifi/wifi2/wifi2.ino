#include <Arduino.h>
#include "sensors.h"
#include "wifi.h"

void setup(){
  Serial.begin(9600);
  delay(1000);

  //definir entradas de sensores
   sensors_set_up();

 //Wifi set up
  WiFi_set_up();
}

void loop(){
  float flujo=Flujo();
  float nivel=Distance(D1, D2);
  float turbidez=Turbidez();
  float color=Color();

  WiFi_send_data(flujo, nivel, turbidez, color);
  //Serial.println(flujo);
  
  delay(15000);
}
