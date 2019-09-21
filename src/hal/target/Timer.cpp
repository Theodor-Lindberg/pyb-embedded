#include "Timer.hpp"
#include "stm32f4xx_ll_tim.h"

struct Timer::TIM_Def : public TIM_TypeDef {};

extern "C" void TIM7_IRQHandler(void) {
	if (LL_TIM_IsActiveFlag_UPDATE(TIM7) != FlagStatus::RESET) {
		LL_TIM_ClearFlag_UPDATE(TIM7);
		NVIC_ClearPendingIRQ(TIM7_IRQn);
	}
}

Timer::Timer() : timer_it_hook(nullptr) { }

Timer::Timer(TIMER timer, ITimerHook* const timer_it_hook) : timer_it_hook(timer_it_hook) {
	switch (timer) {
		case TIMER::TIMER1:
		TIMx = static_cast<TIM_Def*>(TIM1);
			break;
		case TIMER::TIMER2:
		TIMx = static_cast<TIM_Def*>(TIM2);
			break;
		case TIMER::TIMER3:
		TIMx = static_cast<TIM_Def*>(TIM3);
			break;
		case TIMER::TIMER4:
		TIMx = static_cast<TIM_Def*>(TIM4);
			break;
		case TIMER::TIMER5:
		TIMx = static_cast<TIM_Def*>(TIM5);
			break;
		case TIMER::TIMER6:
		TIMx = static_cast<TIM_Def*>(TIM6);
			break;
		case TIMER::TIMER7:
		TIMx = static_cast<TIM_Def*>(TIM7);
			break;
		case TIMER::TIMER8:
		TIMx = static_cast<TIM_Def*>(TIM8);
			break;
		case TIMER::TIMER12:
		TIMx = static_cast<TIM_Def*>(TIM12);
			break;
		case TIMER::TIMER13:
		TIMx = static_cast<TIM_Def*>(TIM13);
			break;
		case TIMER::TIMER14:
		TIMx = static_cast<TIM_Def*>(TIM14);
			break;
	}
	
	LL_TIM_InitTypeDef init_def;
	init_def.Autoreload = 4999U;
	init_def.CounterMode = LL_TIM_COUNTERMODE_UP;
	init_def.RepetitionCounter = 0U;
	init_def.Prescaler = 16799U;
	init_def.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	LL_TIM_EnableCounter(TIMx);
	LL_TIM_EnableBRK(TIMx);

	if (LL_TIM_Init(TIMx, &init_def) != ErrorStatus::SUCCESS) {
		while (true);
	}

	NVIC_SetPriority(TIM7_IRQn, 0);
	NVIC_EnableIRQ(TIM7_IRQn);
	LL_TIM_EnableIT_UPDATE(TIMx);
}

void Timer::start() {
	LL_TIM_SetCounter(TIMx, 0U);
	//LL_TIM_ClearFlag_UPDATE(TIMx);
	LL_TIM_EnableCounter(TIMx);
}

void Timer::stop() {
	LL_TIM_DisableCounter(TIMx);
}

void Timer::set_interval(uint32_t ms) {

}

void Timer::reset() {

}