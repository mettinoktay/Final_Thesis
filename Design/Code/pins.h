#ifndef PINS_H
#define PINS_H

#pragma once

/*  PIN MAP:
 *    Stepper Motor STEP -> D6
 *    Stepper Motor DIR  -> D7
 *    Stepper Motor ENB  -> D8
 *    Stepper Motor FLT  -> D4
 *    Stepper Motor M2   -> D9
 *    Stepper Motor M1   -> D10
 *    Stepper Motor M0   -> D11
 *
 *    Wind Vane   -> A0
 *    Generator A -> D2
 *    Generator B -> D13
 *
 *    Servo -> D5
 *    Pitot -> A0
 */

#define M2     9
#define M1     10
#define M0     11
#define FLT    4
#define STEP   6
#define DIR    7
#define ENB    8

#define SERVO  5

#define VANE   1

#define GEN_A  2
#define GEN_B  13
#define PITOT  0

#define LED    13

#endif
