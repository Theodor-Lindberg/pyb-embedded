#include "DigitalOut.hpp"

DigitalOut::DigitalOut(const int pin):
GPIO(Pin(pin, PinMode::OUTPUT)) {
}

void DigitalOut::write(const bool state) {
    this->state = state;
}

void DigitalOut::toggle() {
    state ^= true;
}