#include <cstddef>
#include "Pin.hpp"

bool pin_states[static_cast<std::size_t>(Port::NUM_PORTS)][static_cast<std::size_t>(Pin::NUM_PINS)] = {};