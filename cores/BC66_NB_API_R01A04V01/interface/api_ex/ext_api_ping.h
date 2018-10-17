/*
 * ext_api_ping.h
 *
 *  Created on: 17.10.2018
 *      Author: Georgi Angelov
 */

#ifndef EXT_API_PING_H_
#define EXT_API_PING_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum {
	PING_OK = 0x0, PING_ERROR = 0x1, PING_RUNNING = 0x2,
} ping_status_t;

typedef enum {
	PING_PACKET_RESULT = 0x0, PING_TOTAL_RESULT = 0x1,
} ping_result_type_t;

typedef void (*ping_request_result_t)(ping_result_type_t, void *);

typedef struct {
	uint32_t count;
	uint32_t size;
	uint32_t recv_timeout;
	uint32_t interval;
	ping_request_result_t callback;
	uint8_t *addr;
} ping_para_t;

ping_status_t ping_request_ex(uint8_t addr_type, ping_para_t *para);

#endif /* EXT_API_PING_H_ */
