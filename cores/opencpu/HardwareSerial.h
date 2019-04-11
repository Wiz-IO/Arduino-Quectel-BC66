/*
  BC66 - uart
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

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <inttypes.h>
#include "Stream.h"
#include <interface.h> 

class HardwareSerial : public Stream
{
protected:
  static void callback(Enum_SerialPort port, Enum_UARTEventType event, bool pinLevel, void *serial);
  Enum_SerialPort port;
// BC66
  QueueHandle_t queue, mutex;
  void MUTEX_LOCK();
  void MUTEX_UNLOCK();

public:
  int save(uint8_t c);
  HardwareSerial(uint32_t id);
  void debug(void);
  void nodebug(void);
  void begin(unsigned long baud, void *user);
  void begin(unsigned long baud);
  void end();
  size_t setRxBufferSize(size_t new_size);
  virtual int available(void);
  virtual int peek(void);
  virtual int read(void);
  virtual void flush(void);
  virtual size_t write(uint8_t);
  inline size_t write(unsigned long n) { return write((uint8_t)n); }
  inline size_t write(long n) { return write((uint8_t)n); }
  inline size_t write(unsigned int n) { return write((uint8_t)n); }
  inline size_t write(int n) { return write((uint8_t)n); }
  size_t write(const char *buf);
  size_t write(const uint8_t *buf, size_t size);    
  using Print::write;
  operator bool() { return true; }
};

#endif
