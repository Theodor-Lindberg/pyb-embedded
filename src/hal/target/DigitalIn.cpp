#include "DigitalIn.hpp"
#include "stm32f4xx_ll_gpio.h"


DigitalIn::DigitalIn(Port port, const Pin pin, const Pull pull): GPIO(port, pin) {
	LL_GPIO_SetPinMode(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number)), static_cast<uint32_t>(PinMode::INPUT));
	LL_GPIO_SetPinPull(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number)), static_cast<uint32_t>(pull));
}

bool DigitalIn::read() {
	return static_cast<bool>(LL_GPIO_IsInputPinSet(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number))));
}