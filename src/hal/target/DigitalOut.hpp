#pragma once
#include "GPIO.hpp"

class DigitalOut: public GPIO {
    public:
    DigitalOut(GPIO_TypeDef* const GPIOx, const uint32_t pin, const uint32_t speed, const uint32_t pull);
    void write(const bool state);
    void toggle();
};