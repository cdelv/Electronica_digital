
// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int greenFrequency = 0;

// Stores the green color
int greenColor = 0;

float Color_pureza();

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  
  // Printing the GREEN (G) value  
  Serial.print(" Porcentaje de pureza = ");
  Serial.print(Color_pureza());
  Serial.println("%");
  delay(1000);
 
 
}

float Color_pureza()
{
// Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // greenColor = map(greenFrequency, 100, 199, 255, 0);

  float G_MIN = 240;
  float G_MAX = 2150;
  greenColor = map(greenFrequency, G_MIN, G_MAX, 100, 0);
  return greenColor ;
}
