#pragma once
#include "GPIOBase.hpp"

extern bool pin_states[][static_cast<size_t>(Pin::NUM_PINS)];

class GPIO : public GPIOBase {
	protected:
	GPIO(const Port port, const Pin pin);
	const Port port;
};