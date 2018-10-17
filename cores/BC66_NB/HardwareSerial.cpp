/*
 HardwareSerial.cpp
 Copyright (c) 2018 Georgi Angelov. All right reserved.

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

 Modified: 08.08.2018 by Georgi Angelov

 */

#include "HardwareSerial.h"

HardwareSerial::HardwareSerial(uint32_t id) {
	event = 0;
	error = 0;
	brg = 0;
	rx_ring_tail = 0;
	rx_ring_head = 0;
	port = (Enum_SerialPort) id;
	if (id < UART_PORT_END)
		port = (Enum_SerialPort) id;
}

int HardwareSerial::save(uint8_t c) {
	uint32_t i = (uint32_t) (rx_ring_head + 1) % sizeof(rx_ring_buff);
	if (i != rx_ring_tail) {
		rx_ring_buff[rx_ring_head] = c;
		rx_ring_head = i;
		return 0; // saved
	}
	return 1; // full
}

void HardwareSerial::begin(unsigned long baudrate) {
	brg = baudrate;
	if (!event)
		event = Ql_OS_CreateEvent();
	Ql_OS_SendMessage(0, MSG_UART_OPEN, (uint32_t) this, 1);
	Ql_OS_WaitEvent(event, 1, -1);
}

void HardwareSerial::end() {
	Ql_UART_Close((Enum_SerialPort) port);
}

int HardwareSerial::available(void) {
	return (uint32_t) (sizeof(rx_ring_buff) + rx_ring_head - rx_ring_tail) % sizeof(rx_ring_buff);
}

int HardwareSerial::peek(void) {
	if (rx_ring_head == rx_ring_tail)
		return -1;
	return rx_ring_buff[rx_ring_tail];
}

int HardwareSerial::read(void) {
	if (rx_ring_head == rx_ring_tail)
		return -1;
	uint8_t rc = rx_ring_buff[rx_ring_tail];
	rx_ring_tail = (uint32_t) (rx_ring_tail + 1) % sizeof(rx_ring_buff);
	return rc;
}

size_t HardwareSerial::write(uint8_t c) {
	return Ql_UART_Write(port, &c, 1);
}

size_t HardwareSerial::write(const char * s) {
	return Ql_UART_Write(port, (u8*)s, Ql_strlen(s));
}

size_t HardwareSerial::write(uint8_t * buf, size_t size) {
	return Ql_UART_Write(port, buf, size);
}

