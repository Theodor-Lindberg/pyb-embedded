#include "Pin.hpp"

bool pin_states[static_cast<size_t>(Port::NUM_PORTS)][static_cast<size_t>(Pin::NUM_PINS)] = {};