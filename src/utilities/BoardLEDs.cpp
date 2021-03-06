#include "BoardLEDs.hpp"

DigitalOut& board::get_board_led(const LED led) {
	switch(led) {
		case LED::BLUE:
			{
				static DigitalOut blue_led(Port::B, Pin::PIN4, Speed::LOW, OutputType::PUSH_PULL);
				return blue_led;
			}
		case LED::GREEN:
			{								
				static DigitalOut green_led(Port::A, Pin::PIN14, Speed::LOW, OutputType::PUSH_PULL);
				return green_led;
			}
		case LED::YELLOW:
			{
				static DigitalOut yellow_led(Port::A, Pin::PIN15, Speed::LOW, OutputType::PUSH_PULL);
				return yellow_led;
			}
		case LED::RED:
			{
				static DigitalOut red_led(Port::A, Pin::PIN13, Speed::LOW, OutputType::PUSH_PULL);
				return red_led;
			}
	}
}