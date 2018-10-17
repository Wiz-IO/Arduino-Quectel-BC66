/*
 * interface.h
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <_ansi.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#ifdef API_EX
#include <api_stdlib.h>
#include <api_os.h>
#include <api_ril.h>
#include <api_hal.h>
#include <api_tel.h>
#include <api_json.h>
#include <api_ssl.h>
#include <api_socket.h>
#include <api_net.h>
#include <api_mqtt.h>
#endif


#include "debug.h"

#include "custom_feature_def.h"
#include "ql_type.h"
#include "ql_system.h"
#include "ql_memory.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "ql_error.h"
#include "ql_common.h"
#include "ql_uart.h"
#include "ql_gpio.h"
#include "ql_adc.h"
#include "ql_pwm.h"
#include "ql_spi.h"
#include "ql_iic.h"
#include "ril.h"
#include "ril_network.h"
#include "ril_socket.h"

extern void __libc_init_array(void);
extern void __libc_fini_array(void);

void *memset(void *dst, int c, size_t n);


typedef enum {
	MSG_UART_OPEN = 0x1010,
	MSG_EINT_OPEN = 0x1011,
	MSG_ADC_OPEN  = 0x1012,
	MSG_TIMER_OPEN = 0x1013,
} message_e;

typedef struct {
	uint32_t event;
	uint32_t count;
	uint32_t interval;
	uint32_t sampling;
	uint32_t value;
	int error;
} adc_context_t;

typedef enum /*Enum_URCType*/ {
    URC_STATE_SYS_BEGIN = 0,
    URC_STATE_SYS_INIT,
    URC_STATE_SIM_CARD,
    URC_STATE_NW_GSM,
    URC_STATE_NW_GPRS,
    URC_STATE_NW_EGPRS,
    URC_STATE_CFUN,
    URC_STATE_COMING_CALL,
    URC_STATE_CALL,
    URC_STATE_NEW_SMS,
    URC_STATE_MODULE_VOLTAGE,
	URC_STATE_ALARM_RING,
	RIL_READY,
	URC_STATE_MAX,
}urc_states_e;

typedef struct{
	uint32_t state[URC_STATE_MAX];
	char serial[20];
	char imei[20];
	char imsi[20];
	char version[20];
	char apn_name[64];
	char apn_user[64];
	char apn_pass[64];
} device_t;

extern device_t dev;

bool isRilReady(void);

#ifndef API_EX

#define	atoi 			Ql_atoi
#define atof 			Ql_atof
#define memcmp  		Ql_memcmp
#define memmove 		Ql_memmove
#define strcpy 			Ql_strcpy
#define strncpy 		Ql_strncpy
#define strcat			Ql_strcat
#define strncat 		Ql_strncat
#define strcmp			Ql_strcmp
#define strncmp			Ql_strncmp
#define strchr			Ql_strchr
#define strlen			Ql_strlen
#define strstr   		Ql_strstr
#define toupper  		Ql_toupper
#define tolower  		Ql_tolower
#define sprintf  		Ql_sprintf
#define snprintf  		Ql_snprintf
#define sscanf  		Ql_sscanf

#define strtok			Ql_strtok
#define strsep 			Ql_strsep
#else

#endif

#ifdef __cplusplus
}
#endif
#endif /* INTERFACE_H_ */
