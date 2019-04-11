#include "stm32f4xx.h"

void turnLedOn(void) {
	GPIOB->ODR |= GPIO_ODR_OD4;
}

void turnLedOff(void) {
	GPIOB->ODR &= ~(GPIO_ODR_OD4);
}

int isButtonPressed(void) {
	return !(GPIOB->IDR & GPIO_IDR_ID3);
}

void setupLed(void) {
	// Set port B4 to general purpose output mode
	GPIOB->MODER &= ~(GPIO_MODER_MODE4);
	GPIOB->MODER |= GPIO_MODER_MODE4_0;

	// Output push-pull
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT4);

	// Low output speed
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;

	// No pull up or pull down
	GPIOB->PUPDR &= GPIO_PUPDR_PUPD4_0;
}

void setupButton(void) {
	// Set port B3 as input
	GPIOB->MODER &= ~(GPIO_MODER_MODE3);

	// Pull upp
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD3);
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD3_0;
}

void EXTI3_IRQHandler(void) {
	if (EXTI->PR & EXTI_PR_PR3) {
		// Clear interrupt flag
		EXTI->PR |= EXTI_PR_PR3;
		// Disable other interrupts
		NVIC_DisableIRQ(EXTI3_IRQn);
		GPIOB->ODR ^= GPIO_ODR_OD4;
		// Enable interrupts again
		NVIC_EnableIRQ(EXTI3_IRQn);
	}
}

int main()
{
	// Enable the GPIO clock for port B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	setupLed();
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