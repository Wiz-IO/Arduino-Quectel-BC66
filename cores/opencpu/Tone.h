#ifndef __TONE_H__
#define __TONE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef __cplusplus
}
#endif

extern void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0);
extern void noTone(uint8_t pin);

#endif //Tone.h