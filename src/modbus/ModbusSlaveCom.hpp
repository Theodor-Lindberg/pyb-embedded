#pragma once
#include <stdint.h>

class ModbusComLayer {
	public:
	ModbusComLayer() = default;
	static uint8_t* get_response(const uint8_t* package, unsigned& length, uint8_t mb_id);
	static constexpr unsigned MAX_PACKAGE_SIZE = 10;
	/**
	 * @brief Modbus Exception Code
	 */
	enum class Exception : uint8_t {
		None = 0x0U,
		Illegal_Function = 0x1U,
		Illegal_Data_Address = 0x2U,
		Illegal_Data_Value = 0x3U,
		Slave_Device_Failure = 0x4U,
		Acknowledge = 0x5U,
		Slave_Device_Busy = 0x6U,
		Negative_Acknowledge = 0x7U,
		Memory_Parity_Error = 0x8U,
		Gateway_Path_Unavailable = 0xAU,
		Gateway_Target_Device_Failed_To_Respond = 0xBU,
		Indicator_Mask = 0x80U	// Used to mask the function code in response
	};

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
	static uint16_t calculate_checksum(const uint8_t* package, unsigned length);
	static uint8_t* send_exception(Exception ex, uint8_t fc, const uint8_t* package, uint8_t id);
	static constexpr unsigned MIN_PACKAGE_SIZE = 7;
	static constexpr uint8_t ID_IDX = 0U;
	static constexpr uint8_t FC_IDX = 1U;
	static constexpr uint8_t EX_IDX = 2U;
	static constexpr uint8_t BROADCAST_ID = 0U;
};