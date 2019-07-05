#pragma once
#include "GPIO.hpp"

class DigitalIn: public GPIO {
    public:
    DigitalIn(const Pin pin);
    bool read();
};