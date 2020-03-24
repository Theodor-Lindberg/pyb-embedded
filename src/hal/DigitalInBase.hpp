#pragma once
#include "Pin.hpp"

class DigitalInBase {
	public:
	virtual bool read() = 0;
};