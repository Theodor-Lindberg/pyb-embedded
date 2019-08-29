#pragma once
#include "USART_Driver.hpp"
#include "IUsartHook.hpp"
#include <vector>

class ModbusSlave : IUsartHook {
	public:
	ModbusSlave(SerialDriver& serial_driver, uint8_t ID, BAUDRATE baudrate, STOPBITS stop_bits, PARITY parity);
	void open();
	void close();
	virtual void rx_it_hook();
	std::vector<uint8_t> v;
	private:
	SerialDriver& serial_driver;
	uint8_t mb_id;
	bool receiving_package;
	uint8_t receive_index;
	uint8_t recieve_buffer[];
};