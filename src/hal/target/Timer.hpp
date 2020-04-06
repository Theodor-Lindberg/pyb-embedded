#pragma once
#include <stdint.h>
#include "ITimerHook.hpp"

enum class TIMER {
	TIMER1,
	TIMER2,
	TIMER3,
	TIMER4,
	TIMER5,
	TIMER6,
	TIMER7,
	TIMER8,
	TIMER12,
	TIMER13,
	TIMER14
};

class Timer {
	public:
	Timer();
	Timer(TIMER timer, ITimerHook* const timer_it_hook);
	void enable();
	void start();
	void stop();
	void set_interval(uint32_t ms);
	void reset();
	private:
	struct TIM_Def;
	TIM_Def* TIMx = nullptr;
	ITimerHook* const timer_it_hook = nullptr;
};