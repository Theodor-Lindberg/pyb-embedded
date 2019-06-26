#include "BoardButton.hpp"
#include "DigitalIn.hpp"
#include "stm32f4xx_ll_gpio.h"

Button& Board::get_board_button() {
    static DigitalIn input_pin(GPIOB, LL_GPIO_PIN_3, LL_GPIO_PULL_UP);
    static Button user_button(input_pin, false);
    return user_button;
}