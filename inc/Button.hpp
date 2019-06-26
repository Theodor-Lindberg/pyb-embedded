#pragma once
#include "DigitalIn.hpp"

class Button {
    private:
    DigitalIn input_pin;
    const bool normal_low;
    public:
    Button() = delete;
    Button(const DigitalIn input_pin, const bool normal_low);
    bool is_pressed();
};