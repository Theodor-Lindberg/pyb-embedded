#pragma once
#include "GPIO.hpp"

class DigitalIn: public GPIO {
	public:
	DigitalIn(const int pin);
	bool read();
	void set(bool);
};