#include "ModbusRequest.hpp"
#include "ModbusRegisters.hpp"
#include "BoardLEDs.hpp"

/**
 * @brief Handle the 'Read Coil Status' Request
 * 
 * @param package 
 * @return ModbusException 
 */
ModbusException handle_fc01(uint8_t *package, unsigned& length) {
	uint16_t coil = package[2] << 8 | package[3];
	uint16_t coils_to_read = package[4] << 8 | package[5];

	if (coil + coils_to_read >= static_cast<uint16_t>(OUTPUT_COIL::NUMBER_OF_COILS)) {
		return ModbusException::Illegal_Data_Address;
	}

	package[2] = (coils_to_read + 8 - 1) / 8; // Division with ceiling to get number of bytes required
	for (auto i = 0; i < package[2]; ++i) {
		package[3 + i] = 0;
	}
	bool status;

	for (uint16_t i =  0; i < coils_to_read; ++i) {
		read_single_coil(static_cast<INPUT_CONTACT>(coil + i), status);
		package[3 + i / 8] |= status << (i % 8);
	}
	length = 5 + package[2]; // addr + fc + number of bytes + actual data + crc
	return ModbusException::Acknowledge;
}

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
			board::get_board_led(board::LED::BLUE).write(status);
			return ModbusException::Acknowledge;
		case OUTPUT_COIL::GREEN_BOARD_LED:
			board::get_board_led(board::LED::GREEN).write(status);
			return ModbusException::Acknowledge;
		case OUTPUT_COIL::YELLOW_BOARD_LED:
			board::get_board_led(board::LED::YELLOW).write(status);
			return ModbusException::Acknowledge;
		case OUTPUT_COIL::RED_BOARD_LED:
			board::get_board_led(board::LED::RED).write(status);
			return ModbusException::Acknowledge;
		default:
			return ModbusException::Illegal_Data_Address;
	}
}

/**
 * @brief Read the status of a single coil.
 * 
 * @param coil The coil address.
 * @param status Set to true when coil coil is ON, otherwise false.
 * @return ModbusException 
 */
ModbusException read_single_coil(INPUT_CONTACT coil, bool& status) {
	switch(coil) {
		case INPUT_CONTACT::BLUE_BOARD_LED:
			status = board::get_board_led(board::LED::BLUE).is_set();
			return ModbusException::Acknowledge;
		case INPUT_CONTACT::GREEN_BOARD_LED:
			board::get_board_led(board::LED::GREEN).is_set();
			return ModbusException::Acknowledge;
		case INPUT_CONTACT::YELLOW_BOARD_LED:
			board::get_board_led(board::LED::YELLOW).is_set();
			return ModbusException::Acknowledge;
		case INPUT_CONTACT::RED_BOARD_LED:
			board::get_board_led(board::LED::RED).is_set();
			return ModbusException::Acknowledge;
		default:
			return ModbusException::Illegal_Data_Address;
	}
}