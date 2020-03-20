#pragma once
#include "Pin.hpp"

class GPIO {
	protected:
	GPIO(Port port, Pin pin);
	struct GPIO_Def;
	GPIO_Def* GPIOx;
	Pin pin_number;
	public:
	GPIO() = delete;
};