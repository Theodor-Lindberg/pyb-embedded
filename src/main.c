#include "stm32f4xx.h"

void delay (int a)
{
    volatile int i,j;

    for (i=0 ; i < a ; i++)
    {
        j++;
    }
    return;
}

void turnLedOn(void) {
	GPIOB->ODR |= GPIO_ODR_OD4;
}

void turnLedOff(void) {
	GPIOB->ODR |= GPIO_ODR_OD4;
}

int isButtonPressed(void) {
	return GPIOB->IDR & GPIO_IDR_ID3;
}

void setupLed(void) {
	// Set port B4 to general purpose output mode
	GPIOB->MODER &= ~(GPIO_MODER_MODE4_1);

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
	GPIOB->PUPDR &= GPIO_PUPDR_PUPD3_0;
}

void main()
{
	// Enable the GPIO clock for port B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	setupLed();
	setupButton();

	
	while(1) {
		// Turn LED on
		if (isButtonPressed()) {
			turnLedOn();
			delay(500000);
			turnLedOff();
			delay(500000);
		}
		else {
			turnLedOn();
		}
	}
}