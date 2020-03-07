#pragma once
#include <stdint.h>

/**
 * @brief Modbus Exception Code
 */
enum class ModbusException : uint8_t {
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