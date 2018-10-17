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

#ifndef _WIRING_CONSTANTS_
#define _WIRING_CONSTANTS_

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

typedef enum {
	CLOSE				= 0,
	INPUT 				= 1,
	OUTPUT				= 2,
	PULLUP				= 4,
	PULLDOWN			= 8,
	INPUT_PULLUP		= INPUT | PULLUP,
	INPUT_PULLDOWN		= INPUT | PULLDOWN,
} PinMode;

#define LOW					(0x0)
#define HIGH				(0x1)

#define CHANGE				(0x2)
#define FALLING				(0x3)
#define RISING				(0x4)

#define DEFAULT				(0x1)
#define EXTERNAL			(0x0)

enum BitOrder {
	LSBFIRST = 0,
	MSBFIRST = 1
};

#define PI					3.1415926535897932384626433832795
#define HALF_PI				1.5707963267948966192313216916398
#define TWO_PI				6.283185307179586476925286766559
#define DEG_TO_RAD			0.017453292519943295769236907684886
#define RAD_TO_DEG			57.295779513082320876798154814105
#define EULER				2.718281828459045235360287471352

#define min(a,b)			((a)<(b)?(a):(b))
#define max(a,b)			((a)>(b)?(a):(b))

#define constrain(amt,low,high)		((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#define round(x)			((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg)			((deg)*DEG_TO_RAD)
#define degrees(rad)			((rad)*RAD_TO_DEG)

#define lowByte(w)			((uint8_t) ((w) & 0xff))
#define highByte(w)			((uint8_t) ((w) >> 8))

#define bit(b)				(1UL << (b))

#define bitRead(value, bit)		(((value) >> (bit)) & 0x01)
#define bitSet(value, bit)		((value) |= (1UL << (bit)))
#define bitClear(value, bit)		((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue)	(bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef unsigned int			word;
typedef unsigned char			byte;
typedef unsigned char			boolean;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* _WIRING_CONSTANTS_ */
