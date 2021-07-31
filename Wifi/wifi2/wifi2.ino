#include "sensors.h"
#include "wifi.h"

void setup() {
  Serial.begin(9600);
  delay(100);

//Wifi set up
  WiFi_set_up();
  Serial.println(" WiFi connected");

  //definir entradas de sensores
   sensors_set_up();
}

void loop() {

  float flujo=Flujo();
  float nivel=Distance(D1, D2);
  float turbidez=Turbidez();
  float color=Color();

  //WiFi_send_data(flujo, nivel, turbidez, color);
  Serial.println(turbidez);
  
  Serial.println("Waiting...");
  delay(15000);
}
