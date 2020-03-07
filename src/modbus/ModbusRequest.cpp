#include "ModbusRequest.hpp"
#include "ModbusRegisters.hpp"

/**
 * @brief Handle the 'Force single Coil' Request
 * 
 * @param package 
 * @return ModbusException 
 */
ModbusException handle_fc05(const uint8_t *package) {
	uint16_t coil = package[2] << 8 | package[3];
	uint16_t tmp_status = package[4] << 8 | package[5];
	bool status;
	if (tmp_status == 0x0000) {
		status = false;
	} else if (tmp_status == 0xFF00) {
		status = true;
	} else {
		return ModbusException::Illegal_Data_Value;
	}

	if (coil >= static_cast<uint16_t>(OUTPUT_COIL::NUMBER_OF_COILS)) {
		return ModbusException::Illegal_Data_Address;
	}

	return force_single_coil(static_cast<OUTPUT_COIL>(coil), status);
}

/**
 * @brief Force a single coil to either ON or OFF.
 * 
 * @param coil The coil address.
 * @param status When true the coil will be set to ON, otherwise OFF.
 * @return ModbusException 
 */
ModbusException force_single_coil(OUTPUT_COIL coil, bool status) {
	switch(coil) {
		case OUTPUT_COIL::BLUE_BOARD_LED:
			return ModbusException::Acknowledge;
		case OUTPUT_COIL::GREEN_BOARD_LED:
			return ModbusException::Acknowledge;
		case OUTPUT_COIL::YELLOW_BOARD_LED:
			return ModbusException::Acknowledge;
		case OUTPUT_COIL::RED_BOARD_LED:
			return ModbusException::Acknowledge;
		default:
			return ModbusException::Illegal_Data_Address;
	}
}