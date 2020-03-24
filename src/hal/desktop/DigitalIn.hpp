#pragma once
#include "DigitalIn.hpp"
#include "DigitalInBase.hpp"
#include "GPIO.hpp"

class DigitalIn: public DigitalInBase, public GPIO {
	public:
	DigitalIn(const Port port, const Pin pin, const Pull pull);
	bool read() final override;
	void set(const bool);
};