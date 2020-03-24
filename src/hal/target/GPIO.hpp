#pragma once
#include "GPIOBase.hpp"

class GPIO : public GPIOBase {
	protected:
	GPIO(Port port, Pin pin);
	struct GPIO_Def;
	GPIO_Def* GPIOx;
};