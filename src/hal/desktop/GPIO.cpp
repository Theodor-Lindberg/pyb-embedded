#pragma once
#include "GPIO.hpp"

GPIO::GPIO(const Port port, const Pin pin) : GPIOBase(pin), port(port) { }