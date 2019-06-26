#include "BoardLEDs.hpp"
#include "stm32f4xx_ll_gpio.h"

DigitalOut& Board::get_board_led(const LED led) {
    switch(led) {
        case LED::BLUE:
            static DigitalOut blue_led(GPIOB, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_PULL_UP);
            return blue_led;
        case LED::GREEN:
            static DigitalOut green_led(GPIOA, LL_GPIO_PIN_14, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_PULL_UP);
            return green_led;
        case LED::YELLOW:
            static DigitalOut yellow_led(GPIOA, LL_GPIO_PIN_15, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_PULL_UP);
            return yellow_led;
        case LED::RED:
            static DigitalOut red_led(GPIOA, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_PULL_UP);
            return red_led;
    }
}