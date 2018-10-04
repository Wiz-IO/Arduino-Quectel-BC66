/*
 * variants.cpp
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */

#include <interface.h>
#include <HardwareSerial.h>
#include "variant.h"

/*GPIO Quectel		Mediatek
 [PIN] 	0, 			 9
 [PIN]  1, 			10
 [PIN]  2, 			11
 [PIN]  3, 			 8
 [PIN]  4, 			 1
 [PIN]  5, 			 6
 [PIN]  6, 			 7
 [PIN]  7, 			14
 [PIN]  8, 			15
 [PIN]  9, 			28
 [PIN]  10, 		12
 [PIN]  11, 		13
 [PIN]  12, 		27
 [PIN]  13, 		26
 [PIN]  14, 		24
 [PIN]  15, 		25
 [PIN]  16, 		18
 [PIN]  17, 		22
 */

PinDescription pinsMap[] = {
		{ 0, PINNAME_NETLIGHT, M_FREE, F_GPIO | F_PWM },
		{ 1, PINNAME_SPI_MISO, M_FREE, F_GPIO | F_SPI },
		{ 2, PINNAME_SPI_MOSI, M_FREE, F_GPIO | F_SPI },
		{ 3, PINNAME_SPI_SCLK, M_FREE, F_GPIO | F_SPI },
		{ 4, PINNAME_SPI_CS,   M_FREE, F_GPIO | F_SPI },
		{ 0, PIN_ADC0, M_ADC, F_ADC },
		// add other pins
};

#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))
PinDescription * getPin(uint32_t pin) {
	for (uint32_t i = 0; i < ARRAYLEN(pinsMap); i++)
		if (pinsMap[i].arduino == pin)
			return &pinsMap[i];
	return NULL;
}

PinDescription * getAdc(uint32_t pin) {
	uint32_t i = 0;
	while (i < ARRAYLEN(pinsMap))
		if (pinsMap[i].arduino == pin && pinsMap[i].function == F_ADC)
			return &pinsMap[i];
	return NULL;
}

HardwareSerial Serial(0);
HardwareSerial Serial1(1);
HardwareSerial Serial2(2);
