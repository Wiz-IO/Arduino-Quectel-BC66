/*
  BC66 - wiring
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

#include <interface.h>
#include <variant.h>

inline void yield(void)
{
  Ql_Sleep(10);
}

unsigned int millis()
{
  return xTaskGetTickCount() * 10;
}

unsigned int seconds(void)
{
  return millis() / 1000;
}

inline unsigned int micros()
{
  return api_get_micro();
}

inline void delayMicroseconds(unsigned int us)
{
  api_delay_us(us);
}

void delay(unsigned int ms)
{
  if (ms < 10)
    ms = 10;
  Ql_Sleep(ms);
}

uint32_t clockCyclesPerMicrosecond(void)
{
    return api_get_cpu_speed();
}

uint32_t clockCyclesToMicroseconds(uint32_t a)
{
    return a / clockCyclesPerMicrosecond();
}

uint32_t microsecondsToClockCycles(uint32_t a)
{
    return a * clockCyclesPerMicrosecond();
}

#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))
PinDescription *getArduinoPin(uint8_t arduinoPin)
{
  for (int i = 0; i < ARRAYLEN(pinsMap); i++)
    if (pinsMap[i].arduino == arduinoPin)
      return &pinsMap[i];
  return NULL;
}

PinDescription *getDevicePin(uint8_t devicePin)
{
  for (int i = 0; i < ARRAYLEN(pinsMap); i++)
    if (pinsMap[i].device == devicePin)
      return &pinsMap[i];
  return NULL;
}

static void eint_callback(Enum_PinName eintPinName, Enum_PinLevel pinLevel, void *user)
{
  Enum_PinName pin = (Enum_PinName)user;
  PinDescription *n = getDevicePin(pin);
  if (n && n->eint)
  {
    Ql_EINT_Mask(pin);
    eint_callback_t cb = (eint_callback_t)n->eint;
    cb(Ql_EINT_GetLevel(n->device));
    Ql_EINT_Unmask(pin);
  }
}

void eintMode(uint8_t pin, Enum_EintType type, eint_callback_t cb, uint32_t hwDebounce, uint32_t swDebounce, bool automask)
{
  PinDescription *n = getArduinoPin(pin);
  if (n)
  {
    if (type == END_OF_HAL_EINT)
    {
      Ql_EINT_Uninit(n->device);
    }
    else if (cb)
    {
      n->eint = cb;
      Ql_EINT_RegisterFast(n->device, eint_callback, (void *)((int)n->device));
      Ql_EINT_Init(n->device, type, hwDebounce, swDebounce, automask);
    }
  }
}

static int _irq_;

void interrupts(void)
{
  api_RestoreIRQMask(_irq_);
}

void noInterrupts(void)
{
  _irq_ = api_SaveAndSetIRQMask();
}