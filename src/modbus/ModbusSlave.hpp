#pragma once
#include "UsartDriver.hpp"
#include "Timer.hpp"
#include "IUsartHook.hpp"
#include "ITimerHook.hpp"

class ModbusSlave : public IUsartHook, public ITimerHook {
	public:
	ModbusSlave(SerialDriver* const serial_driver, TIMER tim);
	ModbusSlave(SerialDriver* const serial_driver, TIMER tim, uint8_t ID, BAUDRATE baudrate, STOPBITS stop_bits, PARITY parity);
	void open();
	void close();
	void set_id(uint8_t ID);
	void process_packet();
	void rx_it_hook() override;
	void timer_it_hook() override;
	private:
	SerialDriver* const serial_driver;
	Timer timer;
	uint8_t mb_id;
	uint8_t receive_index = 0;
	uint8_t buffer[9];
	uint32_t calculate_end_frame(BAUDRATE baudrate) const;
};