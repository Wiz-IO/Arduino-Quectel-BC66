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

#include "opencpu/ql_uart.h"

void debug(char * fmt, ...);

#undef DEBUG
#undef LOG

#define DEBUG 0

#if (DEBUG == 0)
#	define LOG(_STR_, ...)   	Ql_Debug_Trace((char*) _STR_, ##__VA_ARGS__)
#elif (DEBUG == 1)
#	define LOG(_STR_, ...)
#else
#	define LOG(_STR_, ...)
#endif


#ifdef __cplusplus
}
#endif
#endif /* DEBUG_H_ */
