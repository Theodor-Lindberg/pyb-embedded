#pragma once
#include "GPIO.hpp"

class DigitalOut: public GPIO {
    public:
    DigitalOut(const int pin);
    void write(const bool state);
    void toggle();
};