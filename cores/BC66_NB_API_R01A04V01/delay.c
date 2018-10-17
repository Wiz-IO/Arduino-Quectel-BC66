#include "variant.h"
#include "delay.h"


uint32_t micros(void) {
	uint32_t us;
	hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &us);
	return us;
}


void delay(unsigned int t) {
	if (t < 10)
		t = 10;
	Ql_Sleep(t);
}
