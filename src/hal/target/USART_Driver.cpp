#include "USART_Driver.hpp"
#include "IUsartHook.hpp"
#include "stm32f4xx_ll_usart.h"

struct SerialDriver::USART_Def : public USART_TypeDef {};

/**
 * @brief Get a singleton instance of a serial driver.
 * 
 * @param driver_port The USART/UART port to get.
 * @return SerialDriver& A reference to the instance.
 */
SerialDriver* SerialDriver::get_instance(DRIVER_PORT driver_port) { 
	switch(driver_port) {
			case DRIVER_PORT::USART_1:
				static SerialDriver usart1(static_cast<USART_Def*>(USART1));
				return &usart1;
			case DRIVER_PORT::USART_2:
				static SerialDriver usart2(static_cast<USART_Def*>(USART2));
				return &usart2;
			case DRIVER_PORT::USART_3:
				static SerialDriver usart3(static_cast<USART_Def*>(USART3));
				return &usart3;
			case DRIVER_PORT::UART_4:
				static SerialDriver uart4(static_cast<USART_Def*>(UART4));
				return &uart4;
			case DRIVER_PORT::UART_5:
				static SerialDriver uart5(static_cast<USART_Def*>(UART5));
				return &uart5;
			case DRIVER_PORT::USART_6:
				static SerialDriver usart6(static_cast<USART_Def*>(USART6));
				return &usart6;
			default:
				return nullptr;
		}
}

/**
 * @brief Close and then initialize a port, needs to opened before used.
 * 
 * @param baudrate The baudrate to use.
 * @param direction The directions of data used.
 * @param datawidth The size of each byte.
 * @param stopbits The number of stop bits used.
 * @param parity The parity of each package
 * @param hw_control 
 * @param over_sampling The sampling option used when receiving data.
 * @return true If the initialization was successful.
 * @return false If the initialization wasn't successful.
 */
bool SerialDriver::initialize(BAUDRATE baudrate, DIRECTION direction, DATAWIDTH datawidth, STOPBITS stopbits, PARITY parity, HWCONTROL hw_control, OVERSAMPLING over_sampling, IUsartHook* const usart_it_hook) {
	LL_USART_InitTypeDef init_def;
	init_def.BaudRate = static_cast<uint32_t>(baudrate);
	this->usart_it_hook = usart_it_hook;

	switch (direction) {
	case DIRECTION::NONE:
		init_def.TransferDirection = LL_USART_DIRECTION_NONE;
		break;
	case DIRECTION::RX:
		init_def.TransferDirection = LL_USART_DIRECTION_RX;
		break;
	case DIRECTION::TX:
		init_def.TransferDirection = LL_USART_DIRECTION_TX;
		break;
	case DIRECTION::RX_TX:
		init_def.TransferDirection = LL_USART_DIRECTION_TX_RX;
		break;
	default:
		return false;
	}

	switch (datawidth) {
		case DATAWIDTH::B8:
			init_def.DataWidth = LL_USART_DATAWIDTH_8B;
			break;
		case DATAWIDTH::B9:
		init_def.DataWidth = LL_USART_DATAWIDTH_9B;
			break;
		default:
			return false;
	}

	switch (stopbits) {
		case STOPBITS::SB_0_5:
			init_def.StopBits = LL_USART_STOPBITS_0_5;
			break;
		case STOPBITS::SB_1:
			init_def.StopBits = LL_USART_STOPBITS_1;
			break;
		case STOPBITS::SB_1_5:
			init_def.StopBits = LL_USART_STOPBITS_1_5;
			break;
		case STOPBITS::SB_2:
			init_def.StopBits = LL_USART_STOPBITS_2;
			break;
		default:
			return false;
	}

	switch (parity) {
		case PARITY::NONE:
			init_def.Parity = LL_USART_PARITY_NONE;
			break;
		case PARITY::EVEN:
			init_def.Parity = LL_USART_PARITY_EVEN;
			break;
		case PARITY::ODD:
			init_def.Parity = LL_USART_PARITY_ODD;
			break;
		default:
			return false;
	}

	switch (hw_control) {
		case HWCONTROL::NONE:
			init_def.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
			break;
		case HWCONTROL::RTS:
			init_def.HardwareFlowControl = LL_USART_HWCONTROL_RTS;
			break;
		case HWCONTROL::CTS:
			init_def.HardwareFlowControl = LL_USART_HWCONTROL_CTS;
			break;
		case HWCONTROL::RTS_CTS:
			init_def.HardwareFlowControl = LL_USART_HWCONTROL_RTS_CTS;
			break;
		 default:
			return false;
	}

	switch (over_sampling) {
		case OVERSAMPLING::B16:
			init_def.OverSampling = LL_USART_OVERSAMPLING_16;
			break;
		case OVERSAMPLING::B8:
			init_def.OverSampling = LL_USART_OVERSAMPLING_8;
			break;
		default:
			return false;
	}

	close();

	if (LL_USART_Init(USARTx, &init_def) != ErrorStatus::SUCCESS) {
		return false;
	}

	/* (2) NVIC Configuration for USART interrupts */
	/*  - Set priority for USARTx_IRQn */
	
	/*  - Enable USARTx_IRQn */
	NVIC_SetPriority(USART6_IRQn, 0);  
	NVIC_EnableIRQ(USART6_IRQn);
	/* Enable RXNE and Error interrupts */
	LL_USART_EnableIT_RXNE(USARTx);
	LL_USART_EnableIT_ERROR(USARTx);

	return true;
}

