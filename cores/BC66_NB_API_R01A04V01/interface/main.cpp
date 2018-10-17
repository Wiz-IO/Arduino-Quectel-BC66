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

/* Compile Version 1.0.3 */

#include "Arduino.h"

extern void init(void) __attribute__((weak));
extern void setup(void) __attribute__((weak));
extern void loop(void) __attribute__((weak));
TaskHandle_t arduinoTaskHandle;
portTASK_FUNCTION( arduinoTaskFunc, pvParameters);

device_t dev = { 0 };
void pdp_callback(unsigned int app_id, tel_conn_mgr_info_type_enum info_type, tel_conn_mgr_bool result, tel_conn_mgr_err_cause_enum cause, tel_conn_mgr_pdp_type_enum pdp_type);

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

static s32 ril_atHandler(char* line, u32 len, void* userdata) {
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

static void ril_getVersion(void) {
	Ql_RIL_SendATCmd((char*) "ATI\n", 4, ril_atHandler, &dev.version, 0);
}

static void ril_getImei(void) {
	Ql_RIL_SendATCmd((char*) "AT+GSN\n", 4, ril_atHandler, &dev.imei, 0);
}

static int protectApi(void) {
	if (0 == checkApi())
		return 0;
	int i = 10;
	while (i--)
		delay(1000);
	platform_assert("ERROR: Vrong Api Version", "main.cpp", 1);
	return -1;
}

static void deviceInit(void) {
	memset(&dev, 0, sizeof(device_t));
	for (int i = 0; i < URC_STATE_MAX; i++)
		dev.state[i] = -1;
	dev.event = Ql_OS_CreateEvent();
	dev.pdp.event = Ql_OS_CreateEvent();
	dev.pdp.hdl = tel_conn_mgr_register_callback(pdp_callback);
}

extern "C" void proc_main_task(int taskId) {
	__libc_init_array(); // cpp init
	if (protectApi())
		return;
#if DEBUG_ENABLE > 0
	debug_init();
	LOG("[DEV] Quectel EXTENDED API %s\n", getVersion());
	cpuSpeed(0);
#endif
	deviceInit();
	xTaskGenericCreate(arduinoTaskFunc, "ARDUINO", 10*1024, NULL, TASK_PRIORITY_NORMAL, &arduinoTaskHandle, NULL, NULL);
	ST_MSG msg;
	char CMD_SLEEP[] = "AT+QSCLK=0\n"; // disable default sleep
	while (1) {
		Ql_OS_GetMessage(&msg);
		switch (msg.message) {
		case MSG_ID_RIL_READY:
			Ql_RIL_Initialize();
			Ql_RIL_SendATCmd((char*) CMD_SLEEP, strlen(CMD_SLEEP), NULL, NULL, 1000);
			ril_getVersion();
			ril_getImei();
			Ql_OS_SetEvent(dev.event, DEV_EVENT_RIL); // ril ready
			LOG("[DEV] MSG_ID_RIL_READY\n");
			dev.state[RIL_READY] = 1;
			/* module is ready for AT commands */
			break; // MSG_ID_RIL_READY

		case MSG_ID_URC_INDICATION:
			LOG("[RIL] MSG_ID_URC_INDICATION: %d, %d\n", msg.param1, msg.param2);
			if (msg.param1 < URC_STATE_MAX)
				dev.state[msg.param1] = msg.param2; // colect info
			if (URC_SIM_CARD_STATE_IND == msg.param1 && SIM_STAT_READY == msg.param2) {
				// onSimReady();
			}
			break; // MSG_ID_URC_INDICATION

		case MSG_UART_OPEN: /* system call */ {
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

		case MSG_ADC_OPEN: /* system call */ {
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

portTASK_FUNCTION( arduinoTaskFunc, pvParameters) {
	LOG("[ARDUINO] Begin\n");
	init();
	setup();
	while (1) {
		loop();
		vTaskDelay(4); // whitout this APP will crash, give time..
	}
}

/* Device Functions */

void pdp_callback(unsigned int app_id, tel_conn_mgr_info_type_enum info_type, tel_conn_mgr_bool result, tel_conn_mgr_err_cause_enum cause, tel_conn_mgr_pdp_type_enum pdp_type) {
	LOG("   [BEARER] app_id    = %d\n", app_id);
	LOG("   [BEARER] info_type = %d\n", info_type);
	LOG("   [BEARER] result    = %d\n", result);
	LOG("   [BEARER] cause     = %d\n", cause);
	LOG("   [BEARER] pdp_type  = %d\n", pdp_type);
	if (app_id == dev.pdp.id) {
		dev.pdp.result = result;
		Ql_OS_SetEvent(dev.pdp.event, 1);
	}
}

int pdp_act(const char * apn, const char * user, const char * pass, uint32_t timeout) {
	tel_conn_mgr_pdp_type_enum type;
	tel_conn_mgr_ret_enum rc = tel_conn_mgr_activate_int(
			TEL_CONN_MGR_BEARER_TYPE_NBIOT,
			TEL_CONN_MGR_SIM_ID_1,
			TEL_CONN_MGR_PDP_TYPE_IP,
			(char*) apn,
			(char*) user,
			(char*) pass,
			NULL, dev.pdp.hdl, &dev.pdp.id, &type);
	if (TEL_CONN_MGR_RET_OK == rc)
		return OK; // internet is ready
	if (TEL_CONN_MGR_RET_WOULDBLOCK == rc) {
		Ql_OS_WaitEvent(dev.pdp.event, 1, timeout);
		return 0; // TODO callback return;
	}
	return ERROR;
}

void pdp_deact(void) {
	tel_conn_mgr_deactivate(dev.pdp.id);
	// TODO Wait deacting
 }
