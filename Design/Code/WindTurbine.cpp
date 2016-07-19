#include "WindTurbine.h"

WindTurbine::WindTurbine(){
	
}

void WindTurbine::computeDirectionError(double* error){
	_error = error;
	*_error= (analogRead(VANE) - 511.5)*VANCONV;
}

double WindTurbine::computeAoA(double* windSpeed){
	return 0.0f;
}

double WindTurbine::readWindSpeed(double* windSpeed){
	return 0.0f;
}
