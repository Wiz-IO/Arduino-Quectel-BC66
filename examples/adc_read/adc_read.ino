/*
 *  ADC Example
 *  Created on: 03.10.2018
 *  Author: Georgi Angelov
 *  module has one ADC, Quectel name PIN_ADC0, pin 9
 *
 */

#include "Arduino.h"

void setup() {
	Serial.begin(115200);
	Serial.println("ADC Read Example");
	pinMode(LED_BUILTIN, OUTPUT); // Quectel PINNAME_NETLIGHT

	// 0 for ADC
	// 5 (min) samples count
	// 200 mSec (min) samples interval
	analogOpen(0, 5, 200);
	//The average value of ADC sampling. The range is 0mV ~2800mV.
}

void loop() {
	static uint32_t state = 0;
	switch (state) {
	case 0:
		Serial.print("ADC Value: ");
		Serial.print(analogRead(0));
		Serial.println(" mV");
		break;
	default:
		// blink led
		digitalWrite(LED_BUILTIN, state ^ 1);
		break;
	}
	delay(100);
	if (++state > 29)
		state = 0;
}
