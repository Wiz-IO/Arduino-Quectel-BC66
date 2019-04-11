/*
  BC66 - interface
    Created on: 01.01.2019
    Author: Georgi Angelov

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
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <_ansi.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include "ql_common.h"
#include "ql_type.h"
#include "ql_system.h"
#include "ql_memory.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "ql_error.h"
#include "ql_uart.h"
#include "ql_gpio.h"
#include "ql_adc.h"
#include "ql_pwm.h"
#include "ql_spi.h"
#include "ql_iic.h"
#include "ql_eint.h"
#include "ql_power.h"
#include "ql_rtc.h"
#include "ql_time.h"
#include "ql_timer.h"
//#include "ql_wtd.h"

#include "ril.h"
#include "ril_system.h"
#include "ril_util.h"
#include "ril_lwm2m.h"
#include "ril_network.h"
#include "ril_socket.h"
//#include "ril_onenet.h"

#include "api.h"
#include "dbg.h"

extern int snprintf ( char * s, size_t n, const char * format, ... );
extern int vsnprintf (char * s, size_t n, const char * format, va_list arg );

#define ARDUINO_TASK_ID 3 /* arduino_task_id */
#define MSG_PROCESS_MESSAGES 0x100

    extern void entry_main(int) __attribute__((weak)); // if exist, OpenCPU style else setup/loop
    extern void __libc_init_array(void);
    extern void __libc_fini_array(void);

    unsigned int seconds(void);
    unsigned int millis(void);
    unsigned int micros(void);
    void delay(unsigned int);
    void delayMicroseconds(unsigned int us);
    void arduinoProcessMessages(unsigned int wait);    

    int isascii(int c);
    int toascii(int c);
    long atol(const char *s);
    char *itoa(int value, char *result, int base);
    char *ltoa(long value, char *result, int base);
    char *utoa(unsigned value, char *result, int base);
    char *ultoa(unsigned long value, char *result, int base);

    uint32_t clockCyclesPerMicrosecond(void);
    uint32_t clockCyclesToMicroseconds(uint32_t a);
    uint32_t microsecondsToClockCycles(uint32_t a);
    int isAtEnd(char *line, u32 len);

#ifndef SERIAL_BUFFER_SIZE
#define SERIAL_BUFFER_SIZE 256
#endif

    // for SPI
    __attribute__((always_inline)) static inline uint32_t __RBIT(uint32_t value)
    {
        uint32_t result;
        __asm volatile("rbit %0, %1"
                       : "=r"(result)
                       : "r"(value));
        return (result);
    }

    __attribute__((always_inline)) static inline uint32_t __REV(uint32_t value)
    {
        uint32_t result;
        __asm volatile("rev %0, %1"
                       : "=r"(result)
                       : "r"(value));
        return (result);
    }

    __attribute__((always_inline)) static inline uint32_t __REV16(uint32_t value)
    {
        uint32_t result;
        __asm volatile("rev16 %0, %1"
                       : "=r"(result)
                       : "r"(value));
        return (result);
    }

#ifdef __cplusplus
} // extern "C"

void arduinoSetWait(u32 wait);
void delayEx(unsigned int ms);

#endif //__cplusplus

#endif /* INTERFACE_H_ */
