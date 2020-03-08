#include "BoardLEDs.hpp"
#include "stm32f4xx_ll_gpio.h"

GPIO_DEF_DECLARATION

DigitalOut& board::get_board_led(const LED led) {
	switch(led) {
		case LED::BLUE:
			static DigitalOut blue_led(static_cast<GPIO_Def*>(GPIOB), LL_GPIO_PIN_4, Speed::LOW, Pull::UP);
			return blue_led;
		case LED::GREEN:
			static DigitalOut green_led(static_cast<GPIO_Def*>(GPIOA), LL_GPIO_PIN_14, Speed::LOW, Pull::UP);
			return green_led;
		case LED::YELLOW:
			static DigitalOut yellow_led(static_cast<GPIO_Def*>(GPIOA), LL_GPIO_PIN_15, Speed::LOW, Pull::UP);
			return yellow_led;
		case LED::RED:
			static DigitalOut red_led(static_cast<GPIO_Def*>(GPIOA), LL_GPIO_PIN_13, Speed::LOW, Pull::UP);
			return red_led;
	}
}