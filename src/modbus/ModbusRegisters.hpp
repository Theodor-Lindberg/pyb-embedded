#pragma once
#include <stdint.h>

/**
 * @brief Discrete Output Coil
 */
enum class OUTPUT_COIL : uint16_t {
	BLUE_BOARD_LED,
	GREEN_BOARD_LED,
	YELLOW_BOARD_LED,
	RED_BOARD_LED,
	NUMBER_OF_COILS			// The number of discrete output coils
};

/**
 * @brief Discrete Input Contact
 */
enum class INPUT_CONTACT : uint16_t {
	NUMBER_OF_CONTACTS		// The number of discrete input contacts
};

/**
 * @brief Analog Output Holding Register
 */
enum class OUTPUT_REGISTER : uint16_t {
	NUMBER_OF_REGISTERS		// The number of analog output holding registers
};

/**
 * @brief Analog Input Register
 */
enum class INPUT_REGISTER : uint16_t {
	MAJOR_VERSION = 0x0U,	// Major version number of the firmware version
	MINOR_VERSION = 0x1U,	// Minor version number of the firmware version
	PATCH_VERSION = 0x2U,	// Patch version number of the firmware version
	NUMBER_OF_REGISTERS		// The number of analog input registers
};