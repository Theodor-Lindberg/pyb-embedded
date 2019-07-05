#pragma once
#include "DigitalOut.hpp"

namespace Board {
    enum LED {
        BLUE, GREEN, YELLOW, RED
        };

    DigitalOut& get_board_led(const LED led);
}