/*
 * api.h
 *
 *  Created on: 05.10.2018
 *      Author: Georgi Angelov
 */

#ifndef API_H_
#define API_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include "ext_api_hal.h"
#include "ext_api_tel.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"

#include "lwip/lwipopts.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "ext_api_ssl.h"
#include "ext_api_mqtt.h"
#include "ext_api_http.h"
#include "ext_api_ping.h"
#include "ext_api_json.h"
#include "ext_api_ril.h"

uint16_t lwip_htons(uint16_t n);
uint16_t lwip_ntohs(uint16_t n);
uint32_t lwip_htonl(uint32_t n);
uint32_t lwip_ntohl(uint32_t n);

int lwip_getaddrinfo(const char *host, const char *server, const struct addrinfo *hints, struct addrinfo **res);
void lwip_freeaddrinfo(struct addrinfo *ai);


const char * getVersion(void);
int checkApi(void);
void platform_assert(const char *expr, const char *file, int line);

int receiveQuality(void);
int receiveLevel(void);
int serviceStatus(void);

int resolveAddress(const char *server, struct sockaddr_in *addr);

#endif /* API_H_ */
