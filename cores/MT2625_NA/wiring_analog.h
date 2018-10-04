/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_ANALOG_
#define _WIRING_ANALOG_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*
 * \brief Configures the reference voltage used for analog input (i.e. the value used as the top of the input range).
 * This function is kept only for compatibility with existing AVR based API.
 *
 * \param ulMmode Should be set to AR_DEFAULT.
 */
//extern void analogReference( );

/*
 * \brief Writes an analog value (PWM wave) to a pin.
 *
 * \param ulPin
 * \param ulValue
 */
extern void analogWrite( uint32_t ulPin, uint32_t ulValue );

/*
 * \brief Reads the value from the specified analog pin.
 *
 * \param ulPin
 *
 * \return Read value from selected pin, if no error.
 */
extern uint32_t analogRead( uint32_t ulPin );

/*
 * \brief Set the resolution of analogRead return values.
 *
 * \param res
 */
extern void analogReadResolution(int res);

/*
 * \brief Set the resolution of analogWrite parameters.
 *
 * \param res
 */
extern void analogWriteResolution(uint32_t res);



void analogOpen(uint32_t pin, ...);
void analogClose(uint32_t pin);
void analogWriteOnOff(uint32_t pin, bool on_off);


#ifdef __cplusplus
}
#endif

#endif /* _WIRING_ANALOG_ */
