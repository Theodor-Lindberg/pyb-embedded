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

class SerialDriver {
    public:
    static SerialDriver& get_instance(DRIVER_PORT driver_port);
    void initialize(BAUDRATE baudrate, DIRECTION direction, DATAWIDTH datawidth, PARITY parity, HWCONTROL hw_control, OVERSAMPLING over_sampling);
    void de_init();
    void open();
    void close();
    void write(uint8_t data);
    void set_baudrate(BAUDRATE baudrate);
    private:
    struct USART_Def;
    #define USART_DEF_DECLARATION struct SerialDriver::USART_Def : public USART_TypeDef {};
    SerialDriver(USART_Def* const USARTx);
    USART_Def* const USARTx;
};