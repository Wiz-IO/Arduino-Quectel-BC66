/*
  wiring_pulse.c - pulseIn() function
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#include <Arduino.h>

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
  uint32_t init_time = micros();
  uint32_t curr_time = init_time;
  uint32_t max_time = init_time + timeout;
  int pin_state = 0;

  /* read GPIO info */
  pin_state = digitalRead(pin);

  // wait for any previous pulse to end
  while ((pin_state == state) && (curr_time < max_time))
  {
    curr_time = micros();
    pin_state = digitalRead(pin);
  }

  // wait for the pulse to start
  while ((pin_state != state) && (curr_time < max_time))
  {
    curr_time = micros();
    init_time = curr_time;
    pin_state = digitalRead(pin);
  }

  // wait for the pulse to stop
  while ((pin_state == state) && (curr_time < max_time))
  {
    curr_time = micros();
    pin_state = digitalRead(pin);
  }

  if (curr_time < max_time)
  {
    return (curr_time - init_time);
  }
  else
  {
    return 0;
  }
}