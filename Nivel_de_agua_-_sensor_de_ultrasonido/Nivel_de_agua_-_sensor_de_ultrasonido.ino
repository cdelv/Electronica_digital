
long readUltrasonicDistance(int triggerPin, int echoPin);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  double max_d = 150; //deepness of the water tank in centimeters(cm)
  double min_d = 10; //minimum distance the sensor can detect, in centimeters (cm)
  int distance = 0.01723*readUltrasonicDistance(A1, A0); //convertion of the value of time given by the function in centimeters with the formula for constant speed d = v x t

  if(distance<=min_d)
  {
    distance=min_d;
  }
  if(distance>=max_d){
    distance=max_d;
  }
  
  int percentage = map(distance, min_d, max_d, 100, 0); //gives the value of fullness of the tank with a percentage
  distancia;
  delay(10);
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); //Clears the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  //Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
