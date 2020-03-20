#include "BoardButton.hpp"
#include "DigitalIn.hpp"

Button& board::get_board_button() {
	static DigitalIn input_pin(Port::B, Pin::PIN3, Pull::UP);
	static Button user_button(input_pin, false);
	return user_button;
}