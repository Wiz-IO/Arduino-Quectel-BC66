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

#ifndef API_H_
#define API_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"

#include "lwip/lwipopts.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"

#include "api_hal.h"
#include "api_tel.h"
#include "api_ssl.h"
#include "api_http.h"
#include "api_ping.h"
#include "api_json.h"
#include "api_ril.h"
#include "api_nvdm.h"
#include "api_lwm2m.h"
#include "api_mqtt.h"
#include "api_fota.h"

int api_check_api(void);
const char *api_get_version(void);

void api_delay_us(uint32_t us);
uint32_t api_get_micro(void);
uint32_t api_get_cpu_speed(void);
int api_set_cpu_speed(uint32_t kHz);

uint32_t api_get_random(void);

void api_get_imei(char *imei, unsigned int size); // must [16]
bool api_get_uid(uint8_t *uid, uint32_t len);

typedef enum
{
  SIM_NOT_READY = 0x0,
  SIM_PIN = 0x1,
  SIM_PUK = 0x2,
  SIM_READY = 0x3,
  SIM_PIN2 = 0x4,
  SIM_PUK2 = 0x5,
  SIM_UPIN = 0x6,
  SIM_UPUK = 0x7,
  NUM_OF_SIM_STATES = 0x8,
} SimState_e;

int api_get_sim_status(void);
uint32_t api_get_mcc_mnc(void);   //0001.0284 - MTEL = 284.01
void api_get_imsi(char *buffer);  //len = 9
void api_get_iccid(char *buffer); //len = 10

int api_get_creg(void);
int api_get_cereg(void);
int api_get_receive_level(void);
int api_get_quality(void);
int api_get_access(void);
void api_get_mlts_string(char *buf, unsigned int size); // [322]
uint32_t api_get_local_ip(unsigned int index);

uint16_t api_get_cell_tac(void);
uint32_t api_get_cell_cid(void);

uint8_t api_get_psm_active(void);
uint8_t api_get_psm_periodic(void);

int api_rtc_register(void (*callback)(unsigned int, void *), void *param);
int api_rtc_start(unsigned int interval, uint8_t autoRepeat);
int api_rtc_stop(void);

int api_SaveAndSetIRQMask(void) __attribute__((weak));
void api_RestoreIRQMask(int) __attribute__((weak));

////////////////////////////////////////////////////////////////////////////
// NETWORK
////////////////////////////////////////////////////////////////////////////

//char *bzero(char *result, int a2);
uint16_t lwip_htons(uint16_t n);
uint16_t lwip_ntohs(uint16_t n);
uint32_t lwip_htonl(uint32_t n);
uint32_t lwip_ntohl(uint32_t n);

int lwip_getaddrinfo(const char *host, const char *server, const struct addrinfo *hints, struct addrinfo **res);
void lwip_freeaddrinfo(struct addrinfo *ai);
int resolveAddress(const char *server, struct sockaddr_in *addr);

#endif /* API_H_ */
