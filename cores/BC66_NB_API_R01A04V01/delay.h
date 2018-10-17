#ifndef __DELAY_H__
#define __DELAY_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <interface.h>

static inline bool time_after(uint32_t a, uint32_t b) { return ((int32_t)((b) - (a)) < 0); }
void delay(unsigned int t);
uint32_t micros(void);

#define millis()					( xTaskGetTickCount() * 10 )
#define seconds()					( millis() / 1000 )
#define delayMicro( _uS_ )			hal_gpt_delay_us( _uS_ )
#define delaySeconds( _sec_ )   	Ql_Sleep( _sec_ * 1000)

#ifdef __cplusplus
}
#endif
#endif
