#pragma once
#include <stdint.h>

class Timer {
	public:
	Timer();
	void start();
	void stop();
	void set_interval(uint32_t ms);
	void reset();
};