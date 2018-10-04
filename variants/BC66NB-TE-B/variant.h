#ifndef __VARIANT_H__
#define __VARIANT_H__
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

uint32_t cpuSpeed(uint32_t speed);
int setCpuSpeed(uint32_t s);
uint32_t getCpuSpeed(void);
uint32_t clockCyclesPerMicrosecond(void);
uint32_t clockCyclesToMicroseconds(uint32_t a);
uint32_t microsecondsToClockCycles(uint32_t a);

void init(void);

#define F_GPIO	1
#define F_UART	2
#define F_SPI	4
#define F_I2C	8
#define F_PWM	16
#define F_ADC	32

typedef enum _PinTypes {
	M_FREE = 0,
	M_GPIO,
	M_EINT,
	M_UART,
	M_SPI,
	M_I2C,
	M_PWM,
	M_ADC,
	M_MAX,
} PinTypes;

typedef struct {
	uint32_t arduino;
	uint32_t quectel;
	uint32_t mode;
	const uint32_t function;
} PinDescription;

PinDescription * getPin(uint32_t pin);
PinDescription * getAdc(uint32_t pin);

#define LED_BUILTIN 0


#ifdef __cplusplus
}
#endif
#endif /* __VARIANT_H__ */
