#include "ModbusSlave.hpp"
#include "Timer.hpp"
#include "ModbusSlaveCom.hpp"

ModbusSlave::ModbusSlave(SerialDriver* const serial_driver, TIMER tim, uint8_t id, BAUDRATE baudrate, STOPBITS stop_bits, PARITY parity) :
serial_driver(serial_driver), timer(Timer(tim, this)), mb_id(id), receive_index(0U) {
	timer.set_interval(calculate_end_frame(baudrate));
	serial_driver->initialize(baudrate, DIRECTION::RX_TX, DATAWIDTH::B8, stop_bits, parity, HWCONTROL::NONE, OVERSAMPLING::B16, this);
}

ModbusSlave::ModbusSlave(SerialDriver* const serial_driver, TIMER tim) :
	serial_driver(serial_driver), timer(Timer(tim, this)), receive_index(0U) {

}

void ModbusSlave::open() {
	serial_driver->open();
	receive_index = 0U;
}

void ModbusSlave::close() {
	timer.stop();
	serial_driver->close();
}

void ModbusSlave::set_id(uint8_t ID) {
	mb_id = ID;
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
	unsigned receive_length = receive_index;
	response_buffer = ModbusComLayer::get_response(recieve_buffer, receive_length, mb_id);
	serial_driver->send_async(response_buffer, 0U, response_length);
}

/**
 * @brief Calculate how long the end fram should be based on the chosen baudrate.
 * 
 * @param baudrate 
 * @return uint32_t The time frame in microseconds.
 */
uint32_t ModbusSlave::calculate_end_frame(BAUDRATE baudrate) const {
	return 0;
}