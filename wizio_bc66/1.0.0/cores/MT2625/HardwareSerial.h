/*
 HardwareSerial.h - Hardware serial library for Wiring
 Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <interface.h>
#include "Stream.h"

class HardwareSerial: public Stream {

protected:
	uint8_t  rx_ring_buff[1024];
	uint32_t rx_ring_tail;
	uint32_t rx_ring_head;

private:
public:
	Enum_SerialPort port;
	uint32_t brg;
	uint32_t event;
	int error;
	int save(uint8_t c);

	HardwareSerial(uint32_t id);
	~HardwareSerial(){};
	void begin(unsigned long);
	void end(void);
	size_t send(uint8_t * buf, size_t size);
	size_t send(const char * buf);
	virtual int available(void);
	virtual int peek(void);
	virtual int read(void);
	virtual void flush(void) {};
	virtual size_t write(uint8_t);
	virtual size_t write(const char * s);
	using Print::write;

	size_t write(uint8_t * buf, size_t size);
};

extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;

#endif

