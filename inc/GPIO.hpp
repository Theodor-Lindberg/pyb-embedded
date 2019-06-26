#pragma once
#include "stm32f4xx.h"

class GPIO {
    protected:
    GPIO(GPIO_TypeDef* const GPIOx, const uint32_t pin) : GPIOx(GPIOx), pin(pin) {};
    GPIO_TypeDef* const GPIOx;
    const uint32_t pin;
    public:
    GPIO() = delete;
};