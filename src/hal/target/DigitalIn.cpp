#include "DigitalIn.hpp"
#include "stm32f4xx_ll_gpio.h"

DigitalIn::DigitalIn(const Pin pin):
GPIO(pin.GPIOx, pin.number) {
    LL_GPIO_SetPinMode(GPIOx, pin.number, PinMode::INPUT);
    LL_GPIO_SetPinPull(GPIOx, pin.number, pin.pull);
}

bool DigitalIn::read() {
    return static_cast<bool>(LL_GPIO_IsInputPinSet(GPIOx, pin));
}