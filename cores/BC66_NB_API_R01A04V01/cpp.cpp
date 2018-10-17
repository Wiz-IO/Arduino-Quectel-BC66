/*
 * cpp.cpp
 *
 *  Created on: 10.08.2018
 *      Author: Georgi Angelov
 */


#include <interface.h>

void * operator new(size_t size) {
	void * ret = (void*) malloc(size);
	if (0 != size && NULL == ret)
		while (1) {
		}
	return ret;
}

void * operator new[](size_t size) {
	void * ret = (void*) malloc(size);
	if (0 != size && NULL == ret)
		while (1) {
		}
	return ret;
}

void operator delete(void * ptr) {
	free(ptr);
}

void operator delete[](void * ptr) {
	free(ptr);
}
