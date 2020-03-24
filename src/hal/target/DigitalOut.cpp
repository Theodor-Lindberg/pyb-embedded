#include "DigitalOut.hpp"
#include "stm32f4xx_ll_gpio.h"

DigitalOut::DigitalOut(const Port port, const Pin pin, const Speed speed, const OutputType type): GPIO(port, pin) {
	LL_GPIO_SetPinMode(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin)), LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin)), static_cast<uint32_t>(type));
	LL_GPIO_SetPinSpeed(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin)), static_cast<uint32_t>(speed));
}

void DigitalOut::write(const bool state) {
	if (state) {
		LL_GPIO_SetOutputPin(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin)));
	}
	else {
		LL_GPIO_ResetOutputPin(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin)));
	}
}

void DigitalOut::toggle() {
	LL_GPIO_TogglePin(reinterpret_cast<GPIO_TypeDef*>(GPIOx), static_cast<uint32_t>(1 << static_cast<uint32_t>(pin)));
}