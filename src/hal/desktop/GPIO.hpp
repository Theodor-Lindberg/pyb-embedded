#pragma once
#include "GPIOBase.hpp"

class GPIO : GPIOBase {
	protected:
	GPIO(const Port port, const Pin pin);
	bool state = false;
	const Port port;
};