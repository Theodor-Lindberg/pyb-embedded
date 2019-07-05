#include "BoardButton.hpp"
#include "DigitalIn.hpp"
#include "stm32f4xx_ll_gpio.h"

Button& Board::get_board_button() {
    static DigitalIn input_pin(Pin(GPIOB, LL_GPIO_PIN_3, PinMode::INPUT, Pull::UP, Speed::LOW));
    static Button user_button(input_pin, false);
    return user_button;
}