#pragma once
#include "Pin.hpp"

class GPIOBase {
	protected:
	explicit GPIOBase(const Pin pin);
	const Pin pin;
	public:
	GPIOBase() = delete;
	virtual ~GPIOBase() = default;
};