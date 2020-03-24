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

enum class OutputType {
	PUSH_PULL,
	OPEN_DRAIN
};

enum class Speed {
	LOW = 0,
	MEDIUM,
	HIGH,
	VERY_HIGH
};

enum class Port {
	A,
	B,
	C,
	D
};

enum class Pin {
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
};