#include "DigitalIn.hpp"

DigitalIn::DigitalIn(const Port port, const Pin pin, const Pull pull): 
	GPIO(port, pin) {
	pin_states[static_cast<uint32_t>(port)][static_cast<uint32_t>(pin)] = pull == Pull::UP;
}

bool DigitalIn::read() {
	return pin_states[static_cast<uint32_t>(port)][static_cast<uint32_t>(pin)];
}

void DigitalIn::set(bool state) {
	pin_states[static_cast<uint32_t>(port)][static_cast<uint32_t>(pin)] = state;
}