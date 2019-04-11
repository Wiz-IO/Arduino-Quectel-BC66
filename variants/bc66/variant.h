/*
 *  Created on: 01.15.2019
 *      Author: Georgi Angelov
 */

#ifndef __VARIANT_H__
#define __VARIANT_H__

#include <interface.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define LED 4         /* PINNAME_NETLIGHT */
#define LED_BUILTIN 4 /* PINNAME_NETLIGHT */
#define ADC0 PIN_ADC0 /* ONLY THIS PIN */
#define PWM0 PINNAME_NETLIGHT
#define PWM1 PINNAME_RTS_AUX
#define PWM2 PINNAME_GPIO3

    typedef struct
    {
        uint8_t arduino;
        uint8_t device;
        void *eint;
    } PinDescription;
    extern PinDescription pinsMap[18];

    PinDescription *getArduinoPin(uint8_t arduinoPin);
    PinDescription *getDevicePin(uint8_t devicePin);

    typedef void (*eint_callback_t)(uint32_t level);
    void eintMode(uint8_t pin, Enum_EintType type, eint_callback_t cb, uint32_t hwDebounce, uint32_t swDebounce, bool automask);

    void analogReference(uint8_t mode) __attribute__((weak));
    void analogOpen(uint8_t pin, /* val, src, div */...);
    void analogClose(uint8_t pin);
    int analogRead(uint8_t pin);
    void analogWrite(uint8_t pin, int val);

#ifdef __cplusplus
}

void initVariant();

#include <HardwareSerial.h>
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;

#include <DEV.h>
extern DeviceClass Dev;

#include <PSM.h>
extern PSMClass Psm;

#endif //__cplusplus

#endif /* __VARIANT_H__ */
