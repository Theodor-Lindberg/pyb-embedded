#include "catch.hpp"
#include "ModbusSlaveCom.hpp"
#include <iostream>

TEST_CASE("Modbus RTU Slave Function Code 5", "[single-file]") {
	/**
	 * 11 05 00AC FF00 4E8B
	 * @brief This command is writing the contents of discrete coil # 173 to ON in the slave device with address 17.
	 * 11: The Slave Address (11 hex = address17 )
	 * 05: The Function Code 5 (Force Single Coil)
	 * 00AC: The Data Address of the coil. (coil# 173 - 1 = 172 = AC hex). ( 00AC hex = 172 , + 1 offset = coil #173 )
	 * FF00: The status to write ( FF00 = ON,  0000 = OFF )
	 * 4E8B: The CRC (cyclic redundancy check) for error checking.
	 */
	uint8_t data[] = {0x11, 0x05, 0x00, 0xAC, 0xFF, 0x00, 0x4E, 0x8B};
	unsigned length = sizeof(data)/sizeof(uint8_t);

}