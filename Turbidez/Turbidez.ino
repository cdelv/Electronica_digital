#include <EEPROM.h> // to store last calibration value (blanco, Vclear)

int sensor = 0; // variable for averaging
int n = 25; // number of samples to average
int sensorValue = 0;
float voltage = 0.00;
float turbidity = 0.00;
float Vclear = 2.85; // Output voltage to calibrate (with clear water).

int buttoncalib = 2; // The pin location of the push sensor for calibration. Connected to Ground and
// pin D2.

int pushcalib = 1; // variable for pin D2 status.

void setup()
{
Serial.begin(9600);
pinMode(buttoncalib, INPUT_PULLUP); //initializes digital pin 2 as an input with pull-up resistance.

//Serial display
Serial.println("Hi… welcome to your turbidity sensor");

EEPROM.get(0, Vclear); // recovers the last Vclear calibration value stored in ROM.
delay(3000); // Pause for 3 seg
}

void loop()
{
pushcalib = digitalRead(2); // push button status

if (pushcalib == HIGH) {
// If the push button is not pushed, do the normal sensing routine:
for (int i=0; i < n; i++){
sensor += analogRead(A0); // read the input on analog pin 1 (turbidity sensor analog output)
delay(10);
}
sensorValue = sensor / n; // average the n values
voltage = sensorValue * (5.000 / 1023.000); // Convert analog (0-1023) to voltage (0 - 5V)

turbidity = 100.00 - (voltage / Vclear) * 100.00; // as relative percentage; 0% = clear water;

EEPROM.put(0, Vclear); // guarda el voltaje de calibración actualmente en uso.

// Serial display
Serial.print(sensorValue);
Serial.print(", ");
Serial.print(voltage,3);
Serial.print(", ");
Serial.print(turbidity,3);
Serial.print(", ");
Serial.println(Vclear,3);

sensor = 0; // resets for averaging

} else {

// Calibration routine, when push button is pushed:

Serial.println("Put the sensor in clear water to calibrate…");

delay(2000);

for (int i=0; i < n; i++){
sensor += analogRead(A0); // read the input on analog pin 1:
delay(10);
}
sensorValue = sensor / n;
Vclear = sensorValue * (5.000 / 1023.000); // Converts analog (0-1023) to voltage (0-5V):
sensor = 0;
EEPROM.put(0, Vclear); // stores Vclear in ROM
delay(1000);

}
delay(1000); // Pause for 1 seconds. // sampling rate
}
