/*
  BC66 - debug
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

#include "ql_stdlib.h"
#include "ql_uart.h"
#include "dbg.h"
#include "api.h"

static Enum_SerialPort debugPort = UART_PORT_END;
static u32 debugMutex = 0;

void debug_enable(unsigned long port)
{
	if (0 == debugMutex)
		debugMutex = Ql_OS_CreateMutex();
	debugPort = (Enum_SerialPort)port;
}

void debug_disable(void)
{
	debugPort = (Enum_SerialPort)UART_PORT_END;
}

#ifdef ENABLE_DEBUG

static char bufferDebug[1024];

int log_printf(const char *frm, ...)
{
	if (0 == debugMutex || debugPort > UART_PORT2)
		return 0;
	va_list arg;
	va_start(arg, frm);
	if (debugMutex)
		Ql_OS_TakeMutex(debugMutex, -1);
	int n = vsnprintf(bufferDebug, sizeof(bufferDebug), frm, arg);
	va_end(arg);
	if (n > 0)
		n = Ql_UART_Write(debugPort, (u8 *)bufferDebug, n);
	if (debugMutex)
		Ql_OS_GiveMutex(debugMutex);
	return n;
}

void log_buf(const char *text, const unsigned char *buf, unsigned int len)
{
	if (len > 512)
		len = 512;
	char bufferChar[17];
	char bufferDump[512];
	unsigned int i, idx = 0;
	memset(bufferDump, 0, sizeof(bufferDump));
	Ql_snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "[DMP] %s (%u bytes)\n", text, len);
	log_printf(bufferDump);
	idx = 0;
	Ql_memset(bufferChar, 0, sizeof(bufferChar));
	for (i = 0; i < len; i++)
	{
		if (i >= 4096)
			break;
		if (i % 16 == 0)
		{
			if (i > 0)
			{
				Ql_snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "  %s\n", bufferChar);
				log_printf(bufferDump);
				idx = 0;
				Ql_memset(bufferChar, 0, sizeof(bufferChar));
			}
			idx += Ql_snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "%04X: ", (unsigned int)i);
		}
		idx += Ql_snprintf(bufferDump + idx, sizeof(bufferDump) - idx, " %02X", (unsigned int)buf[i]);
		bufferChar[i % 16] = (buf[i] > 31 && buf[i] < 127) ? buf[i] : '.';
	}
	if (len > 0)
	{
		for (/* i = i */; i % 16 != 0; i++)
			idx += Ql_snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "   ");
		Ql_snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "  %s\n", bufferChar);
		log_printf(bufferDump);
	}
}

#endif