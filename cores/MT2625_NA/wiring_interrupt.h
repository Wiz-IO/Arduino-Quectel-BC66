#ifndef __WIRING_INTERRUPT_H__
#define __WIRING_INTERRUPT_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

typedef void (*voidFuncPtr)(void) ;

extern void attachInterrupt(uint32_t pin, voidFuncPtr callback, uint32_t mode);
extern void attachInterruptWithDebounce(uint32_t pin, voidFuncPtr callback, uint32_t mode, uint32_t debounceTime);
extern void detachInterrupt(uint32_t pin);

extern void interrupts(void);
extern void noInterrupts(void);

#ifdef __cplusplus
}
#endif

#endif
