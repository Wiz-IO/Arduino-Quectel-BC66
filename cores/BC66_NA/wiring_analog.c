/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "wiring_analog.h"
#include <interface.h>

// The gpio for PWM is PINNAME_NETLIGHT.
static adc_context_t adc = { 0 };

#define PWM_MAX 	8193
static Enum_PwmSource PWM_SrcClk = PWMSOURCE_32K;
static Enum_PwmSourceDiv PWM_Div = PWMSOURCE_DIV8;
static uint32_t PWM_lowPulseNum = PWM_MAX / 2;
static uint32_t PWM_highPulseNum = PWM_MAX / 2;

void analogClose(uint32_t pin) {
	if (pin) {
		Ql_PWM_Uninit(PINNAME_NETLIGHT);
	} else
		Ql_ADC_Sampling(PIN_ADC0, false);
}

static void pwmCalculate(uint32_t ulValue) {
	PWM_lowPulseNum = PWM_MAX / 2;
	PWM_highPulseNum = PWM_MAX / 2;
}

// 0 for ADC, 1 for PWM
// 5 (min) adc samples count
// 200 mSec (min) adc samples interval
void analogOpen(uint32_t pin, ...) {
	uint32_t pwmSrcClk, pwmDiv, ulValue;
	va_list vl;
	va_start(vl, pin);
	if (pin) {
		pwmSrcClk = va_arg(vl, uint32_t);
		pwmDiv = va_arg(vl, uint32_t);
		ulValue = va_arg(vl, uint32_t);
		PWM_SrcClk = (Enum_PwmSource) pwmSrcClk;
		PWM_Div = (Enum_PwmSourceDiv) pwmDiv;
		Ql_GPIO_Uninit(PINNAME_NETLIGHT); // PIN_FREE
		analogWrite(PINNAME_NETLIGHT, ulValue);
	} else {
		adc.value = 0;
		adc.count = va_arg(vl, uint32_t);
		adc.interval = va_arg(vl, uint32_t);
		if (adc.interval < 200)
			adc.interval = 200;
		if (adc.count < 5)
			adc.count = 5;
		if (!adc.event)
			adc.event = Ql_OS_CreateEvent();
		if (!adc.event)
			return;
		adc.sampling = 1;
		Ql_OS_SendMessage(0, MSG_ADC_OPEN, (uint32_t) &adc.event, 1);
		Ql_OS_WaitEvent(adc.event, 1, -1);
	}
	va_end(vl);
}

uint32_t analogRead(uint32_t ulPin) {
	return adc.value;
}

void analogWriteOnOff(uint32_t pin, bool on_off) {
	Ql_PWM_Output(PINNAME_NETLIGHT, on_off);
}

extern void analogWrite(uint32_t pin, uint32_t ulValue) {
	pwmCalculate(ulValue);
	Ql_PWM_Init(PINNAME_NETLIGHT, PWM_SrcClk, PWM_Div, PWM_lowPulseNum, PWM_highPulseNum);
	Ql_PWM_Output(PINNAME_NETLIGHT, ulValue > 0);
}

#ifdef __cplusplus
}
#endif
