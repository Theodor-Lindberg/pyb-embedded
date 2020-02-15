#pragma once
#include "GPIO.hpp"

class DigitalIn: public GPIO {
	public:
	DigitalIn(GPIO_Def* const GPIOx, const uint32_t pin, const Pull pull);
	bool read();
};