#pragma once
#include <stdint.h>
#include "USART.hpp"

class IUsartHook;
class vector;

class SerialDriverBase {
	public:
	virtual ~SerialDriverBase() = default;
	virtual bool initialize(BAUDRATE baudrate, DIRECTION direction, DATAWIDTH datawidth, STOPBITS stopbits, PARITY parity, HWCONTROL hw_control, OVERSAMPLING over_sampling, IUsartHook* const usart_it_hook);
	virtual bool de_init();
	virtual void open();
	virtual void close();
	virtual void write(uint8_t byte);
	virtual bool send(const uint8_t* data, uint32_t start, uint32_t end);
	virtual bool send_async(const uint8_t* data, uint32_t start, uint32_t end);
	virtual bool print(const uint8_t* str);
	virtual uint8_t read();
};