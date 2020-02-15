#pragma once
#include <stdint.h>

enum class PinMode {
	INPUT = 0,
	OUTPUT,
	ALTERNATE,
	ANALOG
};

enum class Pull {
	NO = 0,
	UP,
	DOWN
};

enum class Speed {
	LOW = 0,
	MEDIUM,
	HIGH,
	VERY_HIGH
};

struct GPIO_Def;
#define GPIO_DEF_DECLARATION struct GPIO_Def : GPIO_TypeDef {};
