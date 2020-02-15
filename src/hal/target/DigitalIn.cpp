#include "DigitalIn.hpp"
#include "stm32f4xx_ll_gpio.h"

GPIO_DEF_DECLARATION

DigitalIn::DigitalIn(GPIO_Def* const GPIOx, const uint32_t pin, const Pull pull):
GPIO(GPIOx, pin) {
	LL_GPIO_SetPinMode(GPIOx, pin, static_cast<uint32_t>(PinMode::INPUT));
	LL_GPIO_SetPinPull(GPIOx, pin, static_cast<uint32_t>(pull));
}

bool DigitalIn::read() {
	return static_cast<bool>(LL_GPIO_IsInputPinSet(GPIOx, pin_number));
}