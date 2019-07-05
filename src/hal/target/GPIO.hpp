#pragma once
#include "Pin.hpp"

class GPIO {
    protected:
    GPIO(GPIO_TypeDef* const GPIOx, const uint32_t pin) : GPIOx(GPIOx), pin(pin) {};
    GPIO_TypeDef* const GPIOx;
    const uint32_t pin;
    public:
    GPIO() = delete;
};