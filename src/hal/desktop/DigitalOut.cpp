#include "DigitalOut.hpp"

DigitalOut::DigitalOut(const Port port, const Pin pin):	GPIO(port, pin) { }

DigitalOut::DigitalOut(const Port port, const Pin pin, const Speed speed, const OutputType type):
	GPIO(port, pin) { }

void DigitalOut::write(const bool state) {
	this->state = state;
}

void DigitalOut::toggle() {
	state ^= true;
}

bool DigitalOut::is_set() {
	return state;
}