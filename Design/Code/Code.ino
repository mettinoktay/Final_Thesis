/*
 *  On my tests, stepper motor could be pulsed once in every 0.6 milliseconds,
 *  resulting 8.33 rev/sec. Calculation:
 *    1000 ms/second / 0.6 ms/pulse / 200 pulse/revolution = 8.33 revolution / second
 *
 *  PIN MAP:
 *    Stepper Motor STEP -> D6
 *    Stepper Motor DIR  -> D7
 *    Stepper Motor ENB  -> D8
 *    Stepper Motor FLT  -> D4
 *    Stepper Motor M2   -> D9
 *    Stepper Motor M1   -> D10
 *    Stepper Motor M0   -> D11
 *
 *    Wind Vane A -> D3
 *    Wind Vane B -> D12
 *    Generator A -> D2
 *    Generator B -> D13
 *
 *    Servo -> D5
 *    Pitot -> A0
 */

#include <Arduino.h>
#include <Servo.h>
#include <PID_v1.h>
#include <PID_Autotune_v0.h>

/*  DEFINITIONS  */

#define CCW      0
#define CW       1
#define ENB      8
#define M2       9
#define M1       10
#define M0       11
#define FLT      4
#define STEP     6
#define DIR      7
#define FULL     0
#define HALF     8
#define QUARTER  4
#define ONE8TH   12
#define ONE16TH  2
#define ONE32ND  14

#define SERVO    5

#define ENC_A    3
#define ENC_B    12
#define GEN_A    2
#define GEN_B    13
#define PITOT    0

#define LED      13

#define ANLCONV  0.00488758553
#define AIRDENS  1.225

Servo pitchServo;
double encoderPulse = 0, windDirection = 0;
double yawSetPoint = 0, yawInput, yawOutput,
       yawKp = 2.0,
       yawKi = 5.0,
       yawKd = 1.0;

PID PID_yawAxis(&yawInput, &yawOutput, &yawSetPoint,
                 yawKp,     yawKi,      yawKd,
                 AUTOMATIC);

void setup() {
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
  pitchServo.attach(SERVO);
  PID_yawAxis.SetMode(AUTOMATIC);
  //disableStepper();
  //enableStepper();
  microStepping(FULL);
}

void loop() {
  if(thereIsAFaultinDRV8825()){
    disableStepper();
  }
  //computeAoA(readWindSpeed());
  //computeYawAngle(windDirection);
}

double computeAoA(double ws) {
  // int AoA;
  // do some math here using ws to calculate AoA
  // pitchServo.write(AoA);
  // return AoA;
}

double computeYawAngle(double wd) {

}

double readWindSpeed() {
  double outputVoltage = 0.0, diff_pressure = 0.0;
  outputVoltage = (analogRead(PITOT)-528)*ANLCONV;
//  Serial.println(analogRead(0));
//  Serial.print("Output voltage: ");
//  Serial.println(outputVoltage);
  diff_pressure = outputVoltage*1000;
//  Serial.print("Differential pressure: ");
//  Serial.println(diff_pressure);
  return sqrt(2*((diff_pressure)/AIRDENS));
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
