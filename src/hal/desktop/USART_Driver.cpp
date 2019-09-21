#include "USART_Driver.hpp"

class IUsartHook {
	public:
	virtual ~IUsartHook() {}
	virtual void rx_it_hook() = 0;
};

void SerialDriver::receive_tx(const std::vector<uint8_t>& data) {
	for (auto v : data) {
		rx_data = v;
		usart_it_hook->rx_it_hook();
	}
}