#pragma once
#include <stdint.h>
#include "USART.hpp"

class IUsartHook;
class vector;

class SerialDriver {
	public:
	SerialDriver(const SerialDriver&) = delete;
	SerialDriver& operator=(const SerialDriver&) = delete;
	static SerialDriver* get_instance(DRIVER_PORT driver_port);
	bool initialize(BAUDRATE baudrate, DIRECTION direction, DATAWIDTH datawidth, STOPBITS stopbits, PARITY parity, HWCONTROL hw_control, OVERSAMPLING over_sampling, IUsartHook* const usart_it_hook);
	bool de_init();
	void open();
	void close();
	void write(uint8_t byte);
	bool send(const uint8_t* data, uint32_t start, uint32_t end);
	bool send_async(const uint8_t* data, uint32_t start, uint32_t end);
	bool print(const uint8_t* str);
	uint8_t read();
	bool is_sending_async();
	bool set_baudrate(BAUDRATE baudrate);
	void rx_callback();
	void tc_it();
	private:
	struct USART_Def;
	USART_Def* const USARTx;
	IUsartHook* usart_it_hook;
	volatile const uint8_t* message_to_send;
	volatile const uint8_t* message_last_index;
	SerialDriver(USART_Def* const USARTx);
	void wait_ready_to_send();
};