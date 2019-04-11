/*
  BC66 - analog
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

#include <variant.h>

#define PWM_MAX 8193
int api_adc_init(int pin);

int analogRead(uint8_t pin)
{
  uint32_t val = -1;
  hal_adc_get_data_polling(0, &val); // * 1400
  return val;
}

void analogWrite(uint8_t pin, int val)
{
  Ql_PWM_Output((Enum_PinName)pin, val);
}

void analogClose(uint8_t pin)
{
  switch (pin)
  {
  //case ADC0: break;
  case PWM0:
    Ql_PWM_Uninit((Enum_PinName)pin);
  }
}

void analogOpen(uint8_t pin, /* val, src, div */...)
{
  switch (pin)
  {
    case ADC0:
      api_adc_init(0);
      break;
    case PWM0:
    case PWM1:
    case PWM2:
    {
      va_list list;
      va_start(list, pin);
      uint32_t val = va_arg(list, uint32_t);
      uint32_t pwmSrcClk = va_arg(list, uint32_t);
      uint32_t pwmDiv = va_arg(list, uint32_t);
      Ql_GPIO_Uninit((Enum_PinName)pin);
      uint32_t PWM_lowPulseNum = PWM_MAX / 2;
      uint32_t PWM_highPulseNum = PWM_MAX / 2;
      Ql_PWM_Init((Enum_PinName)pin, (Enum_PwmSource)pwmSrcClk, (Enum_PwmSourceDiv)pwmDiv, PWM_lowPulseNum, PWM_highPulseNum);
      Ql_PWM_Output((Enum_PinName)pin, val);
    }
    break;
  } //switch
}
