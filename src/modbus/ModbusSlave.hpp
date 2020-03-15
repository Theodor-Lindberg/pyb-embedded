#pragma once
#include "USART_Driver.hpp"
#include "Timer.hpp"
#include "IUsartHook.hpp"
#include "ITimerHook.hpp"

class ModbusSlave : IUsartHook, ITimerHook {
	public:
	ModbusSlave(SerialDriver* const serial_driver, TIMER tim);
	ModbusSlave(SerialDriver* const serial_driver, TIMER tim, uint8_t ID, BAUDRATE baudrate, STOPBITS stop_bits, PARITY parity);
	void open();
	void close();
	void set_id(uint8_t ID);
	void process_packet();
	virtual void rx_it_hook();
	virtual void timer_it_hook();
	private:
	SerialDriver* const serial_driver;
	Timer timer;
	uint8_t mb_id;
	uint8_t receive_index;
	uint8_t recieve_buffer[9];
	uint32_t response_length;
	uint8_t* response_buffer;
	uint32_t calculate_end_frame(BAUDRATE baudrate) const;
};