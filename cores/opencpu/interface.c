/*
  BC66 - interface
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

#include "interface.h"

////////////////////////////////////////////////////////////////////////////
// CPP 
////////////////////////////////////////////////////////////////////////////

extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));
extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));

extern void _init(void) __attribute__((weak));
extern void _fini(void) __attribute__((weak));

void __libc_init_array(void)
{
	size_t count;
	size_t i;
	count = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < count; i++)
		__preinit_array_start[i]();
	_init();
	count = __init_array_end - __init_array_start;
	for (i = 0; i < count; i++)
		__init_array_start[i]();
}

void __libc_fini_array(void)
{
	size_t count;
	size_t i;
	count = __fini_array_end - __fini_array_start;
	for (i = count; i > 0; i--)
		__fini_array_start[i - 1]();
	_fini();
}

extern void abort(void)
{
	while (1) {
		Ql_Sleep(1000);
	}
}

void __cxa_finalize(void *handle) {}
void __cxa_pure_virtual(void)
{
	abort();
}

void __cxa_deleted_virtual(void)
{
	abort();
}

////////////////////////////////////////////////////////////////////////////
// MEMORY
////////////////////////////////////////////////////////////////////////////

extern void *malloc(size_t size)
{
	return pvPortMalloc(size);
}

extern void free(void *p)
{
	vPortFree(p);
}

extern void *calloc(size_t nelem, size_t elsize)
{
	return pvPortCalloc(nelem, elsize);
}

extern void *realloc(void *mem, size_t newsize)
{
	return pvPortRealloc(mem, newsize);
}

////////////////////////////////////////////////////////////////////////////
// OTHER
////////////////////////////////////////////////////////////////////////////

int isAtEnd(char *line, u32 len)
{
    if (Ql_RIL_FindLine(line, len, (char *)"OK"))
        return RIL_ATRSP_SUCCESS;
    if (Ql_RIL_FindLine(line, len, (char *)"ERROR"))
        return RIL_ATRSP_FAILED;
    return RIL_ATRSP_CONTINUE;
}
