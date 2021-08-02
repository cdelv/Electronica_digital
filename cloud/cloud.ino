#include "thingProperties.h"
#include <NewPing.h>
#include <SPI.h>
#include <Wire.h>

int NumPulsos=0;

void Sensors_set_up(void);

void ICACHE_RAM_ATTR ContarPulsos()
{ 
  NumPulsos++;  //incrementamos la variable de pulsos
}

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  Sensors_set_up();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  
  
}

void onAguaChange() {
  NewPing sonar(D0, D1, 150);
  Serial.print("Agua=");
  Serial.println(sonar.ping_cm());
  //return sonar.ping_cm();
}

void onFlujoChange() {
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  delay(1000);    //muestra de 1 segundo
  Serial.print("Flujo=");
  Serial.println(NumPulsos);
}

void onTurbidezChange() {
  // Do something
  int n=1000;
  float sensor=0, value;
  for (int i=0; i < n; i++)
  {
    sensor += analogRead(A0); // read the input on analog pin 0 (turbidity sensor analog output)
    delay(10);
  }
  sensor/=n;

  Serial.print("Turbidez=");
  Serial.println((sensor/625)*100);
  //return (sensor/625)*100;
}

void onSuciedadChange() {
  // Do something
  int greenFrequency = 0;
  int greenColor = 0;
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(D7, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // greenColor = map(greenFrequency, 100, 199, 255, 0);

  float G_MIN = 30;
  float G_MAX = 250;
  greenColor = map(greenFrequency, G_MIN, G_MAX, 100, 0);
  Serial.print("Suciedad=");
  Serial.println(greenColor);
 // return greenColor ;
}


void onHayAguaChange() {
  // Do something
}
void Sensors_set_up(void)
{
  //Pines del sensor de ultra sonido
  pinMode(D0,OUTPUT);
  pinMode(D1, INPUT);

   //Pin del sensor de turbidez
   pinMode(A0, INPUT);

   //Pines del sensor de color
   pinMode(D3, OUTPUT);
   pinMode(D4, OUTPUT);
   pinMode(D5, OUTPUT);
   pinMode(D6, OUTPUT);
   pinMode(D7, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(D3,HIGH);
  digitalWrite(D4,LOW);

  //Pin del sensor de flujo
  pinMode(D2, INPUT);
  attachInterrupt(digitalPinToInterrupt(D2), ContarPulsos, RISING); //habilitar las interrupciones
}
