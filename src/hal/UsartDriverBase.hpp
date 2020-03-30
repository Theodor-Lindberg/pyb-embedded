#pragma once
#include <stdint.h>
#include "USART.hpp"

class IUsartHook;
class vector;

class SerialDriverBase {
	public:
	virtual ~SerialDriverBase() = default;
	virtual bool initialize(BAUDRATE baudrate, DIRECTION direction, DATAWIDTH datawidth, STOPBITS stopbits, PARITY parity, HWCONTROL hw_control, OVERSAMPLING over_sampling, IUsartHook* const usart_it_hook) = 0;
	virtual bool de_init() = 0;
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void write(uint8_t byte) = 0;
	virtual bool send(const uint8_t* data, uint32_t start, uint32_t end) = 0;
	virtual bool send_async(const uint8_t* data, uint32_t start, uint32_t end) = 0;
	virtual bool print(const uint8_t* str) = 0;
	virtual uint8_t read() = 0;
};