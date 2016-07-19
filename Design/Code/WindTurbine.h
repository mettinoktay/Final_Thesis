#ifndef WINDTURBINE_H
#define WINDTURBINE_H

#include "Arduino.h"
#include "pins.h"
#include "configuration.h"

class WindTurbine {
	public:
		WindTurbine();
		void computeDirectionError(double* error);
		double computeAoA(double* windSpeed);
		double readWindSpeed(double* windSpeed);
	private:
		double* _error;
		double* _windSpeed;
};

#endif
