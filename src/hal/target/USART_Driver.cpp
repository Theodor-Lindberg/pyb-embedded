#include "USART_Driver.hpp"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_gpio.h"

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


void SerialDriver::initialize(BAUDRATE baudrate, DIRECTION direction, DATAWIDTH datawidth, PARITY parity, HWCONTROL hw_control, OVERSAMPLING over_sampling) {
    LL_USART_InitTypeDef init_def;
    init_def.BaudRate = static_cast<uint32_t>(baudrate);

    switch (direction) {
    case DIRECTION::NONE:
        init_def.TransferDirection = LL_USART_DIRECTION_NONE;
        break;
    case DIRECTION::RX:
        init_def.TransferDirection = LL_USART_DIRECTION_RX;
    case DIRECTION::TX:
        init_def.TransferDirection = LL_USART_DIRECTION_TX;
    case DIRECTION::RX_TX:
        init_def.TransferDirection = LL_USART_DIRECTION_TX_RX;
    default:
        break;
    }

    switch (datawidth) {
        case DATAWIDTH::B8:
            init_def.DataWidth = LL_USART_DATAWIDTH_8B;
            break;
        case DATAWIDTH::B9:
        init_def.DataWidth = LL_USART_DATAWIDTH_9B;
            break;
        default:
            break;
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
            break;
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
            break;
    }

    switch (over_sampling) {
        case OVERSAMPLING::B16:
            init_def.OverSampling = LL_USART_OVERSAMPLING_16;
            break;
        case OVERSAMPLING::B8:
            init_def.OverSampling = LL_USART_OVERSAMPLING_8;
            break;
        default:
            break;
    }

    LL_USART_Init(USARTx, &init_def);
    
    LL_USART_ClockInitTypeDef c_def;
    c_def.ClockOutput = LL_USART_CLOCK_ENABLE;
    c_def.ClockPhase = LL_USART_PHASE_2EDGE;
    c_def.ClockPolarity = LL_USART_POLARITY_LOW;
    c_def.LastBitClockPulse = LL_USART_LASTCLKPULSE_NO_OUTPUT;
    LL_USART_ClockInit(USARTx, &c_def);

    // TX pin
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_6, LL_GPIO_AF_8);
    LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_6, LL_GPIO_PULL_UP);

    // RX pin
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_7, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_7, LL_GPIO_AF_8);
    LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_7, LL_GPIO_PULL_UP);
}
void SerialDriver::de_init() {
    LL_USART_DeInit(USARTx);
}

void SerialDriver::open() {
    LL_USART_Enable(USARTx);
}

void SerialDriver::close() {
    LL_USART_Disable(USARTx);
}

void SerialDriver::write(uint8_t data) {
    LL_USART_TransmitData8(USARTx, data);
}

void SerialDriver::set_baudrate(BAUDRATE baudrate) {
    close();
}

SerialDriver::SerialDriver(USART_Def* const USARTx) : USARTx(USARTx) { }

/*uint32_t SerialDriver::get_transfer_direction(DIRECTION direction) {
    switch (direction) {
        case DIRECTION::NONE:
            return LL_USART_DIRECTION_NONE;
        case DIRECTION::RX:
            return LL_USART_DIRECTION_RX;
        case DIRECTION::TX:
            return LL_USART_DIRECTION_TX;
        case DIRECTION::RX_TX:
            return LL_USART_DIRECTION_TX_RX;
    }
}*/