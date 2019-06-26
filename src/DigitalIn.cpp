#include "DigitalIn.hpp"
#include "stm32f4xx_ll_gpio.h"

DigitalIn::DigitalIn(GPIO_TypeDef* const GPIOx, const uint32_t pin, const uint32_t pull):
GPIO(GPIOx, pin) {
    LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(GPIOx, pin, pull);
}

bool DigitalIn::read() {
    return static_cast<bool>(LL_GPIO_IsInputPinSet(GPIOx, pin));
}