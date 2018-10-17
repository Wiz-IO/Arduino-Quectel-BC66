/* 
 core_esp8266_noniso.c - nonstandard (but usefull) conversion functions
 Copyright (c) 2014 Ivan Grokhotkov. All rights reserved.
 This file is part of the esp8266 core for Arduino environment.
 
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
 Modified 03 April 2015 by Markus Sattler
 */

#include <interface.h>
#include "stdlib_noniso.h"
#include "math.h"
#include "inttypes.h"

static const char * str_digits = "0123456789abcdef";

void reverse(char* begin, char* end) {
	char *is = begin;
	char *ie = end - 1;
	while (is < ie) {
		char tmp = *ie;
		*ie = *is;
		*is = tmp;
		++is;
		--ie;
	}
}

#if 0 // Ql_atoi
extern int atoi(const char* s) {
	return (int) atol(s);
}
#endif

extern long atol(const char* s) {
	char * tmp;
	return strtol(s, &tmp, 10);
}

extern char* itoa(int value, char* result, int base) {
	if (base < 2 || base > 16) {
		*result = 0;
		return result;
	}
	char* out = result;
	int quotient = abs(value);
	do {
		const int tmp = quotient / base;
		*out = str_digits[quotient - (tmp * base)];
		++out;
		quotient = tmp;
	} while (quotient);
	if (value < 0)
		*out++ = '-';
	reverse(result, out);
	*out = 0;
	return result;
}

extern char* ltoa(long value, char* result, int base) {
	if (base < 2 || base > 16) {
		*result = 0;
		return result;
	}
	char* out = result;
	long quotient = abs(value);
	do {
		const long tmp = quotient / base;
		*out = str_digits[quotient - (tmp * base)];
		++out;
		quotient = tmp;
	} while (quotient);
	if (value < 0)
		*out++ = '-';
	reverse(result, out);
	*out = 0;
	return result;
}

extern char* utoa(unsigned value, char* result, int base) {
	if (base < 2 || base > 16) {
		*result = 0;
		return result;
	}
	char* out = result;
	unsigned quotient = value;
	do {
		const unsigned tmp = quotient / base;
		*out = str_digits[quotient - (tmp * base)];
		++out;
		quotient = tmp;
	} while (quotient);
	reverse(result, out);
	*out = 0;
	return result;
}

extern char* ultoa(unsigned long value, char* result, int base) {
	if (base < 2 || base > 16) {
		*result = 0;
		return result;
	}
	char* out = result;
	unsigned long quotient = value;
	do {
		const unsigned long tmp = quotient / base;
		*out = str_digits[quotient - (tmp * base)];
		++out;
		quotient = tmp;
	} while (quotient);
	reverse(result, out);
	*out = 0;
	return result;
}
