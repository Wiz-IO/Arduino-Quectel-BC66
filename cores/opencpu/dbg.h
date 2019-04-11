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

#ifndef DBG_H_
#define DBG_H_

#define ENABLE_DEBUG
#define ENABLE_TRACE

void debug_enable(unsigned long port);
void debug_disable(void);

int log_printf(const char *frm, ...)  __attribute__((weak));
void log_buf(const char *text, const unsigned char *buf, unsigned int len)  __attribute__((weak));

#ifdef ENABLE_DEBUG
#   include "ql_trace.h"
#   define DBG(FORMAT, ...) log_printf(FORMAT, ##__VA_ARGS__)
#   define DMP(TEXT, BUFFER, LEN) log_buf(TEXT, (unsigned char *)BUFFER, LEN)

#   define LOG_E(FORMAT, ...) log_printf("[ERROR] " FORMAT "\n", ##__VA_ARGS__)
#   define LOG_V(FORMAT, ...) log_printf("[V] " FORMAT "\n", ##__VA_ARGS__) 
#   define LOG_D(FORMAT, ...) log_printf("[D] " FORMAT "\n", ##__VA_ARGS__) 
#   define LOG_I(FORMAT, ...) log_printf("[I] " FORMAT "\n", ##__VA_ARGS__) 
#   define LOG_W(FORMAT, ...) log_printf("[W] " FORMAT "\n", ##__VA_ARGS__) 

#else
#   define DBG(FORMAT, ...) 
#   define DMP(TEXT, BUFFER, LEN)

#   define LOG_E(FORMAT, ...) 
#   define LOG_V(FORMAT, ...)  
#   define LOG_D(FORMAT, ...) 
#   define LOG_I(FORMAT, ...) 
#   define LOG_W(FORMAT, ...) 
#endif

#endif /* DBG_H_ */
