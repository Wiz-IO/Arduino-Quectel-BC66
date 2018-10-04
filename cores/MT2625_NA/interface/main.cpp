/*
 main.cpp - Main loop for Arduino sketches
 Copyright (c) 2005-2013 Arduino Team.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Created on: 08.08.2018
 Author: Georgi Angelov

 */

/* Compile Version 1.0.2 */

#include "Arduino.h"
#include "interface.h"

device_t dev = { 0 };

//UART must be open in main task,
//callback is being processed in Ql_OS_GetMessage()
void uart_callback(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void * user) {
	if (!user)
		return;
	uint8_t c;
	HardwareSerial * p = (HardwareSerial *) (user);
	switch (msg) {
	case EVENT_UART_READY_TO_READ:
		while (Ql_UART_Read(port, &c, 1) == 1)
			if (p->save(c))
				return;
		break;
	default:
		break;
	}
}

//ADC must be open in main task,
//callback is being processed in Ql_OS_GetMessage()
static void adc_callback(Enum_ADCPin adcPin, u32 adcValue, void *user) {
	if (!user)
		return;
	adc_context_t * adc = (adc_context_t *) user;
	adc->value = adcValue;
}

static s32 atHandler(char* line, u32 len, void* userdata) {
	if (!userdata)
		return RIL_ATRSP_FAILED;
	char * p = (char*) userdata;
	if (p == dev.version) {
		if (strstr(line, "Revision:")) {
			strcpy(p, &line[10]);
			replaceChar(p, 13, 0);
			replaceChar(p, 10, 0);
		}
	} else if (p == dev.imei) {
		if ( strlen(line) > 17)
			memcpy(userdata, &line[2], 15);
	}
	if (strstr(line, "OK"))
		return RIL_ATRSP_SUCCESS;
	if (strstr(line, "ERROR"))
		return RIL_ATRSP_FAILED;
	return RIL_ATRSP_CONTINUE; //continue wait
}

static void getVersion(void) {
	Ql_RIL_SendATCmd((char*) "ATI\n", 4, atHandler, &dev.version, 0);
}

static void getImei(void) {
	Ql_RIL_SendATCmd((char*) "ATI\n", 4, atHandler, &dev.imei, 0);
}

/* module is ready for AT commands */
bool isRilReady(void) {
	return dev.state[RIL_READY] == 1;
}

extern "C" void proc_main_task(int taskId) {
	__libc_init_array(); // cpp init

#if DEBUG_ENABLE>0
	debug_init();
	LOG("[DEV] Arduino Quectel BC66 NB IoT MT2625\n");
#endif

	memset(&dev, 0, sizeof(device_t));
	for (int i = 0; i < URC_STATE_MAX; i++)
		dev.state[i] = -1;

	ST_MSG msg;
	while (1) {
		Ql_OS_GetMessage(&msg);
		switch (msg.message) {
		case MSG_ID_RIL_READY:
			Ql_RIL_Initialize();
			getVersion();
			getImei();
			dev.state[RIL_READY] = 1;
			LOG("[DEV] MSG_ID_RIL_READY\n")
			;
			break; // MSG_ID_RIL_READY

		case MSG_ID_URC_INDICATION:
			if (msg.param1 < URC_STATE_MAX)
				dev.state[msg.param1] = msg.param2;
			if (URC_SIM_CARD_STATE_IND == msg.param1 && SIM_STAT_READY == msg.param2) {
				// onSimReady();
			}
			break; // MSG_ID_URC_INDICATION

		case MSG_UART_OPEN: /* system call */{
			if (!msg.param1)
				break;
			HardwareSerial * uart = (HardwareSerial *) (msg.param1);
			if (!uart->event) {
				uart->error = -1000;
				break;
			}
			uart->error = Ql_UART_Register(uart->port, uart_callback, uart);
			if (!uart->error)
				uart->error = Ql_UART_Open(uart->port, uart->brg, FC_NONE);
			Ql_OS_SetEvent(uart->event, msg.param2);
		}
			break; // MSG_UART_OPEN

		case MSG_ADC_OPEN: /* system call */{
			if (!msg.param1)
				break;
			adc_context_t * adc = (adc_context_t *) msg.param1;
			if (!adc->event) {
				adc->error = -1000;
				break;
			}
			adc->error = Ql_ADC_Register(PIN_ADC0, adc_callback, adc);
			if (!adc->error) {
				adc->error = Ql_ADC_Init(PIN_ADC0, adc->count, adc->interval);
				if (!adc->error)
					adc->error = Ql_ADC_Sampling(PIN_ADC0, adc->sampling > 0);
			}
			Ql_OS_SetEvent(adc->event, msg.param2);
		}
			break; // MSG_ADC_OPEN

		} // switch
	}
}

extern void init(void) __attribute__((weak));
extern void setup(void) __attribute__((weak));
extern void loop(void) __attribute__((weak));

extern "C" void proc_arduino(int taskId) {
	unsigned int event = Ql_OS_CreateEvent();
	init();
	setup();
	while (1) {
		loop();
		if (event)
			Ql_OS_WaitEvent(event, 1, 10); // whitout delay APP will crash
	}
}

//OpenCPU have not system time API, this is fake time...
extern "C" void proc_delay(int taskId) {
	unsigned int event = Ql_OS_CreateEvent();
	while (1) {
		if (event) {
			Ql_OS_WaitEvent(event, 1, 10); // whitout delay APP will crash
			__millis += 10;
		}
	}

}
