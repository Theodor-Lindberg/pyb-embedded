#pragma once
#include "DigitalOut.hpp"

namespace Board {
    DigitalOut& get_blue_led();

    DigitalOut& get_green_led();

    DigitalOut& get_yellow_led();

    DigitalOut& get_red_led();
}