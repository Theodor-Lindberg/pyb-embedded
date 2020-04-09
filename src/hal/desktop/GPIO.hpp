#pragma once
#include <cstddef>
#include "GPIOBase.hpp"

extern bool pin_states[][static_cast<std::size_t>(Pin::NUM_PINS)];

class GPIO : public GPIOBase {
	protected:
	GPIO(const Port port, const Pin pin);
	const Port port;
};