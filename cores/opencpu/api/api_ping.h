/*
  BC66 - API
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

#ifndef API_PING_H_
#define API_PING_H_

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

#endif /* API_PING_H_ */
