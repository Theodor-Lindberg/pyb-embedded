#include "BoardLEDs.hpp"

int isButtonPressed(void) {
	return !(GPIOB->IDR & GPIO_IDR_ID3);
}

void setupButton(void) {
	// Set port B3 as input
	GPIOB->MODER &= ~(GPIO_MODER_MODE3);

	// Pull upp
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD3);
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD3_0;
}
 
extern "C" void EXTI3_IRQHandler(void) {
	if (EXTI->PR & EXTI_PR_PR3) {
		// Clear interrupt flag
		EXTI->PR |= EXTI_PR_PR3;
		// Disable other interrupts
		NVIC_DisableIRQ(EXTI3_IRQn);

		Board::get_blue_led().toggle();

		// Enable interrupts again
		NVIC_EnableIRQ(EXTI3_IRQn);
	}
}

int main()
{
	// Enable the GPIO clock for port B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	setupButton();

	// Enable the System Configuration Controller clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Enable interrupt line for port B3
	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PB;

	// Interuppt line is not masked
	EXTI->IMR = EXTI_IMR_IM3;

	// Trigger on falling edge
	EXTI->FTSR |= EXTI_FTSR_TR3;

	NVIC_SetPriority(EXTI3_IRQn, 0);
	NVIC_EnableIRQ(EXTI3_IRQn);

	while(1) {
	}
}