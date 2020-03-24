#include "GPIO.hpp"
#include "stm32f4xx.h"

struct GPIO::GPIO_Def : GPIO_TypeDef {};

GPIO::GPIO(Port port, Pin pin) : GPIOBase(pin) {
	switch (port) {
		case Port::A:
			GPIOx = static_cast<GPIO::GPIO_Def*>(GPIOA);
			break;
		case Port::B:
			GPIOx = static_cast<GPIO::GPIO_Def*>(GPIOB);
			break;
		case Port::C:
			GPIOx = static_cast<GPIO::GPIO_Def*>(GPIOC);
			break;
		case Port::D:
			GPIOx = static_cast<GPIO::GPIO_Def*>(GPIOD);
			break;	
	}
}