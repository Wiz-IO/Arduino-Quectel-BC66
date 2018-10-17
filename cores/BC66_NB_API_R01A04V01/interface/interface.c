/*
 * interface.c
 *
 *  Created on: 11.07.2018
 *      Author: Georgi Angelov
 */

#include "interface.h"

void * __dso_handle = 0;

int __aeabi_atexit(void *object, void (*dtor)(void* /*this*/), void *handle) {
	return 1;
}

int __cxa_atexit(void (*dtor)(void* /*this*/), void *object, void *handle) {
	return 1;
}

void __cxa_finalize(void *handle) {
}

void __cxa_pure_virtual(void) {
	while (1)
		;
}
void __cxa_deleted_virtual(void) {
	while (1)
		;
}

void abort() {
	while (1)
		;
}

extern void* memcpy(void* dest, const void* src, u32 size) {
	return Ql_memcpy(dest, src, size);
}

/* need for quectel lib */
extern void * memset(void *dst, int c, size_t n) {
	if (n) {
		char *d = dst;
		do {
			*d++ = c;
		} while (--n);
	}
	return dst;
}

extern int isdigit(int c) {
	return Ql_isdigit(c);
}

/* MEMORY */
extern void * malloc(u32 size) {
	return Ql_MEM_Alloc(size);
}

extern void free(void *p) {
	if (p)
		Ql_MEM_Free(p);
}

extern void *calloc(size_t nelem, size_t elsize) {
	return pvPortCalloc(nelem, elsize);
}

extern void *realloc(void *mem, size_t newsize) {
	return pvPortRealloc(mem, newsize);
}

/* CPP & HEAP */
extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));
extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));

extern void _init(void) __attribute__((weak));
extern void _fini(void) __attribute__((weak));

void __libc_init_array(void);
void __libc_fini_array(void);

void __libc_init_array(void) {
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

void __libc_fini_array(void) {
	size_t count;
	size_t i;
	count = __fini_array_end - __fini_array_start;
	for (i = count; i > 0; i--)
		__fini_array_start[i - 1]();
	_fini();
}

