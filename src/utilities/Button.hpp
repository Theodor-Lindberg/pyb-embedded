#pragma once
#include "DigitalIn.hpp"

class Button {
	public:
	Button() = delete;
	Button(DigitalIn& input_pin, bool normal_low);
	[[nodiscard]] bool is_pressed();
	private:
	DigitalIn* const input_pin;
	const bool normal_low;
};