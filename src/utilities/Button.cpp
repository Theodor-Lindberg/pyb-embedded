#include "Button.hpp"

Button::Button(DigitalIn& input_pin, bool normal_low):
input_pin(&input_pin), normal_low(normal_low)
{
}

bool Button::is_pressed() {
	return input_pin->read() == normal_low;
}