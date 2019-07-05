#include "DigitalIn.hpp"

DigitalIn::DigitalIn(const int pin):
GPIO(Pin(pin, PinMode::INPUT)) {
}

bool DigitalIn::read() {
    return state;;
}

void DigitalIn::set(bool state) {
    this->state = state;
}