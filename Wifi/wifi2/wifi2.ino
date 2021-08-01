#include <Arduino.h>
#include "sensors.h"
#include "wifi.h"


void setup(){
  Serial.begin(9600);
  delay(1000);

 //Wifi set up
  WiFi_set_up();
  
  //definir entradas de sensores
   sensors_set_up();
}

void loop(){
  float flujo=Flujo();
  float nivel=Distance(D0, D1);
  float turbidez=Turbidez();
  float color=Color();

  WiFi_send_data(flujo, nivel, turbidez, color);
  
  delay(1500);
}
