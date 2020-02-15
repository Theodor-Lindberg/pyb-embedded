#pragma once
#include "GPIO.hpp"

class DigitalOut: public GPIO {
	public:
	DigitalOut(GPIO_Def* const GPIOx, const uint32_t pin, const Speed speed, const Pull pull);
	void write(const bool state);
	void toggle();
};