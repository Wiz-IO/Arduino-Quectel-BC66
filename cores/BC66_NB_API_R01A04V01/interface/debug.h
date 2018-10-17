/*
 * debug.h
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */

#ifndef DEBUG_H_
#define DEBUG_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "ql_uart.h"
#include "ql_stdlib.h"

void debug(char * fmt, ...);
void debug_init(void);

#define DEBUG_ENABLE 1
#if DEBUG_ENABLE > 0
#define DEBUG_PORT  UART_PORT0
#define DBG_BUF_LEN   512
extern char DBG_BUFFER[DBG_BUF_LEN];
#define LOG(FORMAT,...) {\
    Ql_memset(DBG_BUFFER, 0, DBG_BUF_LEN);\
    Ql_sprintf(DBG_BUFFER,FORMAT,##__VA_ARGS__); \
    if (UART_PORT2 == (DEBUG_PORT)) \
    {\
        Ql_Debug_Trace(DBG_BUFFER);\
    } else {\
        Ql_UART_Write((Enum_SerialPort)(DEBUG_PORT), (u8*)(DBG_BUFFER), Ql_strlen((const char *)(DBG_BUFFER)));\
    }\
}

#else
#define LOG(FORMAT,...)
#endif

#ifdef __cplusplus
}
#endif
#endif /* DEBUG_H_ */
