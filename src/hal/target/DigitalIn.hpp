#pragma once
#include "GPIO.hpp"

class DigitalIn: public GPIO {
	public:
	DigitalIn(Port port, const Pin pin, const Pull pull);
	bool read();
};