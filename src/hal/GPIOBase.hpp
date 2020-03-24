#pragma once
#include "Pin.hpp"

class GPIOBase {
	protected:
	GPIOBase(const Pin pin);
	const Pin pin;
	public:
	GPIOBase() = delete;
};