/*
 IPAddress.cpp methods to handle and pass around IP addresses
 Copyright (C) 2014 Intel Corporation

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
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

 */
#include <Arduino.h>
#include <IPAddress.h>


IPAddress::IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) {
	ADDR = (((uint32_t) fourth_octet) << 24 | ((uint32_t) third_octet) << 16 | ((uint32_t) second_octet) << 8 | ((uint32_t) first_octet));
}

IPAddress::IPAddress(const uint8_t * address) {
	ADDR = inet_addr((char* )address);
}

IPAddress& IPAddress::operator=(const uint8_t * address) {
	ADDR = inet_addr((char* )address);
	return *this;
}

IPAddress& IPAddress::operator=(uint32_t address) {
	ADDR = address;
	return *this;
}

IPAddress& IPAddress::operator=(struct sockaddr_in * p_sin) {
	ADDR = p_sin->sin_addr.s_addr;
	return *this;
}

bool IPAddress::operator==(const uint8_t * address) {
	return ADDR == inet_addr((char* )address);
}

size_t IPAddress::printTo(Print& p) const {
	char buffer[sizeof("255.255.255.255")];
	sprintf(buffer, "%u.%u.%u.%u",
			(unsigned int)(ADDR & 0xFF),
			(unsigned int)(ADDR & 0xFF00) >> 8,
			(unsigned int)(ADDR & 0xFF0000) >> 16,
			(unsigned int)(ADDR & 0xFF000000) >> 24);
	p.print(buffer);
	return strlen(buffer);
}

String IPAddress::toString() const {
	char buffer[sizeof("255.255.255.255")];
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%u.%u.%u.%u",
			(unsigned int)(ADDR & 0xFF),
			(unsigned int)(ADDR & 0xFF00) >> 8,
			(unsigned int)(ADDR & 0xFF0000) >> 16,
			(unsigned int)(ADDR & 0xFF000000) >> 24);
    return String(buffer);
}
