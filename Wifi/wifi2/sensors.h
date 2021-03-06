#include <NewPing.h>
#include <SPI.h>
#include <Wire.h>


int NumPulsos=0;
void ICACHE_RAM_ATTR ContarPulsos()
{ 
  NumPulsos++;  //incrementamos la variable de pulsos
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

float Flujo(void)
{
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  delay(1000);    //muestra de 1 segundo
  float value = NumPulsos;
  return (value/45)*100;
}

float Distance(int triggerPin, int echoPin)
{
  NewPing sonar(triggerPin, echoPin, 150);
  float value = map(sonar.ping_cm(), 3, 44, 100, 0);
  return value;
}

float Turbidez(void)
{
  int n=2500;
  float sensor=0, value;
  for (int i=0; i < n; i++)
  {
    sensor += analogRead(A0); // read the input on analog pin 0 (turbidity sensor analog output)
    delay(10);
  }
  sensor/=n;

  return (sensor/790)*100;
  //return sensor;
}

float Color(void)
{
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

  float G_MIN = 25;
  float G_MAX = 400;
  greenColor = map(greenFrequency, G_MIN, G_MAX, 100, 0);
  return greenColor ;
  //return greenFrequency;
}
