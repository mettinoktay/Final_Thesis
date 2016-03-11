void setupSystem(){
 // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.flush();
  pinMode(M2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(FLT, INPUT);
  pinMode(ENB, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(SERVO, OUTPUT);
  pinMode(GEN_B, INPUT);
  pinMode(ENC_B, INPUT);
//attachInterrupt(digitalPinToInterrupt(ENC_A), wind, RISING);
//attachInterrupt(digitalPinToInterrupt(GEN_A), ISR, RISING);
  pitchServo.attach(SERVO);  
  disableStepper();
  //enableStepper();
  microStepping(FULL);
}
