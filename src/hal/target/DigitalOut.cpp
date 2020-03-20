#include "DigitalOut.hpp"
#include "stm32f4xx_ll_gpio.h"

DigitalOut::DigitalOut(Port port, Pin pin, Speed speed, Pull pull): GPIO(port, pin) {
	LL_GPIO_SetPinMode(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number)), LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinPull(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number)), static_cast<uint32_t>(pull));
	LL_GPIO_SetPinSpeed(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number)), static_cast<uint32_t>(speed));
}

void DigitalOut::write(const bool state) {
	if (state) {
		LL_GPIO_SetOutputPin(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number)));
	}
	else {
		LL_GPIO_ResetOutputPin(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number)));
	}
}

void DigitalOut::toggle() {
	LL_GPIO_TogglePin(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin_number)));
}