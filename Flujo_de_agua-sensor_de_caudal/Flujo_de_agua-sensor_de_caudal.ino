
int calc;
volatile int rpmcount;


void rpm();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rpmcount=0;
  attachInterrupt(A2, rmp, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  rpmcount=0;
  sei();
  delay(1000);
  cli();
  calc=(rpmcount*60/350); 
  Serial.print(calc, DEC);
  Serial.print("Litros/min\r\n"); //imprime litros por minuto

  attachInterrupt(A2, rmp, RISING);
  
}

void rpm(){
  rpmcount++;
}
