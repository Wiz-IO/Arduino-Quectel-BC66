#include "interface.h"
#include "constants.h"
#include "wiring_digital.h"
#include "variant.h"

void pinMode(uint32_t pin, uint32_t mode) {
	PinDescription * n = getPin(pin);
	if (!n) {
		LOG("[ERROR] pinMode( %d ) unknown pin\n", pin);
		return;
	}
	if (n->function & F_ADC)
		return;
	int rc;
	Enum_PinDirection dir = PINDIRECTION_IN;
	Enum_PinLevel level = PINLEVEL_HIGH;
	Enum_PinPullSel pullSel = PINPULLSEL_DISABLE;
	if (mode == CLOSE && (n->mode == M_GPIO || n->mode == M_SPI || n->mode == M_I2C)) {
		Ql_GPIO_Uninit((Enum_PinName) n->quectel);
		n->mode = M_FREE;
		return;
	}
	if (n->mode != M_FREE) {
		LOG("[ERROR] pinMode( %d ) %d %d\n", pin, n->quectel, n->mode);
		return;
	}
	if ((mode & PULLUP) > 0) {
		pullSel = PINPULLSEL_PULLUP;
	} else if ((mode & PULLDOWN) > 0) {
		pullSel = PINPULLSEL_PULLDOWN;
	}
	if ((mode & OUTPUT) > 0)
		dir = PINDIRECTION_OUT;
	rc = Ql_GPIO_Init((Enum_PinName) n->quectel, dir, level, pullSel);
	if (rc) {
		LOG("[ERROR] Ql_GPIO_Init( %d ) %d : %d\n", rc, pin, n->quectel);
		return;
	}
	n->mode = M_GPIO;
}

void digitalWrite(uint32_t pin, uint32_t value) {
	PinDescription * n = getPin(pin);
	if (!n)
		return;
	if (n->mode != M_GPIO) {
		LOG("[ERROR] digitalWrite( %d ) %d %d\n", pin, n->quectel, n->mode);
		return;
	}
	Ql_GPIO_SetLevel((Enum_PinName) n->quectel, (Enum_PinLevel) (value & 1));
}

int digitalRead(uint32_t pin) {
	PinDescription * n = getPin(pin);
	if (!n)
		return -1;
	if (n->mode != M_GPIO) {
		LOG("[ERROR] digitalRead() %d : %d\n", pin, n->quectel);
		return -1;
	}
	return Ql_GPIO_GetLevel((Enum_PinName) n->quectel);
}
