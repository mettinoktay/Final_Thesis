void driveStepper(int pulse, int rps)
{
  for(int i = 0; i <= pulse; i++){
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP, LOW);
    delay(rps);
  }
}

void disableStepper()
{
  digitalWrite(ENB, HIGH);
}

void enableStepper()
{
  digitalWrite(ENB, LOW);
}

void microStepping(int stepping)
{
  /*
   Input must be one of these:
     FULL     
     HALF   
     QUARTER
     ONE8TH 
     ONE16TH
     ONE32ND
   */
   PORTB = stepping;
}

void changeDirection(int DIRECTION)
{
  /*
   Input must be one of these:
     CCW
     CW
   */
  digitalWrite(DIR, DIRECTION);
}

int thereIsAFaultinDRV8825()
{
  return !digitalRead(FLT);
}
