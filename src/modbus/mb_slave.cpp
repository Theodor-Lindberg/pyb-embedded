#include "mb_slave.hpp"
#include "SEGGER_RTT.h"

ModbusSlave::ModbusSlave(SerialDriver& serial_driver, uint8_t id, BAUDRATE baudrate, STOPBITS stop_bits, PARITY parity) :
serial_driver(serial_driver), mb_id(id) {
	serial_driver.initialize(baudrate, DIRECTION::RX_TX, DATAWIDTH::B8, stop_bits, parity, HWCONTROL::NONE, OVERSAMPLING::B16, this);
}

void ModbusSlave::open() {
	receiving_package = true;
	receive_index = 0U;
	serial_driver.open();
}

void ModbusSlave::close() {
	serial_driver.close();
}

void ModbusSlave::rx_it_hook() {
	uint8_t received_byte = serial_driver.read();
	recieve_buffer[receive_index++] = received_byte;
}