bool SerialDriver::de_init() {
	return LL_USART_DeInit(USARTx) == ErrorStatus::SUCCESS;
}

/**
 * @brief Opens a new serial connection.
 */
void SerialDriver::open() {
	LL_USART_Enable(USARTx);
}

/**
 * @brief Closes the port connection.
 */
void SerialDriver::close() {
	LL_USART_Disable(USARTx);
}

/**
 * @brief Write one byte worth of data to the serial port output buffer.
 * 
 * @param data The data to send.
 */
void SerialDriver::write(uint8_t data) {
	wait_ready_to_send();
	LL_USART_TransmitData8(USARTx, data);
}

/**
 * @brief Writes a specified number of bytes to the serial port using data from a buffer. 
 * 
 * @param data_buffer The data to write.
 * @param start The first index to send from.
 * @param end The last index to send from.
 */
bool SerialDriver::send(const uint8_t* data_buffer, uint32_t start, uint32_t end) {
	while (start <= end) {
		write(data_buffer[start++]);
	}
	return true;
}

bool SerialDriver::send_async(const uint8_t* data_buffer, uint32_t start, uint32_t end) {
	if (is_sending_async()) {	// Only one message can be sent asynchronosly
		return false;
	}
	message_last_index = data_buffer + end - start - 1U;
	message_to_send = (data_buffer + start);
	LL_USART_EnableIT_TC(USARTx);
	return true;
}

bool SerialDriver::print(const uint8_t* str) {
	while (*str != 0) {
		write(*(str++));
	}
	return true;
}

bool SerialDriver::is_sending_async() {
	return LL_USART_IsEnabledIT_TC(USARTx);
}

bool SerialDriver::set_baudrate(BAUDRATE baudrate) {
	close();
	LL_USART_InitTypeDef init_def;
	init_def.BaudRate = static_cast<uint32_t>(baudrate);
	init_def.TransferDirection = LL_USART_GetTransferDirection(USARTx);
	init_def.DataWidth = LL_USART_GetDataWidth(USARTx);
	init_def.HardwareFlowControl = LL_USART_GetHWFlowCtrl(USARTx);
	init_def.OverSampling = LL_USART_GetOverSampling(USARTx);
	init_def.Parity = LL_USART_GetParity(USARTx);
	init_def.StopBits = LL_USART_GetStopBitsLength(USARTx);
	if (LL_USART_Init(USARTx, &init_def) == ErrorStatus::SUCCESS) {
		open();
		return true;
	}
	return false;
}

void SerialDriver::rx_callback() {
	usart_it_hook->rx_it_hook();
}

void SerialDriver::tc_it() {
	if (message_to_send == message_last_index) {
		LL_USART_DisableIT_TC(USARTx);
	}
	else {
		write(*(message_to_send++));
	}
}

SerialDriver::SerialDriver(USART_Def* const USARTx) : USARTx(USARTx) { }

void SerialDriver::wait_ready_to_send() {
	while (!LL_USART_IsActiveFlag_TC(USARTx));
}

uint8_t SerialDriver::read() {
	return LL_USART_ReceiveData8(USARTx);
}

static USART_TypeDef* get_type_def(DRIVER_PORT driver_port) {
		switch(driver_port) {
		case DRIVER_PORT::USART_1:
			return USART1;
		case DRIVER_PORT::USART_2:
			return USART2;
		case DRIVER_PORT::USART_3:
			return USART3;
		case DRIVER_PORT::UART_4:
			return UART4;
		case DRIVER_PORT::UART_5:
			return UART5;
		case DRIVER_PORT::USART_6:
			return USART6;
		default:
			 __builtin_unreachable();
	}
}

void handle_interrupt(DRIVER_PORT driver_port) {
	USART_TypeDef* usart = get_type_def(driver_port);

	if (LL_USART_IsActiveFlag_RXNE(usart)) {
		SerialDriver::get_instance(driver_port)->rx_callback();
	}
	else if (LL_USART_IsActiveFlag_TC(usart)) {
		SerialDriver::get_instance(driver_port)->tc_it();
	}
}

extern "C" void USART6_IRQHandler(void) {
	handle_interrupt(DRIVER_PORT::USART_6);
	NVIC_ClearPendingIRQ(USART6_IRQn);
}