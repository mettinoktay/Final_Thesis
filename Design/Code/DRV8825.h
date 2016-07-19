/*
 * YILDIZ TEKNÝK ÜNÝVERSÝTESÝ
 * MEKATRONÝK MÜHENDÝSLÝÐÝ
 *
 * LÝSANS BÝTÝRME TEZÝ ÝÇÝN YAZILMIÞ
 * UYGULAMAYA ÖZEL BÝR KÜTÜPHANE
 *
 * Yazar: Metin Oktay Yýlmaz
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
