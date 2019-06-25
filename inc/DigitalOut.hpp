#pragma once
#include "stm32f4xx.h"

class DigitalOut {
    private:
    GPIO_TypeDef* const GPIOx;
    const uint32_t pin;
    public:
    DigitalOut(GPIO_TypeDef* const GPIOx, const uint32_t pin, const uint32_t speed, const uint32_t pull);
    void high();
    void low();
    void toggle();
    static void setHigh(GPIO_TypeDef* const GPIOx, const uint32_t pin_msk);
    static void setLow(GPIO_TypeDef* const GPIOx, const uint32_t pin_msk);
};