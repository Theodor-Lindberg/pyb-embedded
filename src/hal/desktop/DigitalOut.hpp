#pragma once
#include "GPIO.hpp"
#include "DigitalOutBase.hpp"

class DigitalOut: public DigitalOutBase, public GPIO {
	public:
	DigitalOut(const Port port, const Pin pin);
	DigitalOut(const Port port, const Pin pin, const Speed speed, const OutputType type);
	void write(const bool state) final override;
	void toggle() final override;
	bool is_set() final override;
};