/*
 * debug.c
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */
#include "interface.h"

char DBG_BUFFER[DBG_BUF_LEN];

static void CallBack_UART_Hdlr(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void* customizedPara){}

void debug_init(void) {
	s32 ret;
	ret = Ql_UART_Register(UART_PORT0, CallBack_UART_Hdlr, NULL);
	if (ret < QL_RET_OK) {
		Ql_Debug_Trace("[ERR] Fail to register serial port[%d], ret = %d\n", UART_PORT0, ret);
	}
	ret = Ql_UART_Open(UART_PORT0, 115200, FC_NONE);
	if (ret < QL_RET_OK) {
		Ql_Debug_Trace("[ERR] Fail to open serial port[%d], ret = %d\n", UART_PORT0, ret);
	}
	LOG("[DBG] READY\n");
}
