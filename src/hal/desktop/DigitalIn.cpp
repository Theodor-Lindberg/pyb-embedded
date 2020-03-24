#include "DigitalIn.hpp"

DigitalIn::DigitalIn(const Port port, const Pin pin, const Pull pull): 
	GPIO(port, pin) {
	state = pull == Pull::UP;
}

bool DigitalIn::read() {
	return state;;
}

void DigitalIn::set(bool state) {
	this->state = state;
}