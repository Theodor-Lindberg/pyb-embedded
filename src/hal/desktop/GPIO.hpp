#pragma once
#include "Pin.hpp"

class GPIO {
	public:
	GPIO() = delete;
	protected:
	GPIO(const Pin pin) :pin(pin) { state = false; };
	bool state;
	private:
	const Pin pin;
};