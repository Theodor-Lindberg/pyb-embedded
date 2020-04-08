#include "DigitalOut.hpp"

DigitalOut::DigitalOut(const Port port, const Pin pin):	GPIO(port, pin) { }

DigitalOut::DigitalOut(const Port port, const Pin pin, const Speed speed, const OutputType type):
	GPIO(port, pin) { }

void DigitalOut::write(const bool state) {
	pin_states[static_cast<uint32_t>(port)][static_cast<uint32_t>(pin)] = state;
}

void DigitalOut::toggle() {
	pin_states[static_cast<uint32_t>(port)][static_cast<uint32_t>(pin)] ^= true;
}

bool DigitalOut::is_set() {
	return pin_states[static_cast<uint32_t>(port)][static_cast<uint32_t>(pin)];
}