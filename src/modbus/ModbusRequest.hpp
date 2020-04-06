#pragma once
#include "ModbusExceptions.hpp"
#include "ModbusRegisters.hpp"

[[nodiscard]] ModbusException handle_fc01(uint8_t *package, unsigned& length);
[[nodiscard]] ModbusException handle_fc05(const uint8_t *package);
[[nodiscard]] ModbusException force_single_coil(OUTPUT_COIL coil, bool status);
[[nodiscard]] ModbusException read_single_coil(OUTPUT_COIL coil, bool& status);