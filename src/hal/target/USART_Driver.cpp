#include "USART_Driver.hpp"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"

USART_DEF_DECLARATION

SerialDriver& SerialDriver::get_instance(DRIVER_PORT driver_port) { 
	switch(driver_port) {
		case DRIVER_PORT::USART_1:
			static SerialDriver usart1(static_cast<USART_Def*>(USART1));
			return usart1;
		case DRIVER_PORT::USART_2:
			static SerialDriver usart2(static_cast<USART_Def*>(USART2));
			return usart2;
		case DRIVER_PORT::USART_3:
			static SerialDriver usart3(static_cast<USART_Def*>(USART3));
			return usart3;
		case DRIVER_PORT::UART_4:
			static SerialDriver uart4(static_cast<USART_Def*>(UART4));
			return uart4;
		case DRIVER_PORT::UART_5:
			static SerialDriver uart5(static_cast<USART_Def*>(UART5));
			return uart5;
		case DRIVER_PORT::USART_6:
			static SerialDriver usart6(static_cast<USART_Def*>(USART6));
			return usart6;
		default:
			 __builtin_unreachable();
			 break;
	}
}

bool SerialDriver::initialize(BAUDRATE baudrate, DIRECTION direction, DATAWIDTH datawidth, STOPBITS stopbits, PARITY parity, HWCONTROL hw_control, OVERSAMPLING over_sampling) {
	LL_USART_InitTypeDef init_def;
	init_def.BaudRate = static_cast<uint32_t>(baudrate);

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
		///LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART6);
		return false;
	}

	return true;
}

bool SerialDriver::de_init() {
	LL_USART_DeInit(USARTx);
}

void SerialDriver::open() {
	LL_USART_Enable(USARTx);
}

void SerialDriver::close() {
	LL_USART_Disable(USARTx);
}

void SerialDriver::write(uint8_t byte) {
	wait_ready_to_send();
	LL_USART_TransmitData8(USARTx, byte);
}

void SerialDriver::send(const uint8_t* data, uint32_t count) {
	while (count-- > 0U) {
		write(data[count]);
	}
}

void SerialDriver::print(const uint8_t* str) {
	while (*str != 0) {
		write(*(str++));
	}
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

SerialDriver::SerialDriver(USART_Def* const USARTx) : USARTx(USARTx) {}

void SerialDriver::wait_ready_to_send() {
	while (!LL_USART_IsActiveFlag_TC(USARTx));
}