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
 *  
 */

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
#define SERVO    5
#define FULL     0
#define HALF     8
#define QUARTER  4
#define ONE8TH   12
#define ONE16TH  2
#define ONE32ND  14
#define ENC_A    3
#define ENC_B    12
#define GEN_A    2
#define GEN_B    13
#define LED      13
#define PITOT    0

#include "Servo.h"

Servo pitchServo;
int DELAY = 10, time = 0;
int encoderPulse = 0, windDirection = 0;

void setup() {
  setupSystem();
}

void loop() {
  if(thereIsAFaultinDRV8825()){
    disableStepper();
  }
}
