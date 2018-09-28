#include "variant.h"
#include "delay.h"

#ifdef API_EX
uint32_t micros(void) {
	uint32_t us;
	hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &us);
	return us;
}
#else

unsigned int __millis = 0;

unsigned int millis(void) {
	return __millis;
}

unsigned int seconds(void) {
	return __millis / 1000;
}

void delay(unsigned int t) {
	if (t < 10)
		t = 10;
	Ql_Sleep(t);
}

#endif

