/*
 * device.h
 *
 *  Created on: 15.10.2018
 *      Author: Georgi Angelov
 */

#ifndef DEVICE_H_
#define DEVICE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

int setCpuSpeed(uint32_t s);
uint32_t cpuSpeed(uint32_t speed);
uint32_t getCpuSpeed(void);
uint32_t clockCyclesPerMicrosecond(void);
uint32_t clockCyclesToMicroseconds(uint32_t a);
uint32_t microsecondsToClockCycles(uint32_t a);

#ifdef __cplusplus
}
#endif
#endif /* DEVICE_H_ */
