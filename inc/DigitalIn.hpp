#pragma once
#include "GPIO.hpp"

class DigitalIn: public GPIO {
    public:
    DigitalIn(GPIO_TypeDef* const GPIOx, const uint32_t pin, const uint32_t pull);
    bool read();
};