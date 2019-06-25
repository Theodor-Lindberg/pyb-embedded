#include "DigitalOut.hpp"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"

DigitalOut::DigitalOut(GPIO_TypeDef* const GPIOx, const uint32_t pin, const uint32_t speed, const uint32_t pull) :
GPIOx(GPIOx), pin(pin) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinPull(GPIOx, pin, pull);
    LL_GPIO_SetPinSpeed(GPIOx, pin, speed);
}

void DigitalOut::high() {
    LL_GPIO_SetOutputPin(GPIOx, pin);
}

void DigitalOut::low() {
    LL_GPIO_ResetOutputPin(GPIOx, pin);
}

void DigitalOut::toggle() {
    LL_GPIO_TogglePin(GPIOx, pin);
}