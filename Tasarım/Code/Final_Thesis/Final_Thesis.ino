/*
 *   PIN MAP:
 *   Stepper Motor STEP -> D6
 *   Stepper Motor DIR  -> D7
 *   Stepper Motor ENB  -> D8
 *   Stepper Motor FLT  -> D4
 *   Stepper Motor M2   -> D9
 *   Stepper Motor M1   -> D10
 *   Stepper Motor M0   -> D11
 *  
 *   Wind Vane A -> D3 
 *   Wind Vane B -> D12
 *   Generator A -> D2
 *   Generator B -> D13
 *   
 *   Servo -> D5
 *   Pitot -> A0
 *  
*/

#define CCW      0
#define CW       1
#define ENB      8
#define M2       9
#define M1       10
#define M0       11
#define FLT      4
#define STEP     6
#define DIR      7
#define SERVO    5
#define FULL     0
#define HALF     8
#define QUARTER  4
#define ONE8TH   12
#define ONE16TH  2
#define ONE32ND  14
#define ENC_A    2
#define GEN_A    3
#define ENC_B    12
#define GEN_B    13
#define LED      13

#include "Servo.h"

Servo pitchServo;
int encoderPulse = 0, windDirection = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
//attachInterrupt(digitalPinToInterrupt(GEN_A), wind, RISING);
//attachInterrupt(digitalPinToInterrupt(GEN_A), ISR, RISING);
  pitchServo.attach(SERVO);  
//disableStepper();
  enableStepper();
  microStepping(FULL);
}

void loop() {
    analogWrite(STEP, 5);
    changeDirection(CCW);
    Serial.println("CCW");
    delay(5000);
    changeDirection(CW);
    Serial.println("CW");
    delay(5000);
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

void wind()
{
  encoderPulse += digitalRead(GEN_B);
}
