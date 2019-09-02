#include "mb_slave.hpp"
#include "Timer.hpp"
#include <limits>

ModbusSlave::ModbusSlave(SerialDriver* const serial_driver, uint8_t id, BAUDRATE baudrate, STOPBITS stop_bits, PARITY parity) :
serial_driver(serial_driver), mb_id(id) {
	timer.set_interval(calculate_end_frame(baudrate));
	serial_driver->initialize(baudrate, DIRECTION::RX_TX, DATAWIDTH::B8, stop_bits, parity, HWCONTROL::NONE, OVERSAMPLING::B16, this);
}

void ModbusSlave::open() {
	serial_driver->open();
	receive_index = 0U;
}

void ModbusSlave::close() {
	timer.stop();
	serial_driver->close();
}

ModbusSlave::ModbusSlave(SerialDriver* const serial_driver) : serial_driver(serial_driver) {

}

void ModbusSlave::rx_it_hook() {
	uint8_t received_byte = serial_driver->read();
	recieve_buffer[receive_index++] = received_byte;
	timer.reset();
	timer.start();
}

void ModbusSlave::timer_it_hook() {
	timer.stop();
	process_packet();
	receive_index = 0U;
}

void ModbusSlave::process_packet() {
	if (is_package_valid() == false) { // Ignore packages with incorrect id or incorrect checksum
		receive_index = 0U;
		return;
	}

	switch (recieve_buffer[FC_IDX]) {
		case static_cast<uint8_t>(FC::FC01):
			break;
		case static_cast<uint8_t>(FC::FC02):
			break;
		case static_cast<uint8_t>(FC::FC03):
			break;
		case static_cast<uint8_t>(FC::FC04):
			break;
		case static_cast<uint8_t>(FC::FC05):
			break;
		case static_cast<uint8_t>(FC::FC06):
			break;
		case static_cast<uint8_t>(FC::FC15):
			break;
		case static_cast<uint8_t>(FC::FC16):
			break;
		default:
			// Exception::Illegal_Function
			break;
	}

	serial_driver->send_async(response_buffer, 0U, response_length);
}

uint16_t ModbusSlave::calculate_crc(const uint8_t* const buffer, uint32_t count) const {
	return 0;
}

uint32_t ModbusSlave::calculate_end_frame(BAUDRATE baudrate) const {
	return 0;
}

/**
 * @brief Check if the package in the receive buffer is correct.
 * 
 * @return true If the modbus id and checksum are correct.
 * @return false If either the modbus id or checksum are incorrect.
 */
bool ModbusSlave::is_package_valid() const {
	if (mb_id != recieve_buffer[ID_IDX]) {
		return false;
	}

	if (receive_index <= 7U) { // 7 bytes is the smallest valid package
		return false;
	}

	const uint16_t received_crc = static_cast<uint16_t>((recieve_buffer[receive_index - 2U] << __CHAR_BIT__) | (recieve_buffer[receive_index - 1U]));
	const uint16_t calculated_crc = calculate_crc(recieve_buffer, receive_index);
	return (received_crc == calculated_crc);
}

ModbusSlave::Exception ModbusSlave::handle_fc1() {
	return Exception::Acknowledge;
}