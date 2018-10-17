/*
 * debug.c
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */
#include "interface.h"

char DBG_BUFFER[DBG_BUF_LEN];

extern void uart_callback(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void * user);

void debug_init(void) {
	s32 ret;
	ret = Ql_UART_Register(UART_PORT0, uart_callback, NULL);
	if (ret < QL_RET_OK) return;
	ret = Ql_UART_Open(UART_PORT0, 115200, FC_NONE);
	if (ret < QL_RET_OK) return;
	LOG("[DBG] READY\n");
}
