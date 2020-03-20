#pragma once
#include "GPIO.hpp"

class DigitalOut: public GPIO {
	public:
	DigitalOut(Port port, Pin pin, Speed speed, Pull pull);
	void write(bool state);
	void toggle();
};