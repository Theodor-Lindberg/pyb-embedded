#pragma once
#include "ModbusExceptions.hpp"
#include "ModbusRegisters.hpp"

ModbusException handle_fc05(const uint8_t *package);
ModbusException force_single_coil(OUTPUT_COIL coil, bool status);