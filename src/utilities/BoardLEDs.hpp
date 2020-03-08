#pragma once
#include "DigitalOut.hpp"

namespace board {
	enum class LED {
		BLUE, GREEN, YELLOW, RED
		};

	DigitalOut& get_board_led(const LED led);
}