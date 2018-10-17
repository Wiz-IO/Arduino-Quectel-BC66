/*
 * ext_api_hal.h
 *
 *  Created on: 17.10.2018
 *      Author: Georgi Angelov
 */

#ifndef EXT_API_HAL_H_
#define EXT_API_HAL_H_

#include <stdint.h>
#include <stddef.h>

/* DELAY */
typedef enum {
	HAL_GPT_STATUS_ERROR_PORT_USED = 0xFC,
	HAL_GPT_STATUS_ERROR = 0xFD,
	HAL_GPT_STATUS_ERROR_PORT = 0xFE,
	HAL_GPT_STATUS_INVALID_PARAMETER = 0xFF,
	HAL_GPT_STATUS_OK = 0x0,
} hal_gpt_status_t;

typedef enum {
	HAL_GPT_CLOCK_SOURCE_32K = 0x0, HAL_GPT_CLOCK_SOURCE_1M = 0x1,
} hal_gpt_clock_source_t;

hal_gpt_status_t hal_gpt_get_free_run_count(hal_gpt_clock_source_t clock_source, uint32_t *count);
hal_gpt_status_t hal_gpt_delay_us(uint32_t us);

/* CPU */ //AT+CPUFGET? 156000, 104000, 78000, 26000
typedef enum {
	HAL_DVFS_FREQ_RELATION_L = 0x0,
	HAL_DVFS_FREQ_RELATION_H = 0x1,
} hal_dvfs_freq_relation_t;

typedef enum {
	HAL_DVFS_STATUS_NOT_PERMITTED = 0xFB,
	HAL_DVFS_STATUS_BUSY = 0xFC,
	HAL_DVFS_STATUS_UNINITIALIZED = 0xFD,
	HAL_DVFS_STATUS_INVALID_PARAM = 0xFE,
	HAL_DVFS_STATUS_ERROR = 0xFF,
	HAL_DVFS_STATUS_OK = 0x0,
} hal_dvfs_status_t;

uint32_t hal_dvfs_get_cpu_frequency(int a1, int a2, int a3, int a4);
hal_dvfs_status_t hal_dvfs_target_cpu_frequency(uint32_t target_freq, hal_dvfs_freq_relation_t relation);

typedef struct {
	uint8_t rtc_sec;
	uint8_t rtc_min;
	uint8_t rtc_hour;
	uint8_t rtc_day;
	uint8_t rtc_mon;
	uint8_t rtc_week;
	uint8_t rtc_year;
	uint16_t rtc_milli_sec;
} hal_rtc_time_t;

uint8_t tryLightSleep(uint32_t try_sleep_ms);
int tryDeepSleep(void);

#endif /* EXT_API_HAL_H_ */
