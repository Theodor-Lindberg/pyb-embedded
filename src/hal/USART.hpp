#pragma once
#include <stdint.h>

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