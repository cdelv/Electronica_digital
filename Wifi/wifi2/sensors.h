#include <NewPing.h>
#include <SPI.h>
#include <Wire.h>

volatile int NumPulsos;

void ICACHE_RAM_ATTR ContarPulsos()
{ 
  NumPulsos++;  //incrementamos la variable de pulsos
}

void sensors_set_up(void)
{
  //Pines del sensor de ultra sonido
  pinMode(D1,OUTPUT);
  pinMode(D2, INPUT);

  //Pin del sensor de flujo
   pinMode(D4, INPUT);
   attachInterrupt(digitalPinToInterrupt(D4),ContarPulsos,RISING); //habilitar las interrupciones

   //Pin del sensor de turbidez
   pinMode(A0, INPUT);
}
float Flujo(void)
{
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Desabilitamos las interrupciones
  return NumPulsos;
}
float Distance(int triggerPin, int echoPin)
{
  NewPing sonar(triggerPin, echoPin, 150);
  return sonar.ping_cm();
}
float Turbidez(void)
{
  int n=2000;
  float sensor=0, value;
  for (int i=0; i < n; i++)
  {
    sensor += analogRead(A0); // read the input on analog pin 0 (turbidity sensor analog output)
    delay(10);
  }
  sensor/=n;

  return (sensor/200)*100;
  
}
float Color(void)
{
  return 2.5;
}
