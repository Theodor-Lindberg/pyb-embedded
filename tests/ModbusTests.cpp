#include "catch.hpp"
#include "ModbusSlaveCom.hpp"
#include <algorithm>


/**
 * @brief Force Single Coil
 */
TEST_CASE("Modbus RTU Slave Function Code 5", "[single-file]") {
	/**
	 * 11 05 00AC FF00 DF6A
	 * @brief This command is writing the contents of boolean variable  # 1073 to ON to the slave device with address 17.
	 * 11: The Slave Address (11 hex = address17 )
	 * 05: The Function Code 5 (Force Single Coil)
	 * 0001: The Data Address of the coil. (coil# 2 - 1 = 1 = 0x01 hex).
	 * FF00: The status to write ( FF00 = ON,  0000 = OFF )
	 * DF6A: The CRC (cyclic redundancy check) for error checking.
	 */
	uint8_t expected[8] = {0x11, 0x05, 0x00, 0x01, 0xFF, 0x00, 0xDF, 0x6A};
	uint8_t buffer[8];
	std::copy(std::begin(expected), std::end(expected), std::begin(buffer));
	unsigned length = sizeof(buffer)/sizeof(uint8_t);
	unsigned buffer_size = ModbusComLayer::generate_response(buffer, length, buffer[ModbusComLayer::ID_IDX]);

	SECTION("Turn Coil ON") {
		REQUIRE(length == buffer_size);
		for (unsigned i = 0; i < buffer_size; ++i) {
			REQUIRE(buffer[i] == expected[i]);
		}	
	}

	SECTION("Turn Coil OFF") {
		expected[4] = 0x00; // Turn coil off
		uint16_t crc = ModbusComLayer::calculate_checksum(expected, length-2);
		expected[length - 2] = crc & 0x00FF; // Low byte first
		expected[length - 1] = crc >> 8;
		std::copy(std::begin(expected), std::end(expected), std::begin(buffer));
		buffer_size = ModbusComLayer::generate_response(buffer, length, buffer[ModbusComLayer::ID_IDX]);

		REQUIRE(buffer_size == length);
		for (unsigned i = 0; i < length; ++i) {
			REQUIRE(buffer[i] == expected[i]);
		}
	}

	SECTION("Illegal Data Address") {
		expected[2] = 4; // Illegal Data Address
		uint16_t crc = ModbusComLayer::calculate_checksum(expected, length-2);
		expected[length - 2] = crc & 0x00FF; // Low byte first
		expected[length - 1] = crc >> 8;
		std::copy(std::begin(expected), std::end(expected), std::begin(buffer));
		buffer_size = ModbusComLayer::generate_response(buffer, length, buffer[ModbusComLayer::ID_IDX]);

		REQUIRE(buffer_size == 5);
		for (unsigned i = 0; i < buffer_size - 2; ++i) {
			if (i == static_cast<uint8_t>(ModbusComLayer::EX_IDX)) {
				REQUIRE(buffer[i] == static_cast<uint8_t>(ModbusException::Illegal_Data_Address));
			} else if (i == ModbusComLayer::FC_IDX) {
				REQUIRE(buffer[i] == (0x80 | expected[i]));
			} else {
				REQUIRE(buffer[i] == expected[i]);
			}
		}
	}
	
	SECTION("Illegal Data Value") {
		expected[4] = 4; // Illegal Data Value
		uint16_t crc = ModbusComLayer::calculate_checksum(expected, length-2);
		expected[length - 2] = crc & 0x00FF; // Low byte first
		expected[length - 1] = crc >> 8;
		std::copy(std::begin(expected), std::end(expected), std::begin(buffer));
		buffer_size = ModbusComLayer::generate_response(buffer, length, buffer[ModbusComLayer::ID_IDX]);

		REQUIRE(buffer_size == 5);
		for (unsigned i = 0; i < buffer_size - 2; ++i) {
			if (i == ModbusComLayer::EX_IDX) {
				REQUIRE(buffer[i] == static_cast<uint8_t>(ModbusException::Illegal_Data_Value));
			} else if (i == static_cast<uint8_t>(ModbusComLayer::FC_IDX)) {
				REQUIRE(buffer[i] == (0x80 | expected[i]));
			} else {
				REQUIRE(buffer[i] == expected[i]);
			}
		}
	}
}

/**
 * @brief The slave should only respond to it's own ID and broadcasted packages.
 */
TEST_CASE("Modbus RTU Slave ID", "[single-file]") {
	constexpr uint8_t real_id = !ModbusComLayer::BROADCAST_ID;
	uint8_t package[8] = {0x00, 0x05, 0x04, 0x01, 0x04, 0x00, 0x00, 0x00};
	uint8_t buffer[8];

	for (uint8_t id = 0; id < 0xFF; ++id) {
		unsigned length = sizeof(package)/sizeof(uint8_t);
		package[ModbusComLayer::ID_IDX] = id;
		uint16_t crc = ModbusComLayer::calculate_checksum(package, length-2);
		package[length - 2] = crc & 0x00FF; // Low byte first
		package[length - 1] = crc >> 8;
		std::copy(std::begin(package), std::end(package), std::begin(buffer));
		unsigned buffer_size = ModbusComLayer::generate_response(buffer, length, real_id);
		if ((id == ModbusComLayer::BROADCAST_ID) || (id == real_id)) {
			REQUIRE(buffer_size != 0);
		} else {
			REQUIRE(buffer_size == 0);
		}
	}
}

/**
 * @brief Recognize an invalid checksum.
 */
TEST_CASE("Modbus RTU Invalid Checksum", "[single-file]") {
	uint8_t data[] = {0x11, 0x05, 0x00, 0x01, 0xFF, 0x00, 0xDF, 0xFB};
	REQUIRE(0 == ModbusComLayer::generate_response(data, sizeof(data), data[ModbusComLayer::ID_IDX]));
}