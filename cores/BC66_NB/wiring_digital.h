#ifndef __WIRING_DIGITAL_H__
#define __WIRING_DIGITAL_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

extern void pinMode(uint32_t pin, uint32_t mode);
extern void digitalWrite(uint32_t pin, uint32_t value);
extern int  digitalRead(uint32_t pin);

#ifdef __cplusplus
}
#endif

#endif
