#pragma once
#include "ModbusExceptions.hpp"

class ModbusComLayer {
	public:
	ModbusComLayer() = default;
	[[nodiscard]] static uint8_t* get_response(const uint8_t* package, unsigned& length, uint8_t mb_id);
	[[nodiscard]] static uint16_t calculate_checksum(const uint8_t* package, unsigned length);
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
	[[nodiscard]] static uint8_t* send_exception(ModbusException ex, uint8_t fc, uint8_t id);
	static constexpr unsigned MIN_PACKAGE_SIZE = 7;
	static constexpr uint8_t ID_IDX = 0U;
	static constexpr uint8_t FC_IDX = 1U;
	static constexpr uint8_t EX_IDX = 2U;
	static constexpr uint8_t BROADCAST_ID = 0U;
};