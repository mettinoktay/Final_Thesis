#include "DRV8825.h"

DRV8825::DRV8825() {

}

void DRV8825::Drive(int pulse) {
	if (pulse > 0){
		DRV8825::changeDirection(CW);
	}
	else {
		DRV8825::changeDirection(CCW);
		pulse = -1*pulse;
	}

	for(int step = 0; step <= pulse; step++){
	   digitalWrite(STEP, HIGH);
	   delay(1);
	   digitalWrite(STEP, LOW);
	   delay(20);
	}
}

void DRV8825::changeDirection(int DIRECTION) {
	digitalWrite(DIR, DIRECTION);
}

bool DRV8825::isFaulty() {
  return !digitalRead(FLT);
}

void DRV8825::microStepping(int stepping) {
  /*
   Input must be one of these:
     FULL, HALF, QUARTER, ONE8TH, ONE16TH or ONE32ND
   */
   PORTB = stepping;
}

void DRV8825::Disable() {
  digitalWrite(ENB, HIGH);
}

void DRV8825::Enable() {
  digitalWrite(ENB, LOW);
}
