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

#include <string.h>
#include <inttypes.h>
#include "Arduino.h"
#include "HardwareSerial.h"

extern "C" void debug_enable(unsigned long port);
extern "C" void debug_disable(void);

void HardwareSerial::debug(void)
{
    debug_enable(port);
}

void HardwareSerial::nodebug(void)
{
    debug_disable();
}

void HardwareSerial::MUTEX_LOCK()
{
    if (mutex)
        while (xSemaphoreTake(mutex, portMAX_DELAY) != pdPASS)
            ;
}

void HardwareSerial::MUTEX_UNLOCK()
{
    if (mutex)
        xSemaphoreGive(mutex);
}

/*static*/ void HardwareSerial::callback(Enum_SerialPort ql_port, Enum_UARTEventType event, bool pinLevel, void *serial)
{
    if (serial)
        if (event == EVENT_UART_READY_TO_READ)
        {
            uint8_t byte;
            HardwareSerial *p = (HardwareSerial *)serial;
            while (Ql_UART_Read(ql_port, &byte, 1) > 0)
                if (p->queue)
                    if (pdFALSE == xQueueSend(p->queue, &byte, 0))
                        return; //full
        }
}

  HardwareSerial::HardwareSerial(uint32_t id)
  {
    port = (Enum_SerialPort)id;    
    queue = NULL;
    mutex = NULL;    
  }

void HardwareSerial::end()
{
    MUTEX_LOCK();
    Ql_UART_Close(port);
    if (queue)
    {
        vQueueDelete(queue);
        queue = NULL;
    }
    MUTEX_UNLOCK();
}

void HardwareSerial::begin(unsigned long baud, void *config) // TODO
{
    if (mutex == NULL)
    {
        mutex = xSemaphoreCreateMutex();
        if (mutex == NULL)
            return;
    }
    if (queue == NULL)
        queue = xQueueCreate(SERIAL_BUFFER_SIZE, sizeof(uint8_t));
    if (queue)
    {
        if (QL_RET_OK == Ql_UART_Register(port, callback, this))
        {
            if (config)
                Ql_UART_OpenEx(port, (ST_UARTDCB *)config);
            else
                Ql_UART_Open(port, baud, FC_NONE);
        }
    }
}

void HardwareSerial::begin(unsigned long baud)
{
    begin(baud, NULL);
}

size_t HardwareSerial::write(uint8_t c)
{
    MUTEX_LOCK();
    int ret = Ql_UART_Write(port, &c, 1);
    MUTEX_UNLOCK();
    return ret;
}

size_t HardwareSerial::write(const uint8_t *buf, size_t size)
{
    int ret = 0;
    if (buf && size)
    {
        MUTEX_LOCK();
        ret = Ql_UART_Write(port, (uint8_t *)buf, size);
        MUTEX_UNLOCK();
    }
    return ret;
}

size_t HardwareSerial::write(const char *buf)
{
    if (buf)
        return write(buf, Ql_strlen(buf));
    return 0;
}

void HardwareSerial::flush(void)
{
    if (queue)
    {
        MUTEX_LOCK();
        xQueueReset(queue);
        MUTEX_UNLOCK();
    }
}

int HardwareSerial::available()
{
    if (queue)
        return uxQueueMessagesWaiting(queue);
    return 0;
}

int HardwareSerial::peek()
{
    if (available())
    {
        uint8_t c;
        if (queue)
            if (xQueuePeek(queue, &c, 0))
                return c;
    }
    return -1;
}

int HardwareSerial::read(void)
{
    if (available())
    {
        uint8_t c;
        if (queue)
            if (xQueueReceive(queue, &c, 0))
                return c;
    }
    return -1;
}

size_t HardwareSerial::setRxBufferSize(size_t new_size)
{
    MUTEX_LOCK();
    if (queue)
    {
        vQueueDelete(queue);
        queue = xQueueCreate(new_size, sizeof(uint8_t));
        if (queue == NULL)
            return 0;
    }
    MUTEX_UNLOCK();
    return new_size;
}