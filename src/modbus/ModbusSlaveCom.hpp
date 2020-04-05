#pragma once
#include "ModbusExceptions.hpp"

namespace ModbusComLayer {
	/**
	 * @brief Modbus Function Code
	 */
	enum class FC : uint8_t {
		FC01 = 0x1U,	// Read Coil Status
		FC02 = 0x2U,	// Read Input Status
		FC03 = 0x3U,	// Read Holding Registers
		FC04 = 0x4U,	// Read Input Registers
		FC05 = 0x5U,	// Force Single Coil
		FC06 = 0x6U,	// Preset Single Register
		FC15 = 0xFU,	// Force Multiple Coils
		FC16 = 0x10U	// Preset Multiple Registers
	};
	[[nodiscard]] unsigned generate_response(uint8_t* package, unsigned length, uint8_t mb_id);
	[[nodiscard]] uint16_t calculate_checksum(const uint8_t* package, unsigned length);
	void set_checksum(uint8_t* package, unsigned length);
	void set_exception(ModbusException ex, uint8_t* package);
	constexpr unsigned MIN_PACKAGE_SIZE = 7;
	constexpr uint8_t ID_IDX = 0U;
	constexpr uint8_t FC_IDX = 1U;
	constexpr uint8_t EX_IDX = 2U;
	constexpr uint8_t BROADCAST_ID = 0U;
}