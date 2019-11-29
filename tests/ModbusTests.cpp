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
	uint8_t data[] = {0x11, 0x07, 0x00, 0xAC, 0xFF, 0x00, 0x37, 0x4B};
	unsigned length = sizeof(data)/sizeof(uint8_t);
	//uint8_t* response = ModbusComLayer::get_response(data, length, 0x11);
}

/**
 * @brief The slave should only respond to it's own ID and broadcasted packages.
 */
TEST_CASE("Modbus RTU Slave ID", "[single-file]") {
	constexpr uint8_t real_id = !ModbusComLayer::BROADCAST_ID;
	uint8_t package[] = {real_id, 0x05, 0x00, 0xAC, 0xFF, 0x00, 0x00, 0x00};

	for (uint8_t id = 0; id < 0xFF; ++id) {
		unsigned length = sizeof(package)/sizeof(uint8_t);
		package[ModbusComLayer::ID_IDX] = id;
		uint16_t crc = ModbusComLayer::calculate_checksum(package, length-2);
		package[length - 2] = crc >> 8;
		package[length - 1] = crc & 0xFF;
		uint8_t* response = ModbusComLayer::get_response(package, length, real_id);
		if ((id == ModbusComLayer::BROADCAST_ID) || (id == real_id)) {
			REQUIRE(response != nullptr);
		} else {
			REQUIRE(response == nullptr);
			REQUIRE(length == 0);
		}
		delete[] response;
	}
}