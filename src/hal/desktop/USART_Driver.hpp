#include <vector>
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
	void set_rx_buffer(const char* data_buffer, uint32_t length);
	void receive_tx(const std::vector<uint8_t>& data);
	private:
	IUsartHook* usart_it_hook;
	uint8_t rx_data;
};