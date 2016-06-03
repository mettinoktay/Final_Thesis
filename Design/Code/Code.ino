/*
 *  On my tests, stepper motor could be pulsed once in every 0.6 milliseconds,
 *  resulting 8.33 rev/sec. Calculation:
 *    1000 ms/second / 0.6 ms/pulse / 200 pulse/revolution = 8.33 revolution / second
 *
 */

#include "pins.h"
#include "configuration.h"
#include "Servo.h"
#include "PID_v1.h"

Servo pitchServo;
double windDirectionError = 0.0,
       windSpeed = 0.0;
double yawSetPoint = 0.0, yawInput, yawOutput,
       yawKp = 2.0,
       yawKi = 0.0,
       yawKd = 1.0;

PID PID_yawAxis(&yawInput, &yawOutput, &yawSetPoint,
                 yawKp,     yawKi,      yawKd,
                 AUTOMATIC);

void setup() {
  #ifdef BAUD
    Serial.begin(BAUD);
    Serial.flush();
  #endif
  
  pinMode (M2,    OUTPUT);
  pinMode (M1,    OUTPUT);
  pinMode (M0,    OUTPUT);
  pinMode (FLT,   INPUT);
  pinMode (STEP,  OUTPUT);
  pinMode (DIR,   OUTPUT);
  pinMode (SERVO, OUTPUT);
  pinMode (GEN_B, INPUT);
  pitchServo.attach(SERVO);
  enableStepper();
  microStepping(FULL);
}

void loop() {
  while(thereIsAFaultinDRV8825()){
    disableStepper();
  }
  readWindSpeed(windSpeed);
  computeAoA(windSpeed);
  computeDiretionError(windDirectionError);
  PID_yawAxis.Compute();
  Serial.println(yawOutput);
}

void driveStepper(int pulse, int dir ,int rps) {
  changeDirection(dir);
  for(int i = 0; i <= pulse; i++){
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP, LOW);
    delay(rps);
  }
}

void disableStepper() {
  digitalWrite(ENB, HIGH);
}

void enableStepper() {
  digitalWrite(ENB, LOW);
}

void microStepping(int stepping) {
  /*
   Input must be one of these:
     FULL, HALF, QUARTER, ONE8TH, ONE16TH or ONE32ND
   */
   PORTB = stepping;
}

void changeDirection(int DIRECTION) {
  /*
   Input must be one of these:
     CCW, CW
   */
  digitalWrite(DIR, DIRECTION);
}

bool thereIsAFaultinDRV8825() {
  return !digitalRead(FLT);
}

void readWindSpeed(double &windSpeed) {
  double outputVoltage = 0.0, diff_pressure = 0.0;
  outputVoltage = (analogRead(PITOT)-528)*PITCONV;

  diff_pressure = outputVoltage*1000;

  windSpeed = sqrt(2*((diff_pressure)/AIRDENS));
}

double computeAoA(double &windSpeed) {
  // int AoA;
  // do some math here using ws to calculate AoA
  // pitchServo.write(AoA);
  // return AoA;
}


void computeDiretionError(double &error) {
  error = (analogRead(VANE) - 511.5)*VANCONV;
}


