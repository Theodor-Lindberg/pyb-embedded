#include "stm32f4xx.h"

enum PinMode {
    INPUT = 0,
    OUTPUT,
    ALTERNATE,
    ANALOG
};

enum Pull {
    NO = 0,
    UP,
    DOWN
};

enum Speed {
    LOW = 0,
    MEDIUM,
    HIGH,
    VERY_HIGH
};

struct Pin {
    GPIO_TypeDef* const GPIOx;
    const uint32_t number;
    const PinMode mode;
    const Pull pull;
    const Speed speed;
    Pin(GPIO_TypeDef* GPIOx, uint32_t number, PinMode mode, Pull pull, Speed speed):
    GPIOx(GPIOx), number(number), mode(mode), pull(pull), speed(speed) {}
};