#include "BoardLEDs.hpp"
#include "stm32f4xx_ll_gpio.h"

DigitalOut& Board::get_blue_led() {
    static DigitalOut led(GPIOB, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_PULL_UP);
    return led;
}

DigitalOut& Board::get_green_led() {
    static DigitalOut led(GPIOA, LL_GPIO_PIN_14, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_PULL_UP);
    return led;
}

DigitalOut& Board::get_yellow_led() {
    static DigitalOut led(GPIOA, LL_GPIO_PIN_15, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_PULL_UP);
    return led;
}

DigitalOut& Board::get_red_led() {
    static DigitalOut led(GPIOA, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_PULL_UP);
    return led;
}