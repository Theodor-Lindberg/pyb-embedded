#include <vector>
#include <stdint.h>

class IUsartHook;
class vector;

enum class DRIVER_PORT {
	USART_1,
	USART_2,
	USART_3,
	UART_4,
	UART_5,
	USART_6
};

enum class BAUDRATE : uint32_t {
	RATE_9600 = 9600U,
	RATE_19200 = 19200U
};

enum class DIRECTION {
	NONE,
	RX,
	TX,
	RX_TX
};

enum class DATAWIDTH {
	B8, 
	B9
};

enum class STOPBITS {
	SB_0_5,
	SB_1,
	SB_1_5,
	SB_2
};

enum class PARITY {
	NONE,
	EVEN,
	ODD
};

enum class HWCONTROL {
	NONE,
	RTS,
	CTS,
	RTS_CTS
};

enum class OVERSAMPLING {
	B8,
	B16
};

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