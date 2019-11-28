#pragma once
#include "Pin.hpp"

class GPIO {
	protected:
	GPIO(GPIO_Def* const GPIOx, const uint32_t pin_number) : GPIOx(GPIOx), pin_number(pin_number) {};
	GPIO_Def* const GPIOx;
	const uint32_t pin_number;
	public:
	GPIO() = delete;
};