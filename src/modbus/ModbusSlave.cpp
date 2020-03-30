#include "ModbusSlave.hpp"
#include "Timer.hpp"
#include "ModbusSlaveCom.hpp"

ModbusSlave::ModbusSlave(SerialDriver* const serial_driver, TIMER tim, uint8_t id, BAUDRATE baudrate, STOPBITS stop_bits, PARITY parity) :
serial_driver(serial_driver), timer(Timer(tim, this)), mb_id(id) {
	timer.set_interval(calculate_end_frame(baudrate));
	serial_driver->initialize(baudrate, DIRECTION::RX_TX, DATAWIDTH::B8, stop_bits, parity, HWCONTROL::NONE, OVERSAMPLING::B16, this);
}

ModbusSlave::ModbusSlave(SerialDriver* const serial_driver, TIMER tim) :
	serial_driver(serial_driver), timer(Timer(tim, this)) {

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
	buffer[receive_index++] = serial_driver->read();
	if (receive_index == 8) {
		timer_it_hook();
	}
	timer.reset();
}

void ModbusSlave::timer_it_hook() {
	timer.stop();
	process_packet();
	receive_index = 0U;
}

void ModbusSlave::process_packet() {
	unsigned length = ModbusComLayer::generate_response(buffer, receive_index, mb_id);
	serial_driver->send_async(buffer, 0U, length);
	receive_index = 0;
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