/*
 * YILDIZ TEKN�K �N�VERS�TES�
 * MEKATRON�K M�HEND�SL���
 *
 * L�SANS B�T�RME TEZ� ���N YAZILMI�
 * UYGULAMAYA �ZEL B�R K�T�PHANE
 *
 * Yazar: Metin Oktay Y�lmaz
 * Tarih: 06.06.2016
 *
 */

#ifndef DRV8825_H_
#define DRV8825_H_

#include "Arduino.h"
#include "pins.h"
#include "configuration.h"

class DRV8825{
	public:
		DRV8825();
		void Drive(int pulse);
		void changeDirection(int DIRECTION);
		void microStepping(int stepping);
		void Enable();
		void Disable();
		bool isFaulty();
	private:
};

#endif
