/*
 * device.c
 *
 *  Created on: 15.10.2018
 *      Author: georgi.angelov
 */

#include "ext_api_hal.h"
#include "device.h"
#include "debug.h"

int setCpuSpeed(uint32_t s) {
	s /= 1000;
	switch (s) {
	case 26000:
	case 78000:
	case 104000:
	case 156000:
		return hal_dvfs_target_cpu_frequency(s, HAL_DVFS_FREQ_RELATION_L);
	}
	return 1;
}

uint32_t cpuSpeed(uint32_t speed) {
	uint32_t s = getCpuSpeed() * 1000;
	LOG("[DBG] CPU Frequency: %d Hz\n", s);
	if (speed) {
		setCpuSpeed(speed);
		s = getCpuSpeed() * 1000;
		LOG("[DBG] New Frequency: %d Hz\n", s);
	}
	return s;
}

uint32_t getCpuSpeed(void) {
	return hal_dvfs_get_cpu_frequency(0, 0, 0, 0);
}

uint32_t clockCyclesPerMicrosecond(void) {
	return getCpuSpeed();
}

uint32_t clockCyclesToMicroseconds(uint32_t a) {
	return a / clockCyclesPerMicrosecond();
}

uint32_t microsecondsToClockCycles(uint32_t a) {
	return a * clockCyclesPerMicrosecond();
}